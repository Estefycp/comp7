%{
#include <stdio.h>
FILE *file;
%}


%%
f                                    fprintf(file,"floatdcl");
i                                    fprintf(file,"intdcl");
p                                    fprintf(file,"print");
[a-e]|[g-h]|[j-o]|[q-z]              fprintf(file,"id");
\/\/.*\n                             
=                                    fprintf(file,"assign");
\+                                   fprintf(file,"plus");
\-                                   fprintf(file,"minus");
\*				                     fprintf(file,"multiplication");
\/  				                 fprintf(file,"division");
[0-9]+                               fprintf(file,"inum"); 
[0-9]+\.[0-9]+                       fprintf(file,"fnum");
\n+                                  fprintf(file,"\n");
\                                    fprintf(file," ");  
.                                    fprintf(file,"NoRecognized");                                   

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

        file = fopen("tokens.out", "w");

        if(file == NULL)
        {
            printf("Error!");
            return (-1);
        }

        yyset_in(fd);
        yylex();

        fclose(file);
        fclose(fd);
    }
    else
        printf("Usage: a.out filename\n");
    return (0);
}