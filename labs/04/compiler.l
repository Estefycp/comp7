%{
#include <stdio.h>
%}

%%
f                                    printf("floatdcl");
i                                    printf("intdcl");
p                                    printf("print");
[a-e]|[g-h]|[j-o]|[q-z]              printf("id");
\/\/.*\n                             printf("comment\n");
=                                    printf("assign");
\+                                   printf("plus");
\-                                   printf("minus");  
[0-9]+                               printf("inum"); 
[0-9]+\.[0-9]+                       printf("fnum");
\n                                   printf("\n");
\                                    printf(" ");  
.                                    printf("NoRecognized");                                   

%%
