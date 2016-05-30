all: compiler

compiler: compiler.fl compiler.y 
	flex compiler.fl
	yacc compiler.y
	gcc y.tab.c -o compiler
