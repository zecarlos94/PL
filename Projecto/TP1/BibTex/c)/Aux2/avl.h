#ifndef AVL_H

#define AVL_H

typedef enum balancefactor {LH, EH, RH} BalanceFactor;

typedef struct avl_node {
        BalanceFactor bf;       
        char* author; 
	int num;
        struct avl_node *left, *right;
} AVL_node;

typedef struct avl_node* AVL;

typedef struct authors_line {
	char *author;
	struct authors_line *next;
} AUT_LINE;

typedef struct authors_line* AUTS;

AVL insert(AVL p, char* author, int *cresceu);
void insertAVL(AVL a, char* author);
void addAuthors(AVL avl, char* author, AUTS authorsLine);

#endif
