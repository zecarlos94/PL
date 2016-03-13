%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Categorias todas unidas!!
int i;//substring
int j;
int end=0;//arrays
int count[1000];
char* categories[1000];
%}
%%

^\@[a-z]* {
            char category[10000];
            for(i=1;yytext[i]!='{';i++);
            strncpy(category, yytext + 1, i - 0);
            for(j=0;j<=end;j++){
              if(categories[j]!=category){end++;categories[end]=category;count[end]=1;}
              else{count[j]++;}
            }

            for(j=1;j<=end;j++){
              printf("%s\t",categories[j]);
              printf("%d\n",count[j]);
            }
          }

%%
