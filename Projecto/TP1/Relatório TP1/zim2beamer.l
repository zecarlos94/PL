%{
	#include <stdio.h>
	int firstSlide=0;
	FILE *fp;
%}
%%
^[=]{6}[ ]{1}[a-zA-Z0-9 ]+[ ]{1}[=]{6}		{
								if(firstSlide==0){
								fp=fopen("zim2beamer.tex","w");
								fprintf(fp,"%cdocumentclass{beamer}\n %chypersetup{pdfstartview={Fit}}\n %cusetheme{Madrid}\n",92,92,92);
								fprintf(fp,"%cusecolortheme{beaver}\n %cusepackage{pifont}\n %cusepackage{cancel}\n %cbegin{document}\n",92,92,92,92);
								fprintf(fp,"%ctitle[Teste Beamer]{The Real Deal}\n %csubtitle{Example of Beamer}\n",92,92);
								fprintf(fp,"%cauthor[Ze Carlos]\n",92);
								fprintf(fp,"{F.~Author %cinst{1} }\n %cinstitute[University of Minho]{\n %cinst{1}\n",92,92,92);
								fprintf(fp,"Department of Computer Science%c%c\n",92,92);
								fprintf(fp,"University of Minho\n}\n %cdate[PT 2016]{Try number 3, 2016}\n %csubject{Computer Science}\n",92,92);
								}
								yytext[yyleng-7]='\0';fprintf(fp,"\n%cbegin{frame}\n\t%cframetitle{%s}\n",92,92,yytext+7);firstSlide++;
																					}
^[=]{5}[ ]{1}[a-zA-Z0-9 ]+[ ]{1}[=]{5}		{
							if(firstSlide==0){
	 						fprintf(fp,"%cdocumentclass{beamer}\n %chypersetup{pdfstartview={Fit}}\n %cusetheme{Madrid}\n",92,92,92);
	 						fprintf(fp,"%cusecolortheme{beaver}\n %cusepackage{pifont}\n %cusepackage{cancel}\n %cbegin{document}\n",92,92,92,92);
	 						fprintf(fp,"%ctitle[Teste Beamer]{The Real Deal}\n %csubtitle{Example of Beamer}\n",92,92);
	 						fprintf(fp,"%cauthor[Ze Carlos]\n",92);
	 						fprintf(fp,"{F.~Author %cinst{1} }\n %cinstitute[University of Minho]{\n %cinst{1}\n",92,92,92);
	 						fprintf(fp,"Department of Computer Science%c%c\n",92,92);
	 						fprintf(fp,"University of Minho\n}\n %cdate[PT 2016]{Try number 3, 2016}\n %csubject{Computer Science}\n",92,92);
							}
							yytext[yyleng-6]='\0';fprintf(fp,"\n%cbegin{frame}\n\t%cframetitle{%s}\n",92,92,yytext+6);firstSlide++;
																					}
^[=]{4}[ ]{1}[a-zA-Z0-9 ]+[ ]{1}[=]{4}		{
							if(firstSlide==0){
	 					  fprintf(fp,"%cdocumentclass{beamer}\n %chypersetup{pdfstartview={Fit}}\n %cusetheme{Madrid}\n",92,92,92);
	 						fprintf(fp,"%cusecolortheme{beaver}\n %cusepackage{pifont}\n %cusepackage{cancel}\n %cbegin{document}\n",92,92,92,92);
	 						fprintf(fp,"%ctitle[Teste Beamer]{The Real Deal}\n %csubtitle{Example of Beamer}\n",92,92);
	 						fprintf(fp,"%cauthor[Ze Carlos]\n",92);
	 						fprintf(fp,"{F.~Author %cinst{1} }\n %cinstitute[University of Minho]{\n %cinst{1}\n",92,92,92);
	 						ffprintf(fp,"Department of Computer Science%c%c\n",92,92);
	 						fprintf(fp,"University of Minho\n}\n %cdate[PT 2016]{Try number 3, 2016}\n %csubject{Computer Science}\n",92,92);
	 						}
							yytext[yyleng-5]='\0';fprintf(fp,"\n%cbegin{frame}\n\t%cframetitle{%s}\n",92,92,yytext+5);firstSlide++;
																					}
\n\n\n                                    {fprintf(fp,"%cend{frame}\n",92);}
^[=]{3}[ ]{1}[a-zA-Z0-9 ]+[ ]{1}[=]{3}		{yytext[yyleng-4]='\0';fprintf(fp,"\n%s\n",yytext+4);}
^[=]{2}[ ]{1}[a-zA-Z0-9 ]+[ ]{1}[=]{2}		{yytext[yyleng-3]='\0';fprintf(fp,"\n%s\n",yytext+3);}
\{\{.*\}\}														  	{yytext[yyleng-2]='\0';fprintf(fp,"\n%cbegin{figure}[!ht]\n\t %ccentering\n\t %cincludegraphics[width=0.25 %ctextwidth]{%s} \n\t %ccaption{Atom}\n %cend{figure}\n",92,92,92,92,yytext+4,92,92);}
\*.+\*																		{yytext[yyleng-2]='\0';fprintf(fp,"%ctextbf{%s}\n",92,yytext+2);}
\_.+\_																		{yytext[yyleng-2]='\0';fprintf(fp,"\n%cunderline{%s}\n",92,yytext+2);}
[/]{2}[a-zA-z0-9 ]+[/]{2}									{yytext[yyleng-2]='\0';fprintf(fp,"\n%ctextit{%s}\n",92,yytext+2);}
[~]{2}[a-zA-z0-9 ]+[~]{2}									{yytext[yyleng-2]='\0';fprintf(fp,"\n%ccancel{%s}\n",92,yytext+2);}
[']{2}.+[']{2}														{yytext[yyleng-2]='\0';fprintf(fp,"\n%cend{frame}\n%cbegin{frame}[fragile]\n%cbegin{verbatim}\n%s\n%cend{verbatim}\n%cend{frame}\n",92,92,92,yytext+2,92,92);}
[0-9]\.[ A-Za-z0-9]+											{fprintf(fp,"\n%cbegin{itemize}\n\n%cbegin{itemize}\n%citem %s\n%cend{itemize}\n%cend{itemize}\n",92,92,92,yytext,92,92);}
[a-z]\.[ ]{1}[A-Za-z0-9]+									{fprintf(fp,"\n%cbegin{itemize}\n\n%cbegin{itemize}\n%citem %s\n%cend{itemize}\n%cend{itemize}\n",92,92,92,yytext,92,92);}
^[A-Z][A-Za-z0-9 \!]+											{fprintf(fp,"%s\n",yytext);}
\[[ ]\].*       													{fprintf(fp,"\n%cding{112} %s %cpar\n",92,yytext+4,92);}
.\[[ ]\].*       													{fprintf(fp,"%chspace{5ex}%cding{112} %s %cpar\n",92,92,yytext+4,92);}
.\[\*\].*     														{fprintf(fp,"%chspace{5ex}%cverb|%ccheckmark%s %cpar\n",92,92,92,yytext+4,92);}
\[\*\].*        													{fprintf(fp,"%cverb|%ccheckmark %s %cpar\n",92,92,yytext+4,92);}
\[[X|x]\].*    													  {fprintf(fp,"%cverb|%cxmark X %s %cpar\n",92,92,yytext+4,92);}
\n\*[ ]{1}[a-zA-Z0-9 ]+										{fprintf(fp,"\n%cbegin{itemize}\n%citem %s\n%cend{itemize}\n",92,92,yytext+3,92);}
.|\n																			{}
%%
int main(){
	int s;
  s=yylex();
	while(s){fprintf(fp,"%d",s);s=yylex();}
	fprintf(fp,"%cend{document}\n",92);
	fclose(fp);
	return 0;
}
