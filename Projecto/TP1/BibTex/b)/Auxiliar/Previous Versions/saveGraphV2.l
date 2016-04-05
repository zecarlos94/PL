%{

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"

char *author;
GRAPH autores;

 GRAPH linha; autores = NULL; 
 // author = strdup("Tim Nicholson"); autores = insert(autores, author);
void printAutores();

%}

%%

%x AUTOR

author[ ]*\=[ ]*[{"] {linha = NULL; BEGIN AUTOR;}
<AUTOR>[\t" "\n]+ {/* Limpa elementos de formatação */ }
<AUTOR>[^\t\n]*/"\}," { /*Ultimo nome*/
char *authorName = strdup(yytext); 
linha = insert(linha, autorLinha);}
<AUTOR>"\},\n" { /* Caso de paragem*/
autores = getAutores(autores, linha, author); 
BEGIN INITIAL;}
<AUTOR>[^\t\n]+ { 
char *authorName = strdup(yytext); 
linha = insert(linha, autorLinha);
}
.|\n                                    {}
<*><<EOF>>                              {printAutores(); free(linha); free(autores); return 0;}

%%

void printLinha(GRAPH linha) {
        while(linha != NULL) {
                printf("\n%s\n", linha->author);
                linha = linha->next;
        }
}

void printAutores() {
        FILE *fp = fopen("graph.dot", "w");
        GRAPH aux = autores;
        fprintf(fp, "digraph finite_state_machine {\n");
        fprintf(fp, "   rankdir=LR;\n");
        fprintf(fp, "   size=\"20,20\"\n");
        while(aux != NULL) {
                fprintf(fp, "node [shape = circle];");
                fprintf(fp, " \"%s\" ", aux->author);
                aux = aux->next;
        }
        aux = autores;
        while(aux != NULL) {
                if(strncmp(author, aux->author, strlen(author)) == 0) fprintf(fp, "\n\"%s\"", author);
                else fprintf(fp, " -> \"%s\" [label = \"%d\"];", aux->author, aux->num);
                aux = aux->next;
        }
        fprintf(fp, "\n}");
        fclose(fp);
}

int main() {
        int s;
        s=yylex();
        while(s){printf("%d",s);s=yylex();}
        return 0;
}


