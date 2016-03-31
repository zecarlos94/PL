#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"

AVL static insertRight(AVL p, char* author, int *cresceu);
AVL static insertLeft(AVL p, char* author, int *cresceu);
AVL static balanceRight(AVL p);
AVL static balanceLeft(AVL p);
AVL static rotateRight(AVL p);
AVL static rotateLeft(AVL p);

/* Insere um nodo na AVL */
AVL insert(AVL p, char* author, int *cresceu) {
	if(p == NULL) {
		p = (AVL) malloc(sizeof(struct avl_node));
		p->author = malloc(100 * sizeof(char));
		strcpy(p->author, author);
		p->num = 1;
		p->right = p->left = NULL;
		p->bf = EH;
		*cresceu = 1;
	}
	else {
		if(strncmp(author, p->author, strlen(author)) < 0) p = insertLeft(p, author, cresceu);
	     	else p = insertRight(p, author, cresceu);
	}
	return p;
}

/* Faz a insercao a direita na AVL */
AVL insertRight(AVL p, char* author, int *cresceu) {
	p->right = insert(p->right, author, cresceu);
	if(*cresceu) {
		switch(p->bf) {
			case LH:
				p->bf = EH;
				*cresceu = 0;
				break;
			case EH:
				p->bf = RH;
				*cresceu = 1;
				break;
			case RH:
				p = balanceRight(p);
				*cresceu = 0;
		}
	}
	return p;
}

/*Faz a insercao a esquerda na AVL*/
AVL insertLeft(AVL p, char* author, int *cresceu) {
	p->left = insert(p->left, author, cresceu);
	if(*cresceu) {
		switch(p->bf) {
			case RH:
				p->bf = EH;
				*cresceu = 0;
				break;
			case EH:
				p->bf=LH;
				*cresceu = 1;
				break;
			case LH:
				p = balanceLeft(p);
				*cresceu = 0;
		}
	}
	return p;
}

/* Balanceamento da AVL a direita */
AVL balanceRight(AVL p) {
	if(p->right->bf == RH) {
		p = rotateLeft(p);
		p->bf = EH;
		p->left->bf = EH;
	}
	else {
		p->right = rotateRight(p->right);
		p = rotateLeft(p);
		switch(p->bf) {
			case EH:
				p->left->bf = EH;
				p->right->bf = EH;
				break;
			case LH:
				p->left->bf = EH;
				p->right->bf = RH;
				break;
			case RH:
				p->left->bf = LH;
				p->right->bf = EH;
		}
		p->bf = EH;
	}
	return p;
}

/* Balanceamento da AVL a esquerda */
AVL balanceLeft(AVL p) {
	if(p->left->bf == LH) {
		p = rotateRight(p);
		p->bf = EH;
		p->right->bf = EH;
	}
	else {
		p->left = rotateLeft(p->left);
		p = rotateRight(p);
		switch(p->bf) {
			case EH:
				p->left->bf = EH;
				p->right->bf = EH;
				break;
			case RH:
				p->right->bf = EH;
				p->left->bf = LH;
				break;
			case LH:
				p->right->bf = RH;
				p->left->bf = EH;
		}
		p->bf = EH;
	}
	return p;
}

/* Rotacao da AVL a direita */
AVL rotateRight(AVL p) {	
	AVL aux;
	if((!p) || (!p->left)) printf("Erro!\n");
	else {
		aux = p->left;
		p->left = aux->right;
		aux->right = p;
		p = aux;
	}
	return p;
}

/* Rotacao da AVL a esquerda */
AVL rotateLeft(AVL p) {
	AVL aux;
	if((!p) || (!p->right)) printf("Erro!\n");
	else {
		aux = p->right;
		p->right = aux->left;
		aux->left = p;
		p = aux;
	}
	return p;
}

/* Verifica se o autor existe na AVL e caso exista incrementa o seu contador: 1-Existe, 0-Nao Existe */
AVL insertAVL(AVL a, char* author) {
	if(a == NULL) {
		int *cresceu = malloc(sizeof(int));
		a = insert(a, author, cresceu);
	}
	else if(strcmp(author, a->author) == 0) a->num++;
	else if(strcmp(author, a->author) < 0) a->left = insertAVL(a->left, author);
	else a->right = insertAVL(a->right, author);
	return a;
}

AVL addAuthors(AVL avl, char* author, AUTS authorsLine) {
	AUTS aux = authorsLine;
	while(aux != NULL) {
		if(strncmp(author, aux->author, strlen(author)) == 0) {
			aux = authorsLine;
			while(aux != NULL) {
				if(strncmp(author, aux->author, strlen(author)) != 0) avl = insertAVL(avl, aux->author);
			}
			break;
		}
		aux = aux->next;
	}
	return avl;
}
