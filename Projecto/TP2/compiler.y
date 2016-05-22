%{

#define _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(char *);

%}

%union {
	int num;
	char *str;
}

/* Terminal symbols */
%token /*<num>*/ NUMBER
%token /*<str>*/ NAME TEXT AND OR EQLS DIFF SMEQ GTEQ
%token START END WHILE IF READ PRINT ELSE

/* AND -> "&&" | OR -> "||" | EQLS -> "==" | DIFF -> "!=" | SMEQ -> "<=" | GTEQ -> ">=" */

/* Non-terminal symbols */
//%type <str> Declarations Declaration InitArray InitMatrix Body Statement Args MoreArgs Value Variable Prints Else Expression Parcel Factor BooleanExpression BooleanFactor

%%

Program : Declarations START Body END
        ;

Declarations : /* EMPTY */
             | Declarations Declaration 
             ;

Declaration : Variable ';'
            | NAME '[' Expression ']' '=' '{' InitArray '}'
	    | NAME '[' Expression ']' '[' Expression ']' '=' '{' InitMatrix '}'
            | NAME '=' Expression ';'
            ;

InitArray  : NUMBER
           | InitArray ',' NUMBER
           ;

InitMatrix : '{' InitArray '}'
	   | InitMatrix ',' '{' InitArray '}'
           ;

Body : /* EMPTY */
     | Body Statement
     ;

Statement : Variable '=' Expression ';'
          | Variable '=' NAME '(' Args ')' ';'
      /** | NAME '(' Args ')' ';' */	
          | WHILE '(' BooleanExpression ')' '{' Body '}'
          | IF '(' BooleanExpression ')' '{' Body '}' Else  
          | READ '(' Variable ')' ';'
          | PRINT '(' Prints ')' ';'
          ;

Args : /* EMPTY */ 
     | MoreArgs
     ;

MoreArgs : Value 
         | MoreArgs ',' Value 
         ;

Prints : Value
       | TEXT 
       ;

Else : /* EMPTY */
     | ELSE '{' Body '}'
     ;

Expression : Parcel
           | Expression '+' Parcel 
           | Expression '-' Parcel
           ;

Parcel : Parcel '*' Factor
       | Parcel '/' Factor
       | Parcel '%' Factor
       | Factor
       ;

Factor : Value
       | '(' Expression ')'
       ;

Value : NUMBER
      | Variable
      ;

Variable : NAME
         | NAME '[' Expression ']'
         | NAME '[' Expression ']' '[' Expression ']'
         ;

BooleanExpression : BooleanExpression AND BooleanFactor
                  | BooleanExpression OR BooleanFactor
                  | BooleanFactor
                  ;

BooleanFactor : Expression EQLS Expression
              | Expression DIFF Expression
              | Expression '<' Expression
              | Expression '>' Expression
	      | Expression SMEQ Expression
              | Expression GTEQ Expression
              | '(' BooleanExpression ')'
              ;

%%

#include "lex.yy.c"

int yyerror(char *s) {
	fprintf(stderr, "%s (line %d)\n", s, yylineno);
	return 0;
}

int main() {
	yyparse();
	return 0;
}
