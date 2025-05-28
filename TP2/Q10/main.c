#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia, mes, ano;
} Date;

typedef struct {
    char show_id[5];
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
int ids[1368];

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
            vetsplit[qtdp++] = strdup(start);
            if (*(ptr+1)) ptr += 2; // pula aspas final e vírgula
            else ptr++; // fim da linha
        } else {
            start = ptr;
            while (*ptr && *ptr != ',') ptr++;
            if (*ptr) {
                *ptr = '\0';
                ptr++; // avança para depois da vírgula
            }
            vetsplit[qtdp++] = strlen(start) ? strdup(start) : strdup("NaN");
        }
    }

    // Corrige quando ainda há dados restantes e não atingimos 12 campos
    if (*ptr && qtdp < 12) {
        vetsplit[qtdp++] = strdup(ptr);
    }
}


int indexFinder(char *id) {
    return atoi(id + 1) - 1;
}

void organizandoVet(char *organizado[], char organizar[]) {
    int tam = 0;
    char *token = strtok(organizar, ",");
    while (token != NULL && tam < 20) {
        while (*token == ' ') token++;
        organizado[tam++] = strdup(token);
        token = strtok(NULL, ",");
    }
    organizado[tam] = NULL;

    // bubble sort
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
    char *dSeparado[3];
    int z = 0;
    char *token = strtok(date, " ,");
    while (token != NULL && z < 3) {
        dSeparado[z++] = token;
        token = strtok(NULL, " ,");
    }

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
        strcpy(shows[index].show_id, divisao[0]);
        strcpy(shows[index].type, divisao[1]);
        strcpy(shows[index].title, divisao[2]);
        strcpy(shows[index].director, divisao[3]);

        char cast[1000];
        strcpy(cast, divisao[4]);
        char *castArray[21] = {0};
        organizandoVet(castArray, cast);
        guardarVetCast(index, castArray);

        strcpy(shows[index].country, divisao[5]);

        if (strcmp(divisao[6], "NaN") == 0) {
            shows[index].date_added = (Date){0, 0, 0};
        } else {
            shows[index].date_added = parseDate(divisao[6]);
        }

        shows[index].release_year = atoi(divisao[7]);
        strcpy(shows[index].rating, divisao[8]);
        strcpy(shows[index].duration, divisao[9]);

        char listed[1000];
        strcpy(listed, divisao[10]);
        char *listedArray[21] = {0};
        organizandoVet(listedArray, listed);
        guardarVetListed(index, listedArray);
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

void trocar(int ids[], int i, int j) {
    if (i == j) return; // Não faz nada se os índices forem iguais
    
    int temp = ids[i];
    ids[i] = ids[j];
    ids[j] = temp;
}

// Função de comparação principal para o QuickSort
int compararShows(int id1, int id2) {
    Show *show1 = &shows[id1];
    Show *show2 = &shows[id2];
    
    // Compara as datas primeiro
    int cmpData = compararDatas(show1->date_added, show2->date_added);
    if (cmpData != 0) return cmpData;
    
    // Se as datas forem iguais, compara por título (case insensitive)
    #ifdef _WIN32
        return _stricmp(show1->title, show2->title);
    #else
        return strcasecmp(show1->title, show2->title);
    #endif
}

// Função de particionamento para o QuickSort
int particionar(int ids[], int baixo, int alto) {
    // Seleciona o pivô (usando o último elemento)
    int pivo = ids[alto];
    int i = (baixo - 1);
    
    for (int j = baixo; j <= alto - 1; j++) {
        if (compararShows(ids[j], pivo) <= 0) {
            i++;
            trocar(ids, i, j);
        }
    }
    trocar(ids, i + 1, alto);
    return (i + 1);
}

// Implementação recursiva do QuickSort
void quickSortRecursivo(int ids[], int baixo, int alto) {
    if (baixo < alto) {
        // Encontra o índice do pivô
        int pi = particionar(ids, baixo, alto);
        
        // Ordena recursivamente os elementos antes e depois do pivô
        quickSortRecursivo(ids, baixo, pi - 1);
        quickSortRecursivo(ids, pi + 1, alto);
    }
}

// Função de interface para o QuickSort
void quickSort(int ids[], int tam) {
    quickSortRecursivo(ids, 0, tam - 1);
}

int main() {
    leiaShow();
    
    char linha[10];
    fgets(linha, 10, stdin);
    linha[strcspn(linha, "\n")] = '\0';
    int tam = 0;
    
    while (strcmp(linha, "FIM") != 0) {
        int index = indexFinder(linha);
        ids[tam] = index;
        fgets(linha, 10, stdin);
        linha[strcspn(linha, "\n")] = '\0';
        tam++;
    }
    
    quickSort(ids, tam);
    
    for (int i = 0; i < tam; i++) {
        lerShow(shows[ids[i]]);
    }
    
    return 0;
}
