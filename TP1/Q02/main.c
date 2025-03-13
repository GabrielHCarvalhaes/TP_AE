#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool conferindo(int linha[], int tam){
    bool ehPalindromo = true;
    int atras = tam - 1;
    for(int i = 0; i < atras; i++, atras--){
        if(linha[i] != linha[atras]){
            ehPalindromo = false;
            i= atras;
        }
    }
    return ehPalindromo;
}

void mudarASC(char linha[], int tam,int convercao[]){

    for(int i = 0; i < tam; i++){
        if( (unsigned char)linha[i] > 127 ){
            linha[i]='*';       
        }
        convercao[i]= (int)linha[i];
    }

}
int main(){
    char linha[200];
    fgets(linha, 200, stdin);
    linha[strcspn(linha, "\n")] = '\0';
    while(!(strlen(linha) == 3 && linha[0] == 'F' && linha[1] == 'I' && linha[2] == 'M')){
        int tam = strlen(linha);
        int convertido[tam];
        mudarASC(linha, tam, convertido);
        tam=strlen(linha);
        bool ehPalindromo = conferindo(convertido, tam);
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