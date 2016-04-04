%{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "prettybibtex.h"

/*
	Idente cada Campo,
	Um autor por linha,
	Colocar no inicio os campos "author title"
*/

Registo registo;

// Variaveis para campos de token chaveta
int it2 = 0;
int chavetaAberta = 0;

char apelido[20];
char primeiroNome[3]; // SEmpre {[A-Z],., }
int nomeCompleto = 0;
int temApelido = 0;
int formato2 = 0; // Formato dos nomes Apelido, nomes and ...
int primeiroNomeParsed = 0; // Usado para o formato com AND

void formatAuthor(){
if(formato2 && !nomeCompleto){
 // parsing nome formato 2 
nomeCompleto = 1; // Apelido vem primeiro
	primeiroNome[0] = yytext[0];
	primeiroNome[1] = '.';
	primeiroNome[2] = ' ';
 }else if(!formato2){
   if(!primeiroNomeParsed){
 // parsing primeiro nome formato
	primeiroNome[0] = yytext[0];
	primeiroNome[1] = '.';
	primeiroNome[2] = ' ';	
   	primeiroNomeParsed = 1;
	temApelido = 0;
   }else{
	/* coloca todos os nomes da pessoa com exceção do primeiro no apelido
	 como o apelido é o ultimo nome neste formato o ultimo nome vai 
	 sobrepor os outros */
//	Parsing possivel apelido
	temApelido = 1;
	strcpy(apelido,yytext); apelido[yyleng] = '\0'; 
	if(apelido[yyleng-1] == '}') apelido[yyleng-1] = '\0';
   }	
 }
}

%}

%x AUT CHAVE CAMPOS NOMECAMPO VALORCAMPO VALORCAMPOT2 

%%
<INITIAL>@[Ss][Tt][Rr][Ii][Nn][Gg]\{ { ECHO;}
<INITIAL>@[A-Za-z]+\{ {
registo = initRegisto();
yytext[yyleng - 1] = '\0'; yytext+=1;
registo->categoria = strdup(yytext);
BEGIN CHAVE;}
<INITIAL>.|\n { ECHO;}
<*><EOF> { return 0;}
<CHAVE>[A-Za-z0-9:]+ {registo->chave = strdup(yytext);BEGIN CAMPOS;}
<CHAVE>.|\n {}
<CAMPOS>(","?)[\n \t]*\} { printRegisto(registo); BEGIN INITIAL;}
<CAMPOS>\,[\n \t]* {BEGIN NOMECAMPO;}
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
 char* singleName = yytext + i1Token + 1;
 registo->autores[registo->iautores++] = strdup(singleName);
 BEGIN CAMPOS;
} 
<NOMECAMPO>[ ]*=[ ]* { BEGIN VALORCAMPO;}
<NOMECAMPO>[a-zA-Z-]+ {registo->campos[registo->r]->nome = strdup(yytext);} 
<NOMECAMPO>[ \n\t]* { }
<AUT>[ ]+[Aa]nd[ ]+ {
char* authorName = malloc(sizeof(char) * 30);
strcpy(authorName,primeiroNome); 
if(temApelido) strcpy(authorName + 3,apelido); 
registo->autores[registo->iautores++] = authorName;
// reinicializar as variaveis de controlo
temApelido = 0; nomeCompleto = 0; primeiroNomeParsed = 0;
} 
<AUT>["}],[ ]*\n { 
// Paragem de author
char* authorName = malloc(sizeof(char) * 30);
strcpy(authorName,primeiroNome); 
if(temApelido) strcpy(authorName + 3,apelido); 
registo->autores[registo->iautores++] = authorName;
 BEGIN NOMECAMPO;
}
<AUT>([^ ,"\n]("\\\""?))+/"}," {
	formatAuthor();
}
<AUT>([^ ,"\n]("\\\""?))+/, { /*identifica o formato Apelido, Nomes and .. */ formato2 = 1;
// Parsing apelido formato 2
 strcpy(apelido,yytext);
 nomeCompleto = 0;
 temApelido = 1;
}
<AUT>([^ ,"\n]("\\\""?))+ {
	formatAuthor();
}
<AUT>.|\n { 
/* Em principio so limpa espaços e virgulas no caso da formataçao 2 */ }
<VALORCAMPO>[a-zA-Z0-9]+ { registo->campos[registo->r++]->valor= strdup(yytext);  BEGIN CAMPOS;}  
<VALORCAMPO>\"([^"]("\\\""?))*\" { yytext[yyleng -1] = '}'; yytext[0] = '{';
registo->campos[registo->r++]->valor = strdup(yytext);
BEGIN CAMPOS;}
<VALORCAMPO>\{ {
chavetaAberta = 1;
registo->campos[registo->r]->valor = malloc( CAMP_BUFFER_SIZE * sizeof(char));
it2 = 0;
registo->campos[registo->r]->valor[it2++] = '{';  
BEGIN VALORCAMPOT2; }
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

//int yywrap(){return 0;}

int main(){
  	int s;
        while(s = yylex()){printf("%d",s);}
	return 0;
}
