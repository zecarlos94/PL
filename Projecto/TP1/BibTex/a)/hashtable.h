#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 31
#define KEYTYPE_SIZE 30
#define EMPTY 0
#define DELETED -1
#define FULL 1

//Open  Addressing - Linear Probing (insertTable) and Quadratic Probing (insertTable2)
//After hash_function calculated the position if it is not available it try insert in the next position with
//label "empty" or "deleted". "deleted" is required when retrieving data only stops when founds "empty"

typedef char Keytype[KEYTYPE_SIZE];
typedef void *Info;
typedef struct entry{
  int state;
  Keytype key;
  Info info;
}Entry;

typedef Entry* HashTable[HASHSIZE];

int hash_function(Keytype key);
void initializeTable(HashTable ht);
void clearTable(HashTable ht);
void insertTable(HashTable ht, Keytype k, Info i);
int retrieveTable(HashTable ht,Keytype k);
void deleteTable(HashTable ht, Keytype k);
void printHashTable(HashTable ht);
