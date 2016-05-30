%{

#define _GNU_SOURCE

#define NO  0
#define YES 1

#define INTEGER 0
#define ARRAY   1
#define MATRIX  2

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct idtable {
	char *var;		// Variable name
  	int type; 		// Variable type
  	int index;		// Variable index on stack
	int columns;		// Number of columns (for integer is 1)
	struct idtable *next;
} ID;

typedef struct idtable *IdTable;

typedef struct listwhiles {
	int numWhile;
	struct listwhiles *next;
} LWH;

typedef struct listwhiles *ListWhiles;

typedef struct listifs {
	int numIf;
	struct listifs *next;
} LIF;

typedef struct listifs *ListIfs;

int yylex();
int yyerror(char *);

IdTable insertVar(IdTable t, char *var, int type, int index, int columns) {
	if(t == NULL) {
		t = (IdTable) malloc(sizeof(struct idtable));
		t->var = strdup(var);
		t->type = type;
		t->index = index;
		t->columns = columns;
		t->next = NULL;
	}
	else t->next = insertVar(t->next, var, type, index, columns);
	return t;
}

int existVar(IdTable t, char *var) {
	if(t == NULL) return NO;
	else if(strcmp(var, t->var) == 0) return YES;
	else return existVar(t->next, var);
}

int getTypeVar(IdTable t, char *var) {
	if(t == NULL) return -1;
	else if(strcmp(var, t->var) == 0) return t->type;
	else return getTypeVar(t->next, var);
}

int getVarIndex(IdTable t, char *var) {
	if(t == NULL) return -1;
	else if(strcmp(var, t->var) == 0) return t->index;
	else return getVarIndex(t->next, var);
}

int getNumCols(IdTable t, char *var) {
	if(t == NULL) return 0;
	else if(strcmp(var, t->var) == 0) return t->columns;
	else return getNumCols(t->next, var);
}

FILE *fp;		// File where instructions will be saved

int sp = 0;		// Stack pointer	
int addr = 0;		// Instruction index
int endAddr = 0;	// Index of the last flow control ending instruction
int numWhile = 0;	// Number of whiles
int numIf = 0;		// Number of ifs

IdTable t = NULL;
ListWhiles listWhiles = NULL;
ListIfs listIfs = NULL;

%}

%union {
	int num;
	char *str;
}

/* Terminal symbols */
%token <str> NAME TEXT EQLS DIFF SMEQ GTEQ
%token <num> NUMBER 
%token AND OR START END WHILE IF READ PRINT ELSE D1 D2

%%

Program : Declarations {

		fprintf(fp, "start\n");
		addr++;

        } START Body END {

		if(addr == endAddr + 1) fprintf(fp, "     nop\n     end\n");
		else fprintf(fp, "     end\n");
		fclose(fp);

	} 
        ;

Declarations : /* EMPTY */																				
             | Declarations NAME ';' {
			
			if(existVar(t, $2) == YES) {
				char buf[50];
				sprintf(buf, "variable %s already declared", $2);
				yyerror(buf);
			}
			else {
				t = insertVar(t, $2, INTEGER, sp, 1);
				fprintf(fp, "     pushi 0\n");
				sp++;
				addr++;
			}

             }
	     | Declarations D1 NAME '[' NUMBER ']' ';' {

			if(existVar(t, $3) == YES) {
				char buf[50];
				sprintf(buf, "variable %s already declared", $3);
				yyerror(buf);
			}
			else {
				t = insertVar(t, $3, ARRAY, sp, $5);
				fprintf(fp, "     pushn %d\n", $5);
				sp += $5;
				addr++;
			}

	     }			
             | Declarations D2 NAME '[' NUMBER ']' '[' NUMBER ']' ';' {

			if(existVar(t, $3) == YES) {
				char buf[50];
				sprintf(buf, "variable %s already declared", $3);
				yyerror(buf);
			}
			else {
				t = insertVar(t, $3, MATRIX, sp, $8);
				fprintf(fp, "     pushn %d\n", $5 * $8);
				sp += $5 * $8;
				addr++;
			}
   
             }							
             ;

Body : /* EMPTY */
     | Body Statement
     ;

Statement : NAME '=' Expression ';' {

			if(existVar(t, $1) == YES) {
				if(getTypeVar(t, $1) == INTEGER) {
					int varIndex = getVarIndex(t, $1);
					fprintf(fp, "     storeg %d\n", varIndex);
					addr++;
				}
				else {
					char buf[50];
					sprintf(buf, "variable %s has another type", $1);
					yyerror(buf);
				}
			}
			else {
				char buf[50];
				sprintf(buf, "variable %s is not declared", $1);
				yyerror(buf);
			}
          
	  }									
          | D1 NAME {

			if(existVar(t, $2) == YES) {
				if(getTypeVar(t, $2) == ARRAY) {
					int varIndex = getVarIndex(t, $2);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
					addr += 3;
				}
				else {
					char buf[50];
					sprintf(buf, "variable %s has another type", $2);
					yyerror(buf);
				}
			}
			else {
				char buf[50];
				sprintf(buf, "variable %s is not declared", $2);
				yyerror(buf);
			}
          
	  } '[' Expression ']' '=' Expression ';' {

			fprintf(fp, "     storen\n");	
			addr++;

          }				
          | D2 NAME {

			if(existVar(t, $2) == YES) {
				if(getTypeVar(t, $2) == MATRIX) {
					int varIndex = getVarIndex(t, $2);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
					addr += 3;
				}
				else {
					char buf[50];
					sprintf(buf, "variable %s has another type", $2);
					yyerror(buf);
				}
			}
			else {
				char buf[50];
				sprintf(buf, "variable %s is not declared", $2);
				yyerror(buf);
			}
          
	  } '[' Expression ']' {

			int numCols = getNumCols(t, $2);
			fprintf(fp, "     pushi %d\n     mul\n", numCols);
			addr += 2;

          } '[' Expression ']' '=' {

			fprintf(fp, "     add\n");
			addr++;

          } Expression ';' {

			fprintf(fp, "     storen\n");	
			addr++;

          }	
          | WHILE {
	
			numWhile++;
			ListWhiles aux = (ListWhiles) malloc(sizeof(struct listwhiles));
			aux->numWhile = numWhile;
			aux->next = listWhiles;
			listWhiles = aux;
			fprintf(fp, "while%d:\n", numWhile);
			addr++;

          } '(' BooleanExpression ')' {

			fprintf(fp, "     jz endWhile%d\n", numWhile);
			addr++;

          } '{' Body '}' {

			fprintf(fp, "     jump while%d\n", listWhiles->numWhile);
			addr++;
			if(endAddr == addr - 1) {
				fprintf(fp, "     nop\nendWhile%d:\n", listWhiles->numWhile);
				addr++;
			}		
			else fprintf(fp, "endWhile%d:\n", listWhiles->numWhile);
			endAddr = addr;
			addr++;
			listWhiles = listWhiles->next;

          }	
          | IF '(' BooleanExpression ')' {

			numIf++;
			ListIfs aux = (ListIfs) malloc(sizeof(struct listifs));
			aux->numIf = numIf;
			aux->next = listIfs;
			listIfs = aux;
			fprintf(fp, "     jz else%d\n", numIf);
			addr++;

          } '{' Body '}' Else  
          | READ '(' NAME ')' ';' {

			if(existVar(t, $3) == YES) {
				if(getTypeVar(t, $3) == INTEGER) {
					int varIndex = getVarIndex(t, $3);
					fprintf(fp, "     read\n     atoi\n     storeg %d\n", varIndex);
					addr += 3;
				}
				else {
					char buf[50];
					sprintf(buf, "variable %s has another type", $3);
					yyerror(buf);
				}
			}
			else {
				char buf[50];
				sprintf(buf, "variable %s is not declared", $3);
				yyerror(buf);
			}
          
	  }
 	  | READ '(' D1 NAME {

			if(existVar(t, $4) == YES) {
				if(getTypeVar(t, $4) == ARRAY) {
					int varIndex = getVarIndex(t, $4);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
					addr += 3;
				}
				else {
					char buf[50];
					sprintf(buf, "variable %s has another type", $4);
					yyerror(buf);
				}
			}
			else {
				char buf[50];
				sprintf(buf, "variable %s is not declared", $4);
				yyerror(buf);
			}
          
	  } '[' Expression ']' ')' ';' {

			fprintf(fp, "     read\n     atoi\n     storen\n");
			addr += 3;

          }
          | READ '(' D2 NAME {

			if(existVar(t, $4) == YES) {
				if(getTypeVar(t, $4) == MATRIX) {
					int varIndex = getVarIndex(t, $4);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
					addr += 3;
				}
				else {
					char buf[50];
					sprintf(buf, "variable %s has another type", $4);
					yyerror(buf);
				}
			}
			else {
				char buf[50];
				sprintf(buf, "variable %s is not declared", $4);
				yyerror(buf);
			}
          
	  } '[' Expression ']' {

			int numCols = getNumCols(t, $4);
			fprintf(fp, "     pushi %d\n     mul\n", numCols);
			addr += 2;

          } '[' Expression ']' ')' ';' {

			fprintf(fp, "     add\n     read\n     atoi\n     storen\n");
			addr += 4;

          }					
          | PRINT '(' Prints ')' ';'
          | NAME '(' Args ')' ';' {
	
			fprintf(fp, "     pusha %s\n     call\nretorno:\n     nop", $1);
			addr++;

          }
          ;

Prints : Value {

			fprintf(fp, "     writei\n");
			addr++;

       }
       | TEXT {

    			fprintf(fp, "     pushs %s\n     writes\n", $1);
			addr += 2;

       }
       ;

Else : /* EMPTY */ {

   			if(endAddr == addr - 1) {
				fprintf(fp, "     nop\nelse%d:\n", listIfs->numIf);
				addr++;
			}
			else fprintf(fp, "else%d:\n", listIfs->numIf);
			listIfs = listIfs->next;
			endAddr = addr;
			addr++;

     }
     | ELSE {

			if(endAddr == addr - 1) {
				fprintf(fp, "     nop\n     jump endif%d\nelse%d:\n", listIfs->numIf, listIfs->numIf);
 				addr++;
			}
			else fprintf(fp, "     jump endif%d\nelse%d:\n", listIfs->numIf, listIfs->numIf);
			endAddr = addr;
			addr++;

     } '{' Body '}' {

			if(endAddr == addr - 1) {
				fprintf(fp, "     nop\nendif%d:\n", listIfs->numIf);
				addr++;
			}
			else fprintf(fp, "endif%d:\n", listIfs->numIf);
			listIfs = listIfs->next;
			endAddr = addr;
			addr++;

     }
     ;

Expression : Parcel
           | Expression '+' Parcel {

   			fprintf(fp, "     add\n");
			addr++;

           }
           | Expression '-' Parcel {

   			fprintf(fp, "     sub\n");
			addr++;

           }	
           ;

Parcel : Parcel '*' Factor {

   			fprintf(fp, "     mul\n");
			addr++;

       }	
       | Parcel '/' Factor {

   			fprintf(fp, "     div\n");
			addr++;

       }	
       | Parcel '%' Factor {

   			fprintf(fp, "     mod\n");
			addr++;

       }	
       | Factor
       ;

Factor : NUMBER	{

   			fprintf(fp, "     pushi %d\n", $1);
			addr++;

       }		
       | Value
       | '(' Expression ')'
       ;

Value : NAME {

			if(existVar(t, $1) == YES) {
				if(getTypeVar(t, $1) == INTEGER) {
					int varIndex = getVarIndex(t, $1);
					fprintf(fp, "     pushg %d\n", varIndex);
					addr++;
				}
				else {
					char buf[50];
					sprintf(buf, "variable %s has another type", $1);
					yyerror(buf);
				}
			}
			else {
				char buf[50];
				sprintf(buf, "variable %s is not declared", $1);
				yyerror(buf);
			}
          
      }											     				
      | D1 NAME {

			if(existVar(t, $2) == YES) {
				if(getTypeVar(t, $2) == ARRAY) {
					int varIndex = getVarIndex(t, $2);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
					addr += 3;
				}
				else {
					char buf[50];
					sprintf(buf, "variable %s has another type", $2);
					yyerror(buf);
				}
			}
			else {
				char buf[50];
				sprintf(buf, "variable %s is not declared", $2);
				yyerror(buf);
			}
          
      } '[' Expression ']' {

			fprintf(fp, "     loadn\n");
			addr++;

      }															
      | D2 NAME {

			if(existVar(t, $2) == YES) {
				if(getTypeVar(t, $2) == MATRIX) {
					int varIndex = getVarIndex(t, $2);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
					addr += 3;
				}
				else {
					char buf[50];
					sprintf(buf, "variable %s has another type", $2);
					yyerror(buf);
				}
			}
			else {
				char buf[50];
				sprintf(buf, "variable %s is not declared", $2);
				yyerror(buf);
			}
          
      } '[' Expression ']' {

			int numCols = getNumCols(t, $2);
			fprintf(fp, "     pushi %d\n     mul\n", numCols);
			addr += 2;

      } '[' Expression ']' {

			fprintf(fp, "     add\n     loadn\n");
			addr += 2;

      }												
      ;

Args : /* EMPTY */ 
     | MoreArgs
     ;

MoreArgs : Value 
         | NUMBER {

			fprintf(fp, "     pushi %d\n", $1);
			addr++;

         }
         | MoreArgs ',' NUMBER {

			fprintf(fp, "     pushi %d\n", $3);
			addr++;

         }
         | MoreArgs ',' Value 
         ;

BooleanExpression : BooleanExpression AND BooleanFactor {

			fprintf(fp, "     mul\n");
			addr++;

		  }
                  | BooleanExpression OR BooleanFactor {

			fprintf(fp, "     add\n");
			addr++;

	          }
                  | BooleanFactor
                  ;

BooleanFactor : Expression EQLS Expression {

   			fprintf(fp, "     equal\n");
			addr++;

              }
              | Expression DIFF Expression {

   			fprintf(fp, "     equal\n     pushi 0\n     equal\n");
			addr += 3;

              }
              | Expression '<' Expression {

   			fprintf(fp, "     inf\n");
			addr++;

              }
              | Expression '>' Expression {

   			fprintf(fp, "     sup\n");
			addr++;

              }
	      | Expression SMEQ Expression {

   			fprintf(fp, "     infeq\n");
			addr++;

              }
              | Expression GTEQ Expression {

   			fprintf(fp, "     supeq\n");
			addr++;

              }
              | '(' BooleanExpression ')'
              ;

%%

#include "lex.yy.c"

int yyerror(char *s) {
	fprintf(stderr, "%s (line %d)\n", s, yylineno);
	return 0;
}

int main() {
	fp = fopen("test.vm", "w");
	yyparse();
	return 0;
}
