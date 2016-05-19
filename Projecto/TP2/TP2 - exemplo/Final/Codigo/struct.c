#include "struct.h"

struct variavel* insertVariavel(struct variavel *variavel, struct variavel *listaVariaveis)
{
	struct variavel *ant=NULL,*pt=listaVariaveis,*aux=variavel;

	while(pt && pt->nome && strcmp(variavel->nome,pt->nome)>=0)
	{
		ant = pt;
		pt = pt->next;
	}

	if(!ant)
	{
		aux->next = listaVariaveis;
		return aux;
	}
	else
	{
		aux->next = pt;
		ant->next = aux;
		return listaVariaveis;
	}
}

int existeVariavel(char *variavel, struct variavel *listaVariaveis)
{
	struct variavel *pt=listaVariaveis;
	int res = 0;
	
	while(pt && pt->nome && strcmp(variavel,pt->nome)>=0)
	{
		if(strcmp(variavel,pt->nome)==0) 
			res = 1;
		pt = pt->next;
	}

	return res;
}

int enderecoVariavel(char *variavel, struct variavel *listaVariaveis)
{
	struct variavel *pt=listaVariaveis;
	int res = -1;
	
	while(pt && pt->nome && strcmp(variavel,pt->nome)>=0)
	{
		if(strcmp(variavel,pt->nome)==0) 
			res = pt->endereco;
		pt = pt->next;
	}

	return res;
}

char* tipoVariavel(char *variavel, struct variavel *listaVariaveis)
{
	struct variavel *pt=listaVariaveis;
	char* res = NULL;
	
	while(pt && pt->nome && strcmp(variavel,pt->nome)>=0)
	{
		if(strcmp(variavel,pt->nome)==0) 
			res = pt->tipo;
		pt = pt->next;
	}

	return res;
}

void inicializaVariavel(char *variavel, struct variavel *listaVariaveis)
{
	struct variavel *pt=listaVariaveis;	

	while(pt && pt->nome && strcmp(variavel,pt->nome)>=0)
	{
		if(strcmp(variavel,pt->nome)==0) 
			pt->inicializado = 1;
		pt = pt->next;
	}
}

int variavelInicializada(char *variavel, struct variavel *listaVariaveis)
{
	struct variavel *pt=listaVariaveis;
	int res = 0;
	
	while(pt && pt->nome && strcmp(variavel,pt->nome)>=0)
	{
		if(strcmp(variavel,pt->nome)==0) 
			res = pt->inicializado;
		pt = pt->next;
	}

	return res;
}