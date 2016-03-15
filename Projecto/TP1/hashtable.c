#include "hashtable.h"


int hash_function(Keytype key){
  int i=0,sum=0;
  for(;i<KEYTYPE_SIZE-1;i++){ //ends with '\0' so we must subtract one iteration corresponding to that char
    sum+=key[i];
  }
  return (sum%HASHSIZE);
}

void initializeTable(HashTable ht){
  int i=0;
  for(;i<HASHSIZE;i++){
    Entry* new = (Entry*) malloc(sizeof(struct entry));
    new->state=EMPTY;
    strncpy(new->key,"Empty",KEYTYPE_SIZE);
    new->info=NULL;
    ht[i]=new;
  }
}

void clearTable(HashTable ht){
  int i=0;
  for(;i<HASHSIZE;i++) free(ht[i]);
}

void insertTable(HashTable ht, Keytype k, Info i){
  int position=hash_function(k);
  int found=retrieveTable(ht,k);
  if(found!=0){ // k já existe
    ht[found]->info=ht[found]->info + 1;
  }
  else{ //k não existe
  if(ht[position]->state!=FULL){
    strncpy(ht[position]->key,k,KEYTYPE_SIZE);
    ht[position]->info=i;
    ht[position]->state=FULL;
  }
  else{
    //try to insert in the next and so on --- Linear Probing
    while(ht[position]->state==FULL) position=(position+1)%HASHSIZE;
    //it founded an EMPTY or DELETED
    strncpy(ht[position]->key,k,KEYTYPE_SIZE);
    ht[position]->info=i;
    ht[position]->state=FULL;
  }
  }
}

//retrieving with linear probing from the initial position
int retrieveTable(HashTable ht,Keytype k){
  int position=hash_function(k);
  Entry* aux;
  int res=0;
  for(;ht[position]->state!=EMPTY && position<HASHSIZE;position=(position+1)%HASHSIZE){
    if(strncmp(ht[position]->key,k,KEYTYPE_SIZE)==0){
      aux=ht[position];res=position;
    }
  }
  return res;
}

void deleteTable(HashTable ht, Keytype k){
  int position=hash_function(k),i=0;
  for(;ht[position]->state!=EMPTY && i<HASHSIZE;i++){
    if(strncmp(ht[position]->key,k,KEYTYPE_SIZE)==0){
      ht[position]->state=DELETED;
      strncpy(ht[position]->key,"Deleted",KEYTYPE_SIZE);
      ht[position]->info=NULL;
    }
  }
}

void printHashTable(HashTable ht){
  int i=0;
  Entry* aux;
  FILE * fp = fopen("index.html","wr");
  fprintf(fp,"<HMTL>\n\t<BODY>\n");
  for(;i<HASHSIZE;i++){
    aux=ht[i];
    if(aux->state!=EMPTY && aux->state!=DELETED){
      fprintf(fp,"\t\t<li>Categoria: %s, Contagem: %d\n",aux->key,(int) aux->info);
    }
  }
  fprintf(fp,"\t<BODY/>\n<HTML/>");
}
