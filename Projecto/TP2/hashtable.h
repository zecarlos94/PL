#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 31
#define KEYTYPE_SIZE 30
#define MAXSIZE 100

#define EMPTY 0
#define FULL 1

typedef char Keytype[KEYTYPE_SIZE];

typedef struct entry {
	int state;
	Keytype var;	// Nome da variável
  	char *type; 	// Tipo da variável (int, array ou matrix)
	int nLines;	// Número de linhas do values
	int nCols;	// Número de colunas do values
	int stackIndex; // Endereço da variável na stack da VM
} Entry;

typedef Entry* HashTable[HASHSIZE];

typedef struct list {
	char *instruction;
	int addr;
	struct list *next;
} L;

typedef struct list *List;

int hash_function(Keytype var);
HashTable initializeTable(HashTable ht)
HashTable insertTable(HashTable ht, Keytype var, char *type, int nLines, int nCols, int stackIndex);
int retrieveTable(HashTable ht, Keytype var);
List addInstruction(List l, int addr, char *ins);
int getVarIndex(HashTable ht, Keytype var);
char *getType(HashTable ht, Keytype var);
void printInstructions(List l);
