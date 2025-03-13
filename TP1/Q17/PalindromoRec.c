#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void converterASC(int strNum[], char linha[], int i){
    if( i < strlen(linha)){

        int numASC = (int)linha[i];
        strNum[i]= numASC;
        converterASC(strNum, linha, i+1);
    }

}

bool teste(int strNum[], int i, int atras){
    bool ehPalindromo = true;
    if( strNum[i] != strNum[atras]){
        ehPalindromo=false;
        i= atras;
    }
    if(i< atras){
        teste(strNum, i+1, atras-1);
    }

    return ehPalindromo;
}

int main(){
    
    char linha[200];
    fgets(linha,200,stdin);
    linha[strcspn(linha,"\n")] = '\0';
    while(!(strlen(linha) == 3 && linha[0] == 'F' && linha[1] == 'I' && linha[2] == 'M')){

        int strNum[strlen(linha)];
        converterASC(strNum, linha, 0);
        bool ehPalindromo = teste(strNum, 0, strlen(linha)-1);
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
