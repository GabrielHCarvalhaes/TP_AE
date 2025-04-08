#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
    int ano;
}Date;

typedef struct{
    char show_id[5];
    char title[250];
    char director[100];
    char *cast[250];
    char country[70];
    Date date_added;
    int release_year;
    char rating[20];
    char duration[20];
    char *listed_in[250];

}Show;

//show_id,type,title,director,cast,country,date_added,release_year,rating,duration,listed_in,description
// 0   1       2                        3                            4               5          6            7     8      9       10                                              11
//s1,Movie,A Spark Story,"Jason Steran, Leanne Dare","Apthon Corbin, Louis Gonzales",,"September 24, 2021",2021,TV-PG,88 min,Documentary,Two Pixar filmmakers strive to bring their uniquely personal SparkShorts visions to the screen.ion,listed_in,description
    
void split1(char linha[], char *vetsplit[]){
    char separada[200]={0};
    int j = 0,qtdp=0;
    for(int i=j; linha[i] != '\0' && qtdp <12; i++){

        if(linha[i] ==','){
            if(j != 0){
                //salvar oque estava antes da virgula
                separada[j] = '\0';
                vetsplit[qtdp++] = strdup(separada);
                j=0;
            }
            if(linha[i+1] == '"'){
                //pula a virgula e a aspas parta ler apenas oque esta dentro da aspas
                i+=2;
                j=0;

                //le tudo que esta entre aspas
                while(linha[i] != '"'){
                    separada[j++]=linha[i++];
                }

                //guarda oque estava entre aspas
                separada[j] = '\0';
                vetsplit[qtdp++] = strdup(separada);
                j=0;
            }else if(linha[i+1] == ','){
                //Se o campo estiver estive null no csv vai colocar NaN 
                strcpy(separada,"NaN");
                vetsplit[qtdp++] = strdup(separada);
            }
        }else{
            separada[j++]=linha[i];
        }
    }
    if (j > 0) {
        separada[j] = '\0';
        vetsplit[qtdp++] = strdup(separada);
    }

}

void leiaShow(){
    FILE* file =fopen("./tmp/disneyplus.csv","r");
    char linha[2000];
    
    fgets(linha,2000,file);
    linha[strcspn(linha,"\n")] = '\0';
    
    //show_id,type,title,director,cast,country,date_added,release_year,rating,durat            //show_id,type,title,director,cast,country,date_added,release_year,rating,duration,listed_in,description
    // 0   1       2                        3                            4               5          6            7     8      9       10                                              11
    //s1,Movie,A Spark Story,"Jason Steran, Leanne Dare","Apthon Corbin, Louis Gonzales",,"September 24, 2021",2021,TV-PG,88 min,Documentary,Two Pixar filmmakers strive to bring their uniquely personal SparkShorts visions to the screen.ion,listed_in,description
    
    fgets(linha,2000,file);
    linha[strcspn(linha,"\n")] = '\0';
    char *divisao[12];
    split1(linha, divisao);
    for (int i = 0; i < 12; i++){
        
        printf("[%d]: %s \n",i,divisao[i]);

    }
    



}

int main(int argc, char const *argv[]){
    
    leiaShow();
    
    return 0;
}
