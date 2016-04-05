%{

%}

%x AUTOR
%%
author[ ]*\=[ ]*[{"] {BEGIN AUTOR;}
<AUTOR>[\t" "\n]+ {/* Limpa elementos de formatação */ }
<AUTOR>[^\t\n]*/"\}," { ECHO; printf("\n");} 
<AUTOR>"\},\n" { /* Caso de paragem*/ BEGIN INITIAL;}
<AUTOR>[^\t\n]* {ECHO; printf("\n");}
.|\n {}
%%

/*
*/
int main() {
        int s;
        s=yylex();
        while(s){printf("%d",s);s=yylex();}
        return 0;
}


