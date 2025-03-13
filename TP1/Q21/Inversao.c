#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void invertendoStr(char *linha, int i, int atras){
    if(i<atras){
        char tmp = linha[i];
        linha[i] = linha[atras];
        linha[atras] = tmp;

        invertendoStr(linha, i+1, atras-1);
    }

}


int main(){
    
    char linha[50];
    fgets(linha, 50, stdin);
    linha[strcspn(linha,"\n")] = '\0';
    while(!(strlen(linha) == 3 && linha[0] == 'F' && linha[1] == 'I' && linha[2] == 'M')){

        invertendoStr(linha,0,strlen(linha)-1);
        
        printf("%s\n",linha);
        fgets(linha, 50, stdin);
        linha[strcspn(linha,"\n")] = '\0';
    }

    return 0;
}
