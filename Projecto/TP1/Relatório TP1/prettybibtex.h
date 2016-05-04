#ifndef PRETTYBIBTEX_H

#define PRETTYBIBTEX_H

#define CAMP_BUFFER_SIZE 1000
#define MAX_NUMBER_CAMPS 50

typedef struct campo{
  char* nome;
  char* valor;
}*Campo;

typedef struct registo{
  char* categoria;
  char* chave;
  char** autores;
  int iautores;
  Campo* campos;
  int r;
}*Registo;

Registo initRegisto();

void orderCampos(Registo reg);

void printRegisto(Registo reg);

int first(char* s,char c );

#endif
