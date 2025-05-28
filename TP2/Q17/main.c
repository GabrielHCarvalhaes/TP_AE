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


// Função de comparação aprimorada para director e title
int compararShows(int id1, int id2) {
    // Tratamento especial para diretores vazios ou "NaN"
    int isNaN1 = (shows[id1].director[0] == '\0' || strcasecmp(shows[id1].director, "NaN") == 0);
    int isNaN2 = (shows[id2].director[0] == '\0' || strcasecmp(shows[id2].director, "NaN") == 0);
    
    // Diretores "NaN" vão para o final
    if (isNaN1 && !isNaN2) return 1;
    if (!isNaN1 && isNaN2) return -1;
    if (isNaN1 && isNaN2) return strcasecmp(shows[id1].title, shows[id2].title);
    
    // Comparação normal para diretores
    int cmpDirector = strcasecmp(shows[id1].director, shows[id2].director);
    if (cmpDirector != 0) return cmpDirector;
    
    // Desempate por título
    return strcasecmp(shows[id1].title, shows[id2].title);
}

// Versão correta do HeapSort parcial
void heapSortParcial(int ids[], int n, int k) {
    // Primeiro: ordena todo o array com HeapSort completo
    // Fase de construção do heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(ids, n, i);
    
    // Fase de extração
    for (int i = n - 1; i >= 0; i--) {
        // Move a raiz (maior elemento) para o final
        int temp = ids[0];
        ids[0] = ids[i];
        ids[i] = temp;
        
        // Reconstroi o heap reduzido
        heapify(ids, i, 0);
    }
    
    // Segundo: pega apenas os primeiros k elementos
    // (O heapSort completo garante que os primeiros k estão corretos)
}

// Função heapify corrigida
void heapify(int ids[], int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    
    if (esq < n && compararShows(ids[esq], ids[maior]) > 0)
        maior = esq;
    
    if (dir < n && compararShows(ids[dir], ids[maior]) > 0)
        maior = dir;
    
    if (maior != i) {
        int temp = ids[i];
        ids[i] = ids[maior];
        ids[maior] = temp;
        heapify(ids, n, maior);
    }
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
    
    // Executa HeapSort parcial para os 10 primeiros
    heapSortParcial(ids, tam, 10);
    
    
    for (int i = 0; i < 10; i++) {
        lerShow(shows[ids[i]]);
    }
    
    return 0;
}
