all:
	lex compiler.l
	gcc lex.yy.c -o lexic_analyzer -ll
	javac GramarAnalyser.java
	gcc syntax-calc.c -o syntax-calc

clean:
	rm lex.yy.c
	rm lexic_analyzer
	rm ./*.class
	rm syntax-calc
