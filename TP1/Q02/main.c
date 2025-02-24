#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool conferindo(char linha[], int tam){
    bool ehPalindromo = true;
    int atras = tam - 1,pivo = tam / 2;
    for(int i = 0; i < pivo; i++, atras--){
        if(linha[i] != linha[atras]){
            ehPalindromo = false;
            i= pivo;
        }
    }
    return ehPalindromo;
}

int main(){
    char linha[200];
    fgets(linha, 200, stdin);
    linha[strcspn(linha, "\n")] = '\0';
    while(strcmp(linha, "FIM") != 0){
        int tam = strlen(linha);
        bool ehPalindromo = conferindo(linha, tam);
        if(ehPalindromo){
            printf("SIM\n");
        }else{
            printf("NAO\n");
        }
        fgets(linha, 200, stdin);
        linha[strcspn(linha, "\n")] = '\0';
    }

    return 0;
}