all: flexParsing compileParsing execParsing flexTree compileTree execTree createGraph

flexParsing:
	flex parsing.fl

compileParsing:
	gcc lex.yy.c -ll -o parsing

execParsing:
	./parsing < lp.bib > parsedFile.txt

flexTree:
	flex saveTree.fl

compileTree:
	gcc lex.yy.c avl.c -ll -o saveTree

execTree:
	./saveTree < parsedFile.txt

createGraph:
	dot -Tpng graph.dot > fig.png

 
