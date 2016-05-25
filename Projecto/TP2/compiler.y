%{

#define _GNU_SOURCE
#define NO  0
#define YES 1

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct idtable {
	char *var;		// Variable name
  	char *type; 		// Variable type
  	int index;		// Variable index on stack
	int lines;		// Number of lines (for integer and array is 1)
	int columns;		// Number of columns (for integer is 1)
	struct idtable *next;
} ID;

typedef struct idtable *IdTable;

int yylex();
int yyerror(char *);

IdTable insertVar(IdTable t, char *var, char *type, int index, int lines, int columns) {
	if(t == NULL) {
		t = (IdTable) malloc(sizeof(struct idtable));
		t->var = strdup(var);
		t->type = strdup(type);
		t->index = index;
		t->lines = lines;
		t->columns = columns;
		t->next = NULL;
	}
	else t->next = insertVar(t->next, var, type, index, lines, columns);
	return t;
}

int existVar(IdTable t, char *var) {
	if(t == NULL) return NO;
	else if(strcmp(var, t->var) == 0) return YES;
	else return existVar(t->next, var);
}

char *getTypeVar(IdTable t, char *var) {
	if(t == NULL) return NULL;
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
int counterFim = 0;	
IdTable t = NULL;

%}

%union {
	int num;
	char *str;
}

/* Terminal symbols */
%token <str> NAME TEXT EQLS DIFF SMEQ GTEQ
%token <num> NUMBER
%token AND OR  
%token START END WHILE IF READ PRINT ELSE

/* Non-terminal symbols */
//%type <str> Declarations Declaration InitArray InitMatrix Body Statement Args MoreArgs Value Prints Else Expression Parcel Factor BooleanExpression BooleanFactor

%%

Program : Declarations {

		fprintf(fp, "start\n");

        } START Body END {

		fprintf(fp, "     end\n");
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
				t = insertVar(t, $2, "integer", sp, 1, 1);
				fprintf(fp, "     pushi 0\n");
				sp++;
			}

             }
	     | Declarations NAME '[' NUMBER ']'	';' {

			if(existVar(t, $2) == YES) {
				char buf[50];
				sprintf(buf, "variable %s already declared", $2);
				yyerror(buf);
			}
			else {
				t = insertVar(t, $2, "array", sp, 1, $4);
				fprintf(fp, "     pushn %d\n", $4);
				sp += $4;
			}

	     }			
             | Declarations NAME '[' NUMBER ']' '[' NUMBER ']' ';' {

			if(existVar(t, $2) == YES) {
				char buf[50];
				sprintf(buf, "variable %s already declared", $2);
				yyerror(buf);
			}
			else {
				t = insertVar(t, $2, "matrix", sp, $4, $7);
				fprintf(fp, "     pushn %d\n", $4 * $7);
				sp += $4 * $7;
			}
   
             }							
             ;

Body : /* EMPTY */
     | Body Statement
     ;

Statement : NAME '=' Expression ';' {

			if(existVar(t, $1) == YES) {
				if(strcmp(getTypeVar(t, $1), "integer") == 0) {
					int varIndex = getVarIndex(t, $1);
					fprintf(fp, "     storeg %d\n", varIndex);
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
          | NAME {

			if(existVar(t, $1) == YES) {
				if(strcmp(getTypeVar(t, $1), "array") == 0) {
					int varIndex = getVarIndex(t, $1);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
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
          
	  } '[' Expression ']' '=' Expression ';' {

			fprintf(fp, "     storen\n");	

          }				
          | NAME {

			if(existVar(t, $1) == YES) {
				if(strcmp(getTypeVar(t, $1), "matrix") == 0) {
					int varIndex = getVarIndex(t, $1);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
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
          
	  } '[' Expression ']' {

			int numCols = getNumCols(t, $1);
			fprintf(fp, "     pushi %d\n     mul\n", numCols);

          } '[' Expression ']' {

			fprintf(fp, "     add\n");

          } '=' Expression ';' {

			fprintf(fp, "     storen\n");	

          }	
          | WHILE {

			fprintf(fp, "ciclo:\n");

          } '(' BooleanExpression ')' {

			fprintf(fp, "     jz fim\n");

          } '{' Body '}' {

			fprintf(fp, "     jump ciclo\nfim:\n");

          }	
          | IF '(' BooleanExpression ')' {

			fprintf(fp, "     jz else\n");

          } '{' Body '}' Else  
          | READ '(' NAME ')' ';' {

			if(existVar(t, $3) == YES) {
				if(strcmp(getTypeVar(t, $3), "integer") == 0) {
					int varIndex = getVarIndex(t, $3);
					fprintf(fp, "     read\n     atoi\n     storeg %d\n", varIndex);
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
 	  | READ '(' NAME {

			if(existVar(t, $3) == YES) {
				if(strcmp(getTypeVar(t, $3), "array") == 0) {
					int varIndex = getVarIndex(t, $3);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
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
          
	  } '[' Expression ']' ')' ';' {

			fprintf(fp, "     read\n     atoi\n     storen\n");

          }
          | READ '(' NAME {

			if(existVar(t, $3) == YES) {
				if(strcmp(getTypeVar(t, $3), "matrix") == 0) {
					int varIndex = getVarIndex(t, $3);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
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
          
	  } '[' Expression ']' {

			int numCols = getNumCols(t, $3);
			fprintf(fp, "     pushi %d\n     mul\n", numCols);

          } '[' Expression ']' ')' ';' {

			fprintf(fp, "     add\n     read\n     atoi\n     storen\n");

          }					
          | PRINT '(' Prints ')' ';'
          ;

Prints : Value {

			fprintf(fp, "     writei\n");

       }
       | TEXT {

    			fprintf(fp, "     pushs %s\n     writes\n", $1);

       }
       ;

Else : /* EMPTY */ {

   			fprintf(fp, "else:\n");

     }
     | ELSE {

			fprintf(fp, "     jump fim\nelse:\n");

     } '{' Body '}' {

			fprintf(fp, "fim:\n");

     }
     ;

Expression : Parcel
           | Expression '+' Parcel {

   			fprintf(fp, "     add\n");

           }
           | Expression '-' Parcel {

   			fprintf(fp, "     sub\n");

           }	
           ;

Parcel : Parcel '*' Factor {

   			fprintf(fp, "     mul\n");

       }	
       | Parcel '/' Factor {

   			fprintf(fp, "     div\n");

       }	
       | Parcel '%' Factor {

   			fprintf(fp, "     mod\n");

       }	
       | Factor
       ;

Factor : NUMBER	{

   			fprintf(fp, "     pushi %d\n", $1);

       }		
       | Value
       | NAME '(' Args ')' /* loading information... */
       | '(' Expression ')'
       ;

Value : NAME {

			if(existVar(t, $1) == YES) {
				if(strcmp(getTypeVar(t, $1), "integer") == 0) {
					int varIndex = getVarIndex(t, $1);
					fprintf(fp, "     pushg %d\n", varIndex);
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
      | NAME {

			if(existVar(t, $1) == YES) {
				if(strcmp(getTypeVar(t, $1), "array") == 0) {
					int varIndex = getVarIndex(t, $1);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
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
          
      } '[' Expression ']' {

			fprintf(fp, "     loadn\n");

      }															
      | NAME {

			if(existVar(t, $1) == YES) {
				if(strcmp(getTypeVar(t, $1), "matrix") == 0) {
					int varIndex = getVarIndex(t, $1);
					fprintf(fp, "     pushgp\n     pushi %d\n     padd\n", varIndex);
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
          
      } '[' Expression ']' {

			int numCols = getNumCols(t, $1);
			fprintf(fp, "     pushi %d\n     mul\n", numCols);

      } '[' Expression ']' {

			fprintf(fp, "     add\n     loadn\n");

      }												
      ;

Args : /* EMPTY */ 
     | MoreArgs
     ;

MoreArgs : Value 
         | MoreArgs ',' Value 
         ;

BooleanExpression : BooleanExpression AND BooleanFactor /* loading information... */
                  | BooleanExpression OR BooleanFactor /* loading information... */
                  | BooleanFactor
                  ;

BooleanFactor : Expression EQLS Expression {

   			fprintf(fp, "     equal\n");

              }
              | Expression DIFF Expression {

   			fprintf(fp, "     not\n");

              }
              | Expression '<' Expression {

   			fprintf(fp, "     inf\n");

              }
              | Expression '>' Expression {

   			fprintf(fp, "     sup\n");

              }
	      | Expression SMEQ Expression {

   			fprintf(fp, "     infeq\n");

              }
              | Expression GTEQ Expression {

   			fprintf(fp, "     supeq\n");

              }
              | '(' BooleanExpression ')'
              ;

%%

#include "lex.yy.c"

int yyerror(char *s) {
	fprintf(stderr, "%s (line %d)\n", s, yylineno);
	return 0;
}

int main(int argc, char *argv[]) {
	fp = fopen("test.vm", "w");
	yyparse();
	return 0;
}
