all: flexParsing compileParsing execParsing createGraph

flexParsing:
	flex parsing.fl

compileParsing:
	gcc lex.yy.c lista.c -ll -o parsing

execParsing:
	./parsing < lp.bib 

createGraph:
	dot -Tpng graph.dot > fig.png

 
