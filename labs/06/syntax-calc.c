#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
char *tokens[1000];
char **next;
char **last;
char dot[10000];
char *nextdot;
bool expr1();
bool expr2();
bool expr();
bool dcls1();
bool dcls2();
bool dcls();
bool stmts();
bool stmts2();
bool stmts1();


void fillNext(FILE *fp){
    int index=0;
    tokens[index] = (char *) malloc(1000 * sizeof(char));
    while(fscanf(fp, " %999s", tokens[index]) == 1){
        index++;
        tokens[index] = (char *) malloc(1000 * sizeof(char));
    }
    last = tokens+index;
    
    next=tokens;
    
}


void addedge(char *nonterminal1, char** next1, char *nonterminal2, char** next2){
    nextdot += sprintf(nextdot, "%s_%p -> %s_%p\n", nonterminal1, next1, nonterminal2, next2);
}

bool term(char *word){
    bool result = strcmp(*next,word)==0;
    next++;
    return result;
}

bool val1(){
    char **nextsave = next;
    return (addedge("VAL", nextsave, "id", next),term("id"));
}

bool val2(){
    char **nextsave = next;
    return (addedge("VAL", nextsave, "inum", next),term("inum"));
}

bool val3(){
    char **nextsave = next;
    return (addedge("VAL", nextsave, "fnum", next),term("fnum"));
}

bool val(){
   char **save = next;
   char *dotsave = nextdot;
   return (next = save,nextdot = dotsave,val1()) || (next = save,nextdot = dotsave,val2()) || (next = save,nextdot = dotsave,val3());
}

bool expr1(){
    char **nextsave = next;
    return (addedge("EXPR", nextsave, "plus", next),term("plus")) && (addedge("EXPR", nextsave, "VAL", next),val()) && (addedge("EXPR", nextsave, "EXPR", next),expr());
}

bool expr2(){
    char **nextsave = next;
    return (addedge("EXPR", nextsave, "minus", next),term("minus")) && (addedge("EXPR", nextsave, "VAL", next),val()) && (addedge("EXPR", nextsave, "EXPR", next),expr());
}

bool expr5(){
    char **nextsave = next;
    return (addedge("EXPR", nextsave, "empty", next),true);
}

bool expr4(){
    char **nextsave = next;
    return (addedge("EXPR", nextsave, "multiplied", next),term("multiplied")) && (addedge("EXPR", nextsave, "VAL", next),val()) && (addedge("EXPR", nextsave, "EXPR", next),expr());
}

bool expr3(){
    char **nextsave = next;
    return (addedge("EXPR", nextsave, "division", next),term("division")) && (addedge("EXPR", nextsave, "VAL", next),val()) && (addedge("EXPR", nextsave, "EXPR", next),expr());
}

bool expr(){
    char **save = next;
    char *dotsave = nextdot;
    return (next = save,nextdot = dotsave,expr1()) || (next = save,nextdot = dotsave,expr2()) || (next = save,nextdot = dotsave,expr3()) || (next = save,nextdot = dotsave,expr4()) || (next = save,nextdot = dotsave,expr5());
}

bool dcl1(){
    char **nextsave = next;
    return (addedge("DCL", nextsave, "floatdcl", next),term("floatdcl")) && (addedge("DCL", nextsave, "id", next),term("id"));
}

bool dcl2(){
    char **nextsave = next;
    return (addedge("DCL", nextsave, "intdcl", next),term("intdcl")) && (addedge("DCL", nextsave, "id", next),term("id"));
}

bool dcl(){
    char **save = next;
    char *dotsave = nextdot;
    return  (next = save,nextdot = dotsave,dcl1()) || (next = save,nextdot = dotsave,dcl2());
}

bool stmt1(){
    char **nextsave = next;
    return (addedge("STMT", nextsave, "id", next),term("id")) && (addedge("STMT", nextsave, "assign", next),term("assign")) && (addedge("STMT", nextsave, "VAL", next),val()) && (addedge("STMT", nextsave, "EXPR", next),expr());
}

bool stmt2(){
    char **nextsave = next;
    return (addedge("STMT", nextsave, "print", next),term("print")) && (addedge("STMT", nextsave, "id", next),term("id"));
}

bool stmt(){
    char **save = next;
    char *dotsave = nextdot;
    return (next = save,nextdot = dotsave,stmt1()) || (next = save,nextdot = dotsave,stmt2());
}

bool dcls1(){
    char **nextsave = next;
    return (addedge("DCLS", nextsave, "DCL", next), dcl()) && (addedge("DCLS", nextsave, "DCLS", next), dcls());
}

bool dcls2(){
    char **nextsave = next;
    return (addedge("DCLS", nextsave, "empty", next), true);
}

bool dcls(){
    char **save = next;
    char *dotsave = nextdot;
    return (next = save, nextdot = dotsave,dcls1()) || (next = save, nextdot = dotsave,dcls2());
}

bool stmts1(){
    char **nextsave = next;
    return (addedge("STMTS", nextsave, "STMT", next),stmt()) && (addedge("STMTS", nextsave, "STMTS", next),stmts());
}

bool stmts2(){
    char **nextsave = next;
    return (addedge("STMTS", nextsave, "empty", next),true);
}
bool stmts(){
    char **save = next;
    char *dotsave = nextdot;
    return (next = save,nextdot = dotsave,stmts1()) || (next = save,nextdot = dotsave,stmts2());
}

bool prog(){
    char **nextsave = next;
    return  (addedge("PROG", nextsave, "DCLS", next), dcls()) && (addedge("PROG", nextsave, "STMTS", next), stmts());
}

int main(int argc, char * argv[])
{
    if (argc < 2) return 1;
    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return 1;
    fillNext(fp);
    nextdot = dot;

    bool result = false;
    char **save2 = next;
    while(next < last && (result = prog()))
    {
        // for(char **i = save2; i < next; i++){
        //     printf("%s ", *i);
        // }
        // printf("\n");
        save2 = next;
    }

    // if(result){
    //     printf("bien\n");
    // }
    // else{
    //     printf("mal\n");
    // }

    printf("digraph D {\n");
    printf("%s\n", dot);
    printf("}\n");

    // if(prog()){
    //     if(next<last){
    //     printf("%s",*next);
    // }
    //     printf("bien\n");
    // }
    // else{
    //     printf("mal\n");
    // }
    
    fclose(fp);
    return 0;
}




