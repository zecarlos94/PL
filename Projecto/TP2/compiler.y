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
%type <str> declarations body statement args moreArgs value variable prints else expression parcel factor booleanExpression booleanFactor

%%

program : declarations START '{' body '}' END
        ;

declarations : /* EMPTY */
             | declarations variable ';'
             | declarations variable '=' atributions ';'
             ;

body : /* EMPTY */
     | body statement
     ;

statement : variable '=' expression ';'
          | variable '=' NAME '(' args ')' ';'
          | WHILE '(' booleanExpression ')' '{' body '}'
          | IF '(' booleanExpression ')' '{' body '}' else  
          | READ '(' variable ')' ';'
          | PRINT '(' prints ')' ';'
          ;

args : /* EMPTY */ 
     | moreArgs
     ;

moreArgs : value 
         | moreArgs ',' value 
         ;

value : NUMBER
      | variable
      ;

variable : NAME
         | NAME '[' expression ']'
         | NAME '[' expression ']' '[' expression ']'
         ;

prints : value
       | TEXT 
       ;

else : /* EMPTY */
     | ELSE '{' body '}'
     ;

expression : parcel
           | expression '+' parcel 
           | expression '-' parcel
           ;

parcel : parcel '*' factor
       | parcel '/' factor
       | parcel '%' factor
       | factor
       ;

factor : value
       | '(' expression ')'
       ;

booleanExpression : booleanExpression AND booleanFactor
                  | booleanExpression OR booleanFactor
                  | booleanFactor
                  ;

booleanFactor : expression '=' expression
              | expression '!' expression
              | expression '<' expression
              | expression '>' expression
              | '(' booleanExpression ')'
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
