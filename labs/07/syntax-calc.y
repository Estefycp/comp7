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
int yylex();
extern int yyparse();
int nextsave = 0;
int terminalnext =0;
extern int getterminalnext(){
    return terminalnext;
};
void addedge(char *nonterminal1, int next1, char *nonterminal2, int next2){
    printf("%s_%d -> %s_%d\n", nonterminal1, next1, nonterminal2, next2);
}


%}

%token FLOATDCL INTDCL PRINT ID ASSIGN PLUS MINUS MULTIPLICATION DIVISION INUM FNUM ERROR

%%

prog : dcls stmts {
        addedge("PROG", nextsave, "DCLS", $1);
        addedge("PROG", nextsave, "STMTS", $2);
        $$=nextsave;
        nextsave++;
    }
     ;

dcls : dcl dcls {
        addedge("DCLS", nextsave, "DCL", $1);
        addedge("DCLS", nextsave, "DCLS", $2);
        $$=nextsave;
        nextsave++;
    }
     | {
        addedge("DCLS", nextsave, "empty", terminalnext++);
        $$=nextsave;
        nextsave++;
     }
     ;

dcl : FLOATDCL ID{
        addedge("DCL", nextsave, "floatdcl", terminalnext++); 
        addedge("DCL", nextsave, "id", terminalnext++);
        $$=nextsave;
        nextsave++;
    }
    | INTDCL ID {
        addedge("DCL", nextsave, "intdcl", terminalnext++);
        addedge("DCL", nextsave, "id", terminalnext++);
        $$=nextsave;
        nextsave++;
    }
    ;

stmts : stmt stmts{
        addedge("STMTS", nextsave, "STMT", $1);
        addedge("STMTS", nextsave, "STMTS", $2);
        $$=nextsave;
        nextsave++;
    }
      | {
        addedge("STMTS", nextsave, "empty", terminalnext++);
        $$=nextsave;
        nextsave++;
      }
      ;

stmt : ID ASSIGN val expr {
        addedge("STMT", nextsave, "id", terminalnext++); 
        addedge("STMT", nextsave, "assign", terminalnext++);
        addedge("STMT", nextsave, "VAL", $3);
        addedge("STMT", nextsave, "EXPR", $4);
        $$=nextsave;
        nextsave++;
    }
     | PRINT ID {
        addedge("STMT", nextsave, "print", terminalnext++);
        addedge("STMT", nextsave, "id", terminalnext++);
        $$=nextsave;
        nextsave++;
     }
     ;

expr : PLUS val expr{
        addedge("EXPR", nextsave, "plus", terminalnext++);
        addedge("EXPR", nextsave, "VAL", $2);
        addedge("EXPR", nextsave, "EXPR", $3);
        $$=nextsave;
        nextsave++;
    }
     | MINUS val expr {
        addedge("EXPR", nextsave, "minus", terminalnext++);
        addedge("EXPR", nextsave, "VAL", $2);
        addedge("EXPR", nextsave, "EXPR", $3);
        $$=nextsave;
        nextsave++;
     }
     | MULTIPLICATION val expr{
        addedge("EXPR", nextsave, "multiplied", terminalnext++); 
        addedge("EXPR", nextsave, "VAL", $2);
        addedge("EXPR", nextsave, "EXPR", $3);
        $$=nextsave;
        nextsave++;
     }
     | DIVISION val expr {
        addedge("EXPR", nextsave, "division", terminalnext++);
        addedge("EXPR", nextsave, "VAL", $2);
        addedge("EXPR", nextsave, "EXPR", $3);
        $$=nextsave;
        nextsave++;
     }
     | {
        addedge("EXPR", nextsave, "empty", terminalnext++);
        $$=nextsave;
        nextsave++;
      }
     ;

val : ID {
        addedge("VAL", nextsave, "id", terminalnext++);
        $$=nextsave;
        nextsave++;
    }
    | INUM{
        addedge("VAL", nextsave, "inum", terminalnext++);
        $$=nextsave;
        nextsave++;
    }
    | FNUM {
        addedge("VAL", nextsave, "fnum", terminalnext++);
        $$=nextsave;
        nextsave++;
    }
    ;

%%