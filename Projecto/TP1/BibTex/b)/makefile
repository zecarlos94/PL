all : flex gcc res

flex :
	flex prettybibtex.l 

gcc :
	gcc lex.yy.c prettybibtex.c -lfl

res:
	./a.out < lpbib.txt > resultado.txt
