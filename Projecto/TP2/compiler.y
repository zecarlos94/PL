%{

#define _GNU_SOURCE

#define NO  0
#define COL 1
#define LIN 2

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

int yylex();
int yyerror(char *);

HashTable ht;			// Id table
List ins = NULL;		// Instruction list
int sp = 0;			// Stack pointer
int addr = 0;			// Number of instruction index

%}

%union {
	int num;
	char *str;
}

/* Terminal symbols */
%token <num> NUMBER
%token <str> NAME TEXT 
%token AND OR EQLS DIFF SMEQ GTEQ
%token START END WHILE IF READ PRINT ELSE

/* Non-terminal symbols */
/*%type <str> Declarations Body Statement Args MoreArgs Value Prints Else Parcel Factor BooleanExpression BooleanFactor
%type <num> Expression*/

%%

Program : Declarations {ins = addInstruction(ins, sp, "start");} START Body {ins = addInstruction(ins, sp, "stop");} END {printInstructions(ins);}
        ;

Declarations : /* EMPTY */						{ht = initializeTable(ht);}										
             | Declarations NAME ';'					{
										char *var = strdup($2);
										char *type = strdup("int");
										if(retrieveTable(ht, var) != 0) {
											char *error;
											sprintf(error, "variable %s already exists", $2);
											yyerror(error);
										}
										else {
											char buf[50];
											ht = insertTable(ht, var, type, 0, 1, sp);
											sprintf(buf, "pushi 0\n");		
											ins = addInstruction(ins, addr++, buf);
										}
									}
	     | Declarations NAME '[' NUMBER ']'	';'			{
										char *var = strdup($2);
										char *type = strdup("array");
										if(retrieveTable(ht, var) != 0) {
											char *error;
											sprintf(error, "variable %s already exists", $2);
											yyerror(error);
										}
										else {
											char buf[50];
											ht = insertTable(ht, var, type, 0, $4, sp);
											sprintf(buf, "pushn %d\n", $4);		
											ins = addInstruction(ins, addr++, buf);
											sp += $4;
										}
									}
             | Declarations NAME '[' NUMBER ']' '[' NUMBER ']' ';'	{
										char *var = strdup($2);
										char *type = strdup("matrix");
										if(retrieveTable(ht, var) != 0) {
											char *error;
											sprintf(error, "variable %s already exists", $2);
											yyerror(error);
										}
										else {
											char buf[50];
											ht = insertTable(ht, var, type, $4, $7, sp);
											sprintf(buf, "pushn %d\n", $4 * $7);		
											ins = addInstruction(ins, addr++, buf);
											sp += $4 * $7;
										}
									}						
             ;

Body : /* EMPTY */								
     | Body Statement								
     ;

Statement : NAME '=' Expression ';'						{
											char *var = strdup($1);
											if(retrieveTable(ht, var) != 0) {
												char *type = getType(var);
												if(strcmp(type, "int") != 0) {
													char buf[50];
													int varIndex = getVarIndex(ht, var);
													sprintf(buf, "storeg %d", varIndex);
													ins = addInstruction(ins, addr++, buf);
												}
												else {
													char *error;
													sprintf(error, "variable %s is not an integer", var);
													yyerror(error);
												}
											}
											else {
												char *error;
												sprintf(error, "variable %s is not declared", var);
												yyerror(error);
											}
										}
          | NAME '[' Expression ']' '=' Expression ';'				
          | NAME '[' Expression ']' '[' Expression ']' '=' Expression ';'
          | WHILE '(' BooleanExpression ')' '{' Body '}'			
          | IF '(' BooleanExpression ')' '{' Body '}' Else  	
          | READ '(' Value ')' ';'				
          | PRINT '(' Prints ')' ';'				
          ;

Prints : Value	
       | TEXT 	
       ;

Else : /* EMPTY */		
     | ELSE '{' Body '}'	
     ;

Expression : Parcel			
           | Expression '+' Parcel 	{
						char buf[50];
						sprintf(buf, "add\n");
						ins = addInstruction(ins, addr++, buf);
					}
           | Expression '-' Parcel	{
						char buf[50];
						sprintf(buf, "sub\n");
						ins = addInstruction(ins, addr++, buf);
					}
           ;

Parcel : Parcel '*' Factor		{
						char buf[50];
						sprintf(buf, "mul\n");
						ins = addInstruction(ins, addr++, buf);
					}
       | Parcel '/' Factor		{
						char buf[50];
						sprintf(buf, "div\n");
						ins = addInstruction(ins, addr++, buf);
					}
       | Parcel '%' Factor		{
						char buf[50];
						sprintf(buf, "mod\n");
						ins = addInstruction(ins, addr++, buf);
					}
       | Factor
       ;

Factor : NUMBER				{
						char buf[50];
						sprintf(buf, "pushi %d\n", $1);
						ins = addInstruction(ins, addr++, buf);
					}
       | Value
       | NAME '(' Args ')'
       | '(' Expression ')'
       ;

Value : NAME						{
								char *var = strdup($1);
								if(retrieveTable(ht, var) != 0) {
									char *type = getType(var);
									if(strcmp(type, "int") == 0) {
										char buf[50];
										int varIndex = getVarIndex(ht, var);
										sprintf(buf, "pushg %d", varIndex);
										ins = addInstruction(ins, addr++, buf);
									}
									else {
										char *error;
										sprintf(error, "variable %s is not an integer", var);
										yyerror(error);
									}
								}
								else {
									char *error;
									sprintf(error, "variable %s is not declared", var);
									yyerror(error);
								}
							}										     				
      | NAME '[' Expression ']'															
      | NAME '[' Expression ']' '[' Expression ']'												
      ;

Args : /* EMPTY */ 
     | MoreArgs
     ;

MoreArgs : Value 
         | MoreArgs ',' Value 
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

int main(int argc, char *argv[]) {
	yyparse();
	return 0;
}
