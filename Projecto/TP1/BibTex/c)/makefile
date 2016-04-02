all: flexTree compileTree execTree createGraph

flexTree:
	flex tp1C.fl

compileTree:
	gcc lex.yy.c lista.c -ll -o tp1C

execTree:
	./tp1C < graphTeste.txt $(ARGS)

createGraph:
	dot -Tpng graph.dot > fig.png

 
