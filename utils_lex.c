#include "utils_lex.h"

char* string_no_quotes(char* str){
     //Je retire les "" du nom du fichier
    for(int i=0;i<strlen(str);i++){
        str[i] = str[i+1];
    }
    //str = realloc(str,strlen(str)-1);
      
    str[strlen(str)-1] = '\0';
    //str = realloc(str,strlen(str)-1);
    return str;
}