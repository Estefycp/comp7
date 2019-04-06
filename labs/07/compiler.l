%{
#include <stdio.h>
#include "y.tab.h"
extern int yylex();
FILE *file;
%}


%%
f                                    return FLOATDCL;
i                                    return INTDCL;
p                                    return PRINT;
[a-e]|[g-h]|[j-o]|[q-z]              return ID;
\/\/.*\n                             
=                                    return ASSIGN;
\+                                   return PLUS;
\-                                   return MINUS;
\*				                     return MULTIPLICATION;
\/  				                 return DIVISION;
[0-9]+                               return INUM;
[0-9]+\.[0-9]+                       return FNUM;
\n+                                  
\                                    
.                                    return ERROR;                                ;

%%


int main(int argc, char **argv) {
    FILE    *fd;

    if (argc == 2)
    {
        if (!(fd = fopen(argv[1], "r")))
        {
            perror("Error: ");
            return (-1);
        }

        

        yyset_in(fd);
        
        printf("digraph G {\n");
        yyparse();
        printf("}\n");
        
        fclose(fd);
    }
    else
        printf("Usage: a.out filename\n");
    return (0);
}