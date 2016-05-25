%{

#define _GNU_SOURCE
#define DEC 0
#define ATR 1

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(char *);

FILE *fp = fopen("test.vm", "w");	// File where instructions will be saved
int sp = 0;				// Stack pointer

%}

%union {
	int num;
	char *str;
}

/* Terminal symbols */
%token <num> NUMBER
%token AND OR EQLS DIFF SMEQ GTEQ
%token <str> NAME TEXT 
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
			
			if(/* exists $2 on tableId */) {
				char buf[50];
				sprintf(buf, "variable %s already declared", $2);
				yyerror(buf);
			}
			else {
				/* save $2 on tableId ($2, sp, lines = 0, columns = 0) */
				fprintf(fp, "     pushi 0\n");
				sp++;
			}

             }
	     | Declarations NAME '[' NUMBER ']'	';' {

			if(/* exists $2 on tableId */) {
				char buf[50];
				sprintf(buf, "variable %s already declared", $2);
				yyerror(buf);
			}
			else {
				/* save $2 on tableId ($2, sp, lines = 0, columns = $4) */
				fprintf(fp, "     pushn %d\n", $4);
				sp += $4;
			}

	     }			
             | Declarations NAME '[' NUMBER ']' '[' NUMBER ']' ';' {

			if(/* exists $2 on tableId */) {
				char buf[50];
				sprintf(buf, "variable %s already declared", $2);
				yyerror(buf);
			}
			else {
				/* save $2 on tableId ($2, sp, line = $4, column = $7) */
				fprintf(fp, "     pushn %d\n", $4 * $7);
				sp += $4 * $7;
			}
   
             }							
             ;

Body : /* EMPTY */
     | Body Statement
     ;

Statement : NAME '=' Expression ';' {

			if(/* exists $1 on tableId */) {
				if(/* type of $1 is integer */) {
					/* int varIndex = getVarIndex($1) */
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

			if(/* exists $1 on tableId */) {
				if(/* type of $1 is array */) {
					/* int varIndex = getVarIndex($1) */
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

			if(/* exists $1 on tableId */) {
				if(/* type of $1 is matrix */) {
					/* int varIndex = getVarIndex($1) */
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

			/* int numCols = getNumCols($1) */
			fprintf(fp, "     pushi %d\n     mul\n", numCols);

          } '[' Expression ']' {

			fprintf(fp, "     add\n");

          } '=' Expression ';' {

			fprintf(fp, "     storen\n");	

          }	
          | WHILE {

			fprintf(fp, "ciclo:\n");

          } '(' BooleanExpression ')' {

			fprintf(fp, "     jz fim:\n");

          } '{' Body '}' {

			fprintf(fp, "     jump ciclo\nfim:\n");

          }	
          | IF '(' BooleanExpression ')' {

			fprintf(fp, "     jz else\n");

          } '{' Body '}' Else  
          | READ '(' NAME ')' ';' {

			if(/* exists $3 on tableId */) {
				if(/* type of $3 is integer */) {
					/* int varIndex = getVarIndex($3) */
					fprintf(fp, "     read\n      atoi\n     storeg %d\n", varIndex);
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

			if(/* exists $3 on tableId */) {
				if(/* type of $3 is array */) {
					/* int varIndex = getVarIndex($3) */
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

			fprintf(fp, "     read\n      atoi\n     storen\n");

          }
          | READ '(' NAME {

			if(/* exists $3 on tableId */) {
				if(/* type of $3 is matrix */) {
					/* int varIndex = getVarIndex($3) */
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
				sprintf(buf, "variable %s is not declared", $1);
				yyerror(buf);
			}
          
	  } '[' Expression ']' {

			/* int numCols = getNumCols($3) */
			fprintf(fp, "     pushi %d\n     mul\n", numCols);

          } '[' Expression ']' ')' ';' {

			fprintf(fp, "     add\n     read\n      atoi\n     storen\n");

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

			if(/* exists $1 on tableId */) {
				if(/* type of $1 is integer */) {
					/* int varIndex = getVarIndex($1) */
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

			if(/* exists $1 on tableId */) {
				if(/* type of $1 is array */) {
					/* int varIndex = getVarIndex($1) */
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

			/* int numCols = getNumCols($1) */
			fprintf(fp, "     loadn\n");

      }															
      | NAME {

			if(/* exists $1 on tableId */) {
				if(/* type of $1 is matrix */) {
					/* int varIndex = getVarIndex($1) */
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

			/* int numCols = getNumCols($1) */
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

   			fprintf(fp, "     not\n");

              }
              | Expression DIFF Expression {

   			fprintf(fp, "     equal\n");

              }
              | Expression '<' Expression {

   			fprintf(fp, "     supeq\n");

              }
              | Expression '>' Expression {

   			fprintf(fp, "     infeq\n");

              }
	      | Expression SMEQ Expression {

   			fprintf(fp, "     sup\n");

              }
              | Expression GTEQ Expression {

   			fprintf(fp, "     inf\n");

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
	yyparse();
	return 0;
}
