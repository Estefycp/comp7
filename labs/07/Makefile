all:
	lex compiler.l
	yacc -d syntax-calc.y
	gcc lex.yy.c y.tab.c -o syntax-calc

clean:
	rm lex.yy.c y.tab.c y.tab.h syntax-calc