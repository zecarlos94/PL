#include "hashtable.h"

int hash_function(Keytype var) {
	int i = 0, sum = 0;
  	for(; i < KEYTYPE_SIZE - 1; i++) sum+=var[i];
  	return(sum % HASHSIZE);
}

HashTable initializeTable(HashTable ht) {
	int i = 0;
  	for(; i < HASHSIZE; i++) {
    		Entry* new = (Entry*) malloc(sizeof(struct entry));
    		new->state = EMPTY;
    		strncpy(new->var, "Empty", KEYTYPE_SIZE);
    		new->type = strdup("Empty");
    		new->nLines = 0;
		new->nCols = 0;
		new->stackIndex = -1;
    		ht[i]=new;
  	}
	return ht;
}

HashTable insertTable(HashTable ht, Keytype var, char *type, int nLines, int nCols, int stackIndex) {
	int position = hash_function(var);
  	int found = retrieveTable(ht, var);
  	if(found == 0) {
  		if(ht[position]->state != FULL) {
			ht[position]->state=FULL;
    			strncpy(ht[position]->var, var, KEYTYPE_SIZE);
    			memset(ht[position]->type);
    			ht[position]->type = strdup(type);
			ht[position]->nLines = nLines;
			ht[position]->nCols = nCols;
			ht[position]->stackIndex = stackIndex;
		}
  	}
 	else {
    		while(ht[position]->state == FULL) position = (position + 1) % HASHSIZE;
    		ht[position]->state=FULL;
    		strncpy(ht[position]->var, var, KEYTYPE_SIZE);
    		memset(ht[position]->type);
    		ht[position]->type = strdup(type);
		ht[position]->nLines = nLines;
		ht[position]->nCols = nCols;
		ht[position]->stackIndex = stackIndex;
  	}
	return ht;
}

// Retrieving with linear probing from the initial position
int retrieveTable(HashTable ht, Keytype var) {
	int position = hash_function(var);
  	Entry* aux;
  	int res = 0;
  	for(; ht[position]->state != EMPTY && position < HASHSIZE; position = (position + 1) % HASHSIZE) {
    		if(strncmp(ht[position]->var, var, KEYTYPE_SIZE) == 0) {
      			aux = ht[position];
			res = position;
    		}
 	}
  	return res;
}

List addInstruction(List l, int addr, char *ins) {
	if(l == NULL) {
		l = (List) malloc(sizeof(struct list));
		l->instruction = strdup(ins);
		l->addr = addr;
		l->next = NULL;
	}
	else l->next = addInstruction(l->next, addr, ins);
	return l;
}

int getVarIndex(HashTable ht, Keytype var) {
	int position = hash_function(var);
  	Entry* aux;
  	int res = 0;
  	for(; ht[position]->state != EMPTY && position < HASHSIZE; position = (position + 1) % HASHSIZE) {
    		if(strncmp(ht[position]->var, var, KEYTYPE_SIZE) == 0) {
      			aux = ht[position];
			res = aux->stackIndex;
    		}
 	}
  	return res;
}

char *getType(HashTable ht, Keytype var) {
	int position = hash_function(var);
  	Entry* aux;
  	char *res;
  	for(; ht[position]->state != EMPTY && position < HASHSIZE; position = (position + 1) % HASHSIZE) {
    		if(strncmp(ht[position]->var, var, KEYTYPE_SIZE) == 0) {
      			aux = ht[position];
			res = strdup(aux->type);
    		}
 	}
  	return res;
}

void printInstructions(List l) {
	while(l != NULL) printf("%s", l->instruction);
}
