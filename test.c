#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int charCount(char letra, char * string){
    int i; 
    int counter = 0;
    for(i = 0; i < strlen(string); i++){
        if(string[i] == letra){
            counter+=1;
        }
    }
    return counter;
}

void countAZ(char * string){
    char c;
    FILE * fp = fopen("tabela.txt", "a+");
    for(c = 'A'; c < 'Z'; c++){
        fprintf(fp, "%d ",charCount(c, string));
    }
    fclose(fp);
}

void writeFile(char * string){
    FILE * filePointer = fopen("tabela.txt", "ab+");
    if (filePointer == NULL){
        printf("Erro na abertura!");
        exit(-1);
    }
    fclose(filePointer);
    fclose(fopen("tabela.txt", "w"));
    countAZ(string);
}

int main(int argc, char const *argv[]){
    char string[30];
    scanf("%s", string);
    writeFile(string);
    return 0;
}
