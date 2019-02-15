#include <stdio.h>

#include <regex.h>        
regex_t regex,regexi;
#define expression "[a-e]|[g-h]|[j-o]|[q-z]"
#define num "[0-9]+"

int main(int argc, char **argv){
    FILE *file;
    file = fopen(argv[1], "r");
    FILE *output;
    output = fopen("lex.out","w");
    int status,status2;
    status = regcomp(&regex,expression,REG_EXTENDED|REG_NOSUB);
    status2 = regcomp(&regexi,num,REG_EXTENDED|REG_NOSUB);
    char s[1];
  
    int c;

    while ((c = getc(file)) != EOF){
        s[0]=c;

        if(c == 'f'){
            fputs("floatdcl",output);
        }
        else if(c=='i'){
            fputs("intdcl",output);
        }
        else if(c == '='){
            fputs("assign",output);
        }
        else if(c == 'p'){
            fputs("print",output);
        }
        else if (c == '-'){
            fputs("minus",output);
        }
         else if (c == '+'){
            fputs("plus",output);
        }
        else if(!regexec(&regex,s,(size_t)0,NULL,0)){
            fputs("id",output);
        }
        else if(!regexec(&regexi,s,(size_t)0,NULL,0)){

            int isf = 0;
            c = getc(file);
            while(isdigit(c) || c == '.'){
                if (c == '.'){
                isf = 1;
                }
                c = getc(file);
            }
            if (isf){
                fputs("fnum", output);
            }else{
                fputs("inum", output);
            }  
            ungetc(c,file);

        }
        else{
            fputc(c,output);
        }
         
    }
   
    fclose(file);
    fclose(output);
    return 0;
}