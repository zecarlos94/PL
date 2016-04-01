#ifndef LISTA_H

#define LISTA_H

typedef struct grafo_autores {
	char *author;
	int num;
	struct grafo_autores *next;
} GA;

typedef struct grafo_autores *GRAPH;

void insert(GRAPH g, char *author);
void getAutores(GRAPH autores, GRAPH linha, char *author);

#endif
