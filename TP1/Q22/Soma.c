#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int somando(char *linha, int i){
    int result=0;
    if(i < strlen(linha)){

        int num = linha[i]-'0';
        result = num + somando(linha, i+1);
    }

    return result;
}

int main(){
    
    char linha[50];
    fgets(linha,50,stdin);
    linha[strcspn(linha,"\n")]='\0';

    while(!(strlen(linha) == 3 && linha[0] == 'F' && linha[1] == 'I' && linha[2] == 'M')){
        
        int result = somando(linha, 0);
        printf("%i\n", result);

        fgets(linha,50,stdin);
        linha[strcspn(linha,"\n")]='\0';
    }




    return 0;
}
