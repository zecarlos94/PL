%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
  #include "hashtable.h"
	HashTable ht;
	int count=1;
	int position=0;
%}



%%

@[a-zA-Z]+\{			{
                    char* str = (char *) malloc(sizeof(char)*1000);
						        strcpy(str,yytext+1);
						        str[yyleng-2] ='\0';
										insertTable(ht, str, (int *)count);
						      }

.|\n							{}




%%
int main(){
	initializeTable(ht);
	int s;
  s=yylex();
	while(s){printf("%d",s);s=yylex();}
	printHashTable(ht);
	printf("\n");
	return 0;
}
