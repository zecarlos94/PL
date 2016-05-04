#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"

GRAPH insert(GRAPH g, char *author) {
	if(g == NULL) { 
		g = (GRAPH) malloc(sizeof(struct grafo_autores));
		g->author = strdup(author);
		g->num = 1;
		g->next = NULL;
	}
	else if(strncmp(author, g->author, strlen(author)) == 0) g->num++;
	else g->next = insert(g->next, author);
	return g;
}

GRAPH getAutores(GRAPH autores, GRAPH linha, char *author) {
	GRAPH aux = linha;
	while(aux != NULL) {
		if(strncmp(author, aux->author, strlen(author)) == 0) {
			aux = linha;
			while(aux != NULL) {
				if(strncmp(author, aux->author, strlen(author)) != 0) autores = insert(autores, aux->author);
				aux = aux->next;
			} 
			break;
		}
		else aux = aux->next;
	}
	return autores;
}
