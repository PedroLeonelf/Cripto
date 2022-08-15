#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int getTotalOcorrunces(int * vect){
    int len;
    int total = 0;
    for(len = 0; len < 26; len++){
        total += vect[len];
    }
    return total;
}

void writeBackFrequency(char * file, int * freq){
    int total = getTotalOcorrunces(freq);
    FILE * fp = fopen(file, "w");
    for(int i = 0; i < 26; i++){
        float value = (float)100 * freq[i] / total;
        fprintf(fp, "%f ", value);
    }
    fclose(fp);
}

int charCount(char letra, char * string){
    int i; 
    int counter = 0;
    for(i = 0; i < strlen(string); i++){
        if(string[i] == letra || string[i] == letra + 32){
            counter+=1;
        }
    }
    return counter;
}

void countAZ(char * string, char * file){
    char c;
    int vector[26];
    for(c = 'A'; c <= 'Z'; c++){
        // fprintf(fp, "%d ",charCount(c, string));
        vector[c - 'A'] = charCount(c, string);
    }
    writeBackFrequency(file, vector);
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
    checkFileIsOk(out);
    fclose(fopen(out, "w"));
    countAZ(in, out);

}

float chiQuadrado(){
    int i;
    FILE *fpReference = fopen("tabelaPortugues.txt", "r");
    FILE *fpDecript = fopen("tabelaTexto.txt", "r");
    float ref, actual, equation;
    float sum = 0.0;
    for(i = 0; i <= 25; i++){
        fscanf(fpReference, "%f", &ref);
        fscanf(fpDecript, "%f", &actual);
        equation = pow((actual - ref),2) / ref;
        sum += equation;
    }
    return sum;    
}





void decrypt(char * encryptText){
    char * out = malloc(strlen(encryptText));
    char * aux = malloc(strlen(encryptText));
    float menor = 10000.0;
    int auxKey;
    for (int i = 1; i <= 58; i++){
        for(int idx = 0; idx < strlen(encryptText); idx++){
            out[idx] = encryptText[idx] + i;
            if(encryptText[idx] + i >'Z')
                out[idx] = encryptText[idx] + i - 25;
        }
        writeTable("tabelaTexto.txt", out);
        float chi = chiQuadrado();
        char key = 'A'+i-1;
        if (chi < menor){
            menor = chi;
            auxKey = key;
            strcpy(aux,out);
        }
        printf("%s key:%c chi:%f \n", out, key, chi);
    }
    printf("\nMenor:%s key:%c chi:%f \n", aux, auxKey, menor);

}
 


int main(int argc, char const *argv[]){
    char stringCifrada[50] = "HQKQWTFLCGETRTEGROYOEGXQDTFLQUTDLTEKTZQ";
    decrypt(stringCifrada);
    // chiQuadrado();
    // writeTable("tabelaTexto.txt", stringCifrada);
    // printf("%d", 'A');
    return 0;
}
