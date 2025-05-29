#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia, mes, ano;
} Date;

typedef struct {
    char show_id[10];  
    char type[50];
    char title[250];
    char director[100];
    char *cast[21]; 
    char country[70];
    Date date_added;
    int release_year;
    char rating[20];
    char duration[20];
    char *listed_in[21]; 
} Show;

Show shows[1368];

// Função para limpar aspas extras
char* clean_quotes(char *str) {
    if (str == NULL || strcmp(str, "NaN") == 0) return strdup("NaN");
    
    char *result = malloc(strlen(str) + 1);
    char *dest = result;
    int in_quotes = 0;
    
    for (char *src = str; *src; src++) {
        if (*src == '"') {
            if (in_quotes && *(src+1) == '"') {
                *dest++ = '"';
                src++;
            }
            in_quotes = !in_quotes;
        } else {
            *dest++ = *src;
        }
    }
    *dest = '\0';
    
    if (strlen(result) == 0) {
        free(result);
        return strdup("NaN");
    }
    return result;
}

void split1(char linha[], char *vetsplit[]) {
    char *ptr = linha;
    char *start;
    int qtdp = 0;
    
    while (*ptr && qtdp < 12) {
        if (*ptr == '"') {
            ptr++; // pula aspas inicial
            start = ptr;
            while (*ptr && !(*ptr == '"' && (*(ptr+1) == ',' || *(ptr+1) == '\0'))) ptr++;
            *ptr = '\0';
            
            vetsplit[qtdp++] = clean_quotes(start);
            
            if (*(ptr+1)) ptr += 2; // pula aspas final e vírgula
            else ptr++; // fim da linha
        } else {
            start = ptr;
            while (*ptr && *ptr != ',') ptr++;
            if (*ptr) {
                *ptr = '\0';
                ptr++; // avança para depois da vírgula
            }
            vetsplit[qtdp++] = strlen(start) ? clean_quotes(start) : strdup("NaN");
        }
    }

    // Preenche campos faltantes com NaN
    while (qtdp < 12) {
        vetsplit[qtdp++] = strdup("NaN");
    }
}

int indexFinder(char *id) {
    return atoi(id + 1) - 1;
}

void organizandoVet(char *organizado[], char organizar[]) {
    if (strcmp(organizar, "NaN") == 0) {
        organizado[0] = strdup("NaN");
        organizado[1] = NULL;
        return;
    }

    int tam = 0;
    char *token = strtok(organizar, ",");
    while (token != NULL && tam < 20) {
        // Remove apenas espaços no início
        while (*token == ' ') token++;
        
        // Não remove espaços no final
        if (strlen(token) > 0) {
            organizado[tam++] = strdup(token);
        }
        token = strtok(NULL, ",");
    }
    organizado[tam] = NULL;

    // bubble sort (mantido igual)
    for (int i = 0; i < tam - 1; i++) {
        for (int j = i + 1; j < tam; j++) {
            if (strcmp(organizado[i], organizado[j]) > 0) {
                char *tmp = organizado[i];
                organizado[i] = organizado[j];
                organizado[j] = tmp;
            }
        }
    }
}

void guardarVetCast(int index, char *guardar[]) {
    int i;
    for (i = 0; guardar[i] != NULL && i < 20; i++) {
        shows[index].cast[i] = strdup(guardar[i]);
    }
    shows[index].cast[i] = NULL;
}

void guardarVetListed(int index, char *guardar[]) {
    int i;
    for (i = 0; guardar[i] != NULL && i < 20; i++) {
        shows[index].listed_in[i] = strdup(guardar[i]);
    }
    shows[index].listed_in[i] = NULL;
}

Date parseDate(char *date) {
    if (date == NULL || strcmp(date, "NaN") == 0) {
        return (Date){0, 0, 0};
    }

    char *dSeparado[3];
    int z = 0;
    char *token = strtok(date, " ,");
    while (token != NULL && z < 3) {
        dSeparado[z++] = token;
        token = strtok(NULL, " ,");
    }

    if (z != 3) return (Date){0, 0, 0};

    char *meses[12] = {"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};

    int numMes = 0;
    for (int i = 0; i < 12; i++) {
        if (strcmp(meses[i], dSeparado[0]) == 0) {
            numMes = i + 1;
            break;
        }
    }

    return (Date){atoi(dSeparado[1]), numMes, atoi(dSeparado[2])};
}

void leiaShow() {
    FILE *file = fopen("/tmp/disneyplus.csv", "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[2000];
    fgets(linha, 2000, file); // cabeçalho

    while (fgets(linha, 2000, file) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';

        char *divisao[12] = {0};
        split1(linha, divisao);

        int index = indexFinder(divisao[0]);
        strncpy(shows[index].show_id, divisao[0], 9);
        shows[index].show_id[9] = '\0';
        
        strcpy(shows[index].type, divisao[1]);
        strcpy(shows[index].title, divisao[2]);
        strcpy(shows[index].director, divisao[3]);

        char cast[1000];
        strcpy(cast, divisao[4]);
        char *castArray[21] = {0};
        organizandoVet(castArray, cast);
        guardarVetCast(index, castArray);

        strcpy(shows[index].country, divisao[5]);
        shows[index].date_added = parseDate(divisao[6]);
        shows[index].release_year = atoi(divisao[7]);
        strcpy(shows[index].rating, divisao[8]);
        strcpy(shows[index].duration, divisao[9]);

        char listed[1000];
        strcpy(listed, divisao[10]);
        char *listedArray[21] = {0};
        organizandoVet(listedArray, listed);
        guardarVetListed(index, listedArray);

        // Libera memória alocada para os campos temporários
        for (int i = 0; i < 12; i++) {
            free(divisao[i]);
        }
    }

    fclose(file);
}

char* formatterData(Date formatar) {
    if (formatar.ano == 0) return strdup("NaN");

    char *meses[12] = {"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};

    char *data_formatada = malloc(30 * sizeof(char));
    sprintf(data_formatada, "%s %d, %d", meses[formatar.mes - 1], formatar.dia, formatar.ano);
    return data_formatada;
}

void lerShow(Show sh) {
    printf("=> %s ## %s ## %s ## %s ## [", sh.show_id, sh.title, sh.type, sh.director);
    for (int i = 0; sh.cast[i] != NULL; i++) {
        printf("%s%s", sh.cast[i], (sh.cast[i+1] ? ", " : ""));
    }
    printf("] ## %s ## ", sh.country);

    char *data_formatada = formatterData(sh.date_added);
    printf("%s ## ", data_formatada);
    free(data_formatada);

    printf("%d ## %s ## %s ## [", sh.release_year, sh.rating, sh.duration);
    for (int i = 0; sh.listed_in[i] != NULL; i++) {
        printf("%s%s", sh.listed_in[i], (sh.listed_in[i+1] ? ", " : ""));
    }
    printf("] ##\n");
}

typedef struct celula Celula;

struct celula {
    Show elemento;
    Celula* prox;  
    Celula* ant;
    int pos;
};

typedef struct {
    Celula* primeiro;
    Celula* ultimo;
    int tam;
}Lista;

Lista lista;

void start(){
    lista.primeiro = (Celula*)malloc(sizeof(Celula));
    lista.primeiro->prox = NULL; 
    lista.primeiro->ant = NULL;
    lista.tam = 0;
    lista.ultimo = lista.primeiro;
}

void inserirInicio(Show x){
    Celula *tmp = (Celula*) malloc(sizeof(Celula));
    tmp->elemento = x;

    if (lista.primeiro->prox == NULL) {
        tmp->prox = NULL;
        tmp->ant = lista.primeiro;
        lista.primeiro->prox = tmp;
        lista.ultimo = tmp;
    }else {
        tmp->prox = lista.primeiro->prox;
        tmp->ant = lista.primeiro;
        tmp->prox->ant = tmp;  
        lista.primeiro->prox = tmp;
    }
    lista.tam++;
}

void inserirFim(Show x){
    Celula *tmp = (Celula*) malloc(sizeof(Celula));
    tmp->elemento = x;
    tmp->prox = NULL;
    tmp->ant = lista.ultimo;

    lista.ultimo->prox = tmp;
    lista.ultimo = tmp;
    lista.tam++;
}

void inserir(Show x, int pos){
    Celula *i = lista.primeiro;
    for (int j = 0; j < pos && i->prox != NULL; j++) {
        i = i->prox;
    }
    if(i->prox == NULL){
        inserirFim(x);
    }else{
        Celula *tmp = (Celula*)malloc(sizeof(Celula));
        tmp->elemento = x;
        tmp->prox = i->prox;
        tmp->ant = i;
        i->prox->ant = tmp;
        i->prox = tmp;
    }
    lista.tam++;
}

Show removerInicio(){
    Celula *i = lista.primeiro->prox;
    lista.primeiro->prox = i->prox;
    i->prox = NULL;
    Show resp = i->elemento;

    if(lista.ultimo == i){
        lista.ultimo = lista.primeiro;
    }
    lista.tam--;
    free(i);
    return resp;
}

Show removerFim(){
    Celula *i = lista.ultimo;
    Show resp = i->elemento;
    lista.ultimo = i->ant;
    lista.ultimo->prox = NULL;

    i->ant = NULL;
    free(i);
    lista.tam--;
    return resp;
}

Show remover(int pos){
    Celula *i = lista.primeiro;
    for (int j = 0; j < pos && i->prox != NULL; j++) {
        i = i->prox;
    }
    
    Celula* tmp = i->prox;
    Show resp;
    if(tmp->prox == NULL){
        resp = removerFim();
    }else{
        resp = tmp->elemento;
        i->prox = tmp->prox;
        tmp->prox->ant = i;
        tmp->prox = NULL;
        tmp->ant=NULL;
        free(tmp);  
    }
    lista.tam--;
    return resp;
}
void mostrar(){
    for(Celula *i = lista.primeiro->prox; i!=NULL; i= i->prox ){
        lerShow(i->elemento);
    }
}
int compararDatas(Date a, Date b) {
    // Trata casos onde uma ou ambas as datas são NULL (0/0/0)
    if (a.ano == 0 && b.ano == 0) return 0;
    if (a.ano == 0) return -1;
    if (b.ano == 0) return 1;
    
    // Compara anos
    if (a.ano != b.ano) return a.ano - b.ano;
    // Compara meses
    if (a.mes != b.mes) return a.mes - b.mes;
    // Compara dias
    return a.dia - b.dia;
}

int compararShows(int id1, int id2) {
    Show *show1 = &shows[id1];
    Show *show2 = &shows[id2];
    
    // Compara as datas primeiro
    int cmpData = compararDatas(show1->date_added, show2->date_added);
    if (cmpData != 0) return cmpData;
    
    // Se as datas forem iguais, compara por título (case insensitive)
    return strcasecmp(show1->title, show2->title);
}

// Função para trocar os elementos de dois nós 
void trocarNos(Celula *a, Celula *b) {
    Show temp = a->elemento;
    a->elemento = b->elemento;
    b->elemento = temp;
}

// Função de comparação entre dois nós
int compararNos(Celula *a, Celula *b) {
    // Compara as datas primeiro
    int cmpData = compararDatas(a->elemento.date_added, b->elemento.date_added);
    if (cmpData != 0) return cmpData;
    
    // Se as datas forem iguais, compara por título (case insensitive)
    return strcasecmp(a->elemento.title, b->elemento.title);
}

// Função de particionamento para o QuickSort
Celula* particionar(Celula *inicio, Celula *fim) {
    Celula *pivo = fim;
    Celula *i = inicio->ant;
    
    for (Celula *j = inicio; j != fim; j = j->prox) {
        if (compararNos(j, pivo) <= 0) {
            i = (i == NULL) ? inicio : i->prox;
            trocarNos(i, j);
        }
    }
    
    i = (i == NULL) ? inicio : i->prox;
    trocarNos(i, fim);
    return i;
}

// Implementação recursiva do QuickSort
void quickSortRecursivo(Celula *inicio, Celula *fim) {
    if (fim != NULL && inicio != fim && inicio != fim->prox) {
        Celula *pivo = particionar(inicio, fim);
        quickSortRecursivo(inicio, pivo->ant);
        quickSortRecursivo(pivo->prox, fim);
    }
}

// Função de interface para o QuickSort
void ordenarListaQuickSort() {
    if (lista.tam <= 1) return;
    
    // Ignora o nó cabeça e ordena a partir do primeiro elemento real
    quickSortRecursivo(lista.primeiro->prox, lista.ultimo);
}

int main() {
    leiaShow();
    start();
    char linha[30];
    fgets(linha,30,stdin);
    linha[strcspn(linha, "\n")] = '\0';
    while (strcmp(linha,"FIM") != 0 ) {
        int index = indexFinder(linha);
        inserirFim(shows[index]);
        fgets(linha,30,stdin);
        linha[strcspn(linha, "\n")] = '\0';
    }

    ordenarListaQuickSort();

    mostrar();
    return 0;
}
