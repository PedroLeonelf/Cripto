#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int charCount(char letra, char * string){
    int i; 
    int counter = 0;
    printf("String:%s\n", string);
    for(i = 0; i < strlen(string); i++){
        if(string[i] == letra || string[i] == letra + 32){
            printf("Achou %c em %c\n", letra, string[i]);
            counter+=1;
        }
    }
    return counter;
}

void countAZ(char * string, char * file){
    char c;
    FILE * fp = fopen(file, "a+");
    for(c = 'A'; c < 'Z'; c++){
        fprintf(fp, "%d ",charCount(c, string));
    }
    fclose(fp);
}


void checkFileIsOk(char * file){
    FILE * fp = fopen(file, "r");
    if(fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    fclose(fp);
}

long fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

char * readFile(char * file){
    FILE * fp = fopen(file, "r");
    checkFileIsOk(file);
    long size = fsize(fp);
    char * fcontent = malloc(size);
    fread(fcontent, 1, size, fp);
    return fcontent;
}

void writeTable(char * out, char * in){
    checkFileIsOk(in);
    checkFileIsOk(out);
    fclose(fopen(out, "w"));
    countAZ(readFile(in), out);
}
 


int main(int argc, char const *argv[]){
    // printf("%s", readFile("texto.txt"));
    // writeTable("tabelaTexto.txt", "texto.txt");
    // printf("%c", 'a' - 32);
    writeTable("tabelaCorpus.txt", "corpus_portugues.txt");
    return 0;
}
