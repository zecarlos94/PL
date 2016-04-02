%{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
/*
	Idente cada Campo,
	Um autor por linha,
	Colocar no inicio os campos "author title"
*/

#define CAMP_BUFFER_SIZE 10000
#define MAX_NUMBER_CAMPS 50
#define NAMES_BUFFER 100

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

Registo registo;


Registo initRegisto(){
	Registo reg = malloc( sizeof(struct registo));
	reg->r = 0;reg->iautores = 0;
	reg->autores = malloc( 30 * sizeof(char*));
	int k;
	int n = MAX_NUMBER_CAMPS;
	
	reg->campos = malloc( n * (sizeof(Campo)));	
	for(k=0; k < n ;k++)
		reg->campos[k] = malloc(sizeof(struct campo));
	return reg;
}

void orderCampos(Registo reg){
	int j,k, t = -1; /* index a author t title */
	for(j = 0; j < reg->r ; j++){
		char* valor = (reg->campos[j]->nome);
		for(k = 0; valor[k] != '\0' ; k++ )
			valor[k] = tolower(valor[k]);

		if( strcmp(valor,"title") == 0 ) {t = j; break;}
	}
	if( t > 0){
			Campo sub = reg->campos[0];
			reg->campos[0] = reg->campos[t];
			reg->campos[t] = sub;
		}

}

char *trim(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}
        
void printRegisto(Registo reg){
	int k;
	orderCampos(reg);
	printf("@%s{%s,\n",reg->categoria,reg->chave);
	if(reg->autores != NULL && reg->iautores > 0)
           if(reg->iautores == 1) 
		 printf("    author = {%s},\n",reg->autores[0]);
	    else{
	      printf("    author = {%s\n",reg->autores[0]);
              for(k= 1; k < reg->iautores - 1; k++) 
		printf("\t      %s\n",reg->autores[k]);
	      printf("\t      %s},\n",reg->autores[k]);
            }	

	for(k = 0; k < (reg->r - 1) ; k++)
		printf("    %s = %s,\n",reg->campos[k]->nome,reg->campos[k]->valor);	

	printf("    %s = %s\n",reg->campos[reg->r - 1]->nome,reg->campos[reg->r-1]->valor);	
	printf("}\n");
	free(reg); reg = NULL;
}


void p(){printf("%s",yytext);}

int first(char* s,char c ){
	int t;
	for(t = 0; s[t]!='\0'; t++)
		if( s[t]== c) break;
	return t;
}

char apelido[20];
char primeiroNome[3]; // SEmpre {[A-Z],., }
int nomeCompleto = 0;
int temApelido = 0;

int formato2 = 0; // Formato dos nomes Apelido, nomes and ...

int primeiroNomeParsed = 0; // Usado para o formato classico

int it1 = 0;
int it2 = 0;
int chavetaAberta = 0;
%}

%x AUT AUTTESTE1NOME CHAVE CATEGORIA CAMPOS NOMECAMPO SEPARADORCAMPO VALORCAMPO VALORCAMPOT1 VALORCAMPOT2 SCANNOME

%%
<INITIAL>@[Ss][Tt][Rr][Ii][Nn][Gg] { p();}
<INITIAL>@ {
registo = initRegisto();
BEGIN CATEGORIA;}
<INITIAL>.|\n {p();}
<CATEGORIA>[a-zA-Z]* {registo->categoria = strdup(yytext); BEGIN CHAVE;}
<CHAVE>[{ ]* {}
<CHAVE>[A-Za-z0-9:]* {registo->chave = strdup(yytext);BEGIN CAMPOS;}
<CAMPOS>\} { printRegisto(registo); BEGIN INITIAL;}
<CAMPOS>[\n ]* {}
<CAMPOS>\,[\n ]* {BEGIN NOMECAMPO;}
<CAMPOS>\,[\n ]*\} { printRegisto(registo); BEGIN INITIAL;}
<NOMECAMPO>[ ]*[Aa][Uu][Tt][Hh][Oo][Rr][ ]*=[ ]*["{][ ]*["}] {/* Lista de Autores vazia */
registo->autores = NULL;
BEGIN CAMPOS;}
<NOMECAMPO>[ ]*[Aa][Uu][Tt][Hh][Oo][Rr][ ]*=[ ]*["{] { 
registo->iautores=0; 
temApelido = 0; nomeCompleto = 0; primeiroNomeParsed = 0;formato2=0;
BEGIN AUT; 	
}
<NOMECAMPO>[ ]*[Aa][Uu][Tt][Hh][Oo][Rr][ ]*=[ ]*["{][ ]*[^ ]+[ ]*["}]/, {
 int iAspas = first(yytext,'"');
 int iPar = first(yytext,'{'); int i1Token;
 if( iAspas < iPar) i1Token = iAspas; else i1Token = iPar;
 yytext[yyleng-1] = '\0';
 char* singleName = trim(yytext + i1Token + 1);
 registo->autores[registo->iautores++] = strdup(singleName);
 BEGIN CAMPOS;
} 
<NOMECAMPO>[ \n]* { }
<NOMECAMPO>[a-zA-Z-]* {registo->campos[registo->r]->nome = strdup(yytext);
BEGIN SEPARADORCAMPO; } 
<SEPARADORCAMPO>[ ]*=[ ]* { BEGIN VALORCAMPO;}
<AUTTESTE1NOME>[ ]+ {}
<AUTTESTE1NOME>\.  {BEGIN AUT;}
<AUTTESTE1NOME>[A-Za-z]+[ ]+["}]/, {
yytext[yyleng-1] = '\0';
registo->autores[registo->iautores++] = strdup(yytext);
BEGIN CAMPOS;
}
<AUT>[ ]+[Aa]nd[ ]+ {
//printf("AND\n"); 	
char* authorName = malloc(sizeof(char) * 30);
strcpy(authorName,primeiroNome); 
if(temApelido) strcpy(authorName + 3,apelido); 
registo->autores[registo->iautores++] = authorName;
// reinicializar as variaveis de controlo
temApelido = 0; nomeCompleto = 0; primeiroNomeParsed = 0;
} 
<AUT>("\""?"}"?),[ ]*\n { 
//printf("Paragem de author\n"); p();
char* authorName = malloc(sizeof(char) * 30);
strcpy(authorName,primeiroNome); 
if(temApelido) strcpy(authorName + 3,apelido); 
registo->autores[registo->iautores++] = authorName;
 BEGIN NOMECAMPO;
}
<AUT>([^ ,"]("\\\""?))+/, { /*identifica o formato Apelido, Nomes and .. */ formato2 = 1;
 //printf("Parsing apelido formato 2\n");p();
 strcpy(apelido,yytext);
 // apelido[yyleng] = '\0';
 nomeCompleto = 0;
 temApelido = 1;
}
<AUT>([^ ,"]("\\\""?))+ {
if(formato2 && !nomeCompleto){
 //	printf("parsing nome formato 2\n"); 
//	p();	
nomeCompleto = 1; // Apelido vem primeiro
	primeiroNome[0] = yytext[0];
	primeiroNome[1] = '.';
	primeiroNome[2] = ' ';
 }else if(!formato2){
   if(!primeiroNomeParsed){
 //	printf("parsing primeiro nome formato 1\n");
//p();
	primeiroNome[0] = yytext[0];
	primeiroNome[1] = '.';
	primeiroNome[2] = ' ';	
   	primeiroNomeParsed = 1;
	temApelido = 0;
   }else{
	/* coloca todos os nomes da pessoa com exceção do primeiro no apelido
	 como o apelido é o ultimo nome neste formato o ultimo nome vai 
	 sobrepor os outros */
//	printf("Parsing possivel apelido\n");
//	p();
	temApelido = 1;
	strcpy(apelido,yytext); apelido[yyleng] = '\0';
	if(apelido[yyleng-1] == '}') apelido[yyleng-1] = '\0';
   }	
 }
}
<AUT>.|\n { 
/* Em principio so limpa espaços e virgulas no caso da formataçao 2 */ }
<VALORCAMPO>[a-zA-Z0-9]+ { registo->campos[registo->r++]->valor= strdup(yytext);  BEGIN CAMPOS;}  
<VALORCAMPO>\" {registo->campos[registo->r]->valor = malloc( CAMP_BUFFER_SIZE * sizeof(char));
it1 = 0; registo->campos[registo->r]->valor[it1++] = '{';  
BEGIN VALORCAMPOT1;}
<VALORCAMPO>\{ {
chavetaAberta = 1;
registo->campos[registo->r]->valor = malloc( CAMP_BUFFER_SIZE * sizeof(char));
it2 = 0;
registo->campos[registo->r]->valor[it2++] = '{';  
BEGIN VALORCAMPOT2; }
<VALORCAMPOT1>\\\" {
registo->campos[registo->r]->valor[it1++] = yytext[0];
registo->campos[registo->r]->valor[it1++] = yytext[1];
}
<VALORCAMPOT1>\" { 
registo->campos[registo->r]->valor[it1++] = '}';
registo->campos[registo->r++]->valor[it1++] = '\0';
BEGIN CAMPOS;  
}
<VALORCAMPOT1>.|\n  {
registo->campos[registo->r]->valor[it1++] = yytext[0];
} 

<VALORCAMPOT2>\{ {
chavetaAberta++;
registo->campos[registo->r]->valor[it2++] = '{';  
}
<VALORCAMPOT2>\} {
chavetaAberta--;
if(chavetaAberta == 0){
registo->campos[registo->r]->valor[it2++] = '}';  
registo->campos[registo->r++]->valor[it2++] = '\0';  
BEGIN CAMPOS;
}else{
	registo->campos[registo->r]->valor[it2++] = '}';  
	}
}
<VALORCAMPOT2>.|\n  {
registo->campos[registo->r]->valor[it2++] = yytext[0];
} 
%%
/**
*

<AUT>([^ ,"]("\""?))* {
printf("Apenas 1 nome\n");p(); 
// Caso a entrada author tenha apenas um nome 
if(yytext[yyleng-1] == '}') yytext[yyleng-1] = '\0';
strcpy(registo->autores[registo->iautores++],yytext);
BEGIN NOMECAMPO;
} 



	name[0] = "[A-Z].*"
	name[i-1] = "[A-Za-z]*"

	return [A-Z]". "[A-Za-z]*
<AUT>[ ]* {  guardar nome }
<AUT>[^ ,] { // name[i++][ic++] = yytext[0];  
BEGIN AUTVIRGULA; }
<AUT>[\"}], {authorName = formatName(name); 
	     registo->autores[registo->iautores++] = strdup(authorName);
             BEGIN NOMECAMPO;}
<AUT>[^ "}]* {name[i++] = strdup(yytext); }
*/

int main(){
  	int s;
  	s=yylex();
        while(s){printf("%d",s);s=yylex();}
	return 0;
}
