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
%token <num> NUMBER
%token <str> NAME TEXT
%token START END WHILE IF READ PRINT ELSE AND OR

/* Non-terminal symbols */
%type <str> Declarations Body Statement Args MoreArgs Value Variable Prints Else Expression Parcel Factor BooleanExpression BooleanFactor

%%

Program : Declarations START '%%' Body '%%' END
        ;

Declarations : /* EMPTY */
             | Declarations Declaration 
             ;

Declaration : Variable ';'
            | NAME '['NUMBER']' '=' '{'InitArray1 '}'
	    | NAME '['NUMBER']''['NUMBER']' '=' '{'InitArray2'}'
            | Variable '=' Expression ';'

InitArray2 : '{' InitArray1 '}'
	   | InitArray2 ',' '{'InitArray1'}'

InitArray1 : NUMBER
           | InitArray1 ',' NUMBER

Body : /* EMPTY */
     | Body Statement
     ;

Statement : Variable '=' Expression ';'
          | Variable '=' NAME '(' Args ')' ';'
          | NAME '(' Args ')' ';'	{/*program call with no return*/}
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

Value : NUMBER
      | Variable
      ;

Variable : NAME
         | NAME '[' Expression ']'
         | NAME '[' Expression ']' '[' Expression ']'
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

BooleanExpression : BooleanExpression AND BooleanFactor
                  | BooleanExpression OR BooleanFactor
                  | BooleanFactor
                  ;

BooleanFactor : Expression '==' Expression
              | Expression '!=' Expression
              | Expression '<' Expression
              | Expression '>' Expression
              | '(' BooleanExpression ')'
              ;

%%

#include "lex.yy.c"

int yyerror(char *s) {
	fprintf(stderr, "Erro sintatico: %s (%d)\n", s, yylineno);
	return 0;
}

int main() {
	yyparse();
	return 0;
}
