%{
#include <stdio.h>
#include <string.h>

void yyerror(const char *str)
{
    fprintf(stderr,"error: %s\n",str);
}

int yywrap()
{
    return 1;
}

main()
{
    yyparse();
}

%}

%token FLOATDCL INTDCL PRINT ID ASSIGN PLUS MINUS MULTIPLICATION DIVISION INUM FNUM

%%

prog : dcls stmts
     ;

dcls : dcl dcls
     |
     ;

dcl : FLOATDCL ID
    | INTDCL ID
    ;

stmts : stmt stmts
      |
      ;

stmt : ID ASSIGN val expr
     | PRINT ID
     ;

expr : PLUS val expr
     | MINUS val expr
     | MULTIPLICATION val expr
     | DIVISION val expr
     ;

val : ID
    | INUM
    | FNUM
    ;

%%