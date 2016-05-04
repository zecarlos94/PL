
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "prettybibtex.h"

Registo initRegisto(){
        Registo reg = malloc( sizeof(struct registo));
        reg->r = 0;reg->iautores = 0;
        reg->autores = malloc( 30 * sizeof(char*));
        int k;
        int n = MAX_NUMBER_CAMPS;

        reg->campos = malloc( n * (sizeof(Campo)));
        for(k=0; k < n ;k++)
                reg->campos[k] = malloc(sizeof(struct campo));
        return reg;
}

void orderCampos(Registo reg){
        int j,k, t = -1; /* index a author t title */
        for(j = 0; j < reg->r ; j++){
                char* valor = (reg->campos[j]->nome);
                for(k = 0; valor[k] != '\0' ; k++ )
                        valor[k] = tolower(valor[k]);

                if( strcmp(valor,"title") == 0 ) {t = j; break;}
        }
        if( t > 0){
                        Campo sub = reg->campos[0];
                        reg->campos[0] = reg->campos[t];
                        reg->campos[t] = sub;
                }
}

void printRegisto(Registo reg){
        int k;
        orderCampos(reg);
        printf("@%s{%s,\n",reg->categoria,reg->chave);
        if(reg->autores != NULL && reg->iautores > 0)
           if(reg->iautores == 1)
                 printf("    author = {%s},\n",reg->autores[0]);
            else{
              printf("    author = {%s\n",reg->autores[0]);
              for(k= 1; k < reg->iautores - 1; k++)
                printf("\t      %s\n",reg->autores[k]);
              printf("\t      %s},\n",reg->autores[k]);
            }

        for(k = 0; k < (reg->r - 1) ; k++)
                printf("    %s = %s,\n",reg->campos[k]->nome,reg->campos[k]->valor);

        printf("    %s = %s\n",reg->campos[reg->r - 1]->nome,reg->campos[reg->r-1]->valor);
        printf("}\n");
        free(reg); reg = NULL;
}

int first(char* s,char c ){
        int t;
        for(t = 0; s[t]!='\0'; t++)
                if( s[t]== c) break;
        return t;
}

