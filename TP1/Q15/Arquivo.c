#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int qtdnumeros;


    scanf("%i", &qtdnumeros);
    getchar(); // Consome a quebra de linha deixada pelo scanf

   
    FILE *file = fopen("Doubles.txt", "wb+");
    char linha[50];

    // Loop para ler os números e escrevê-los no arquivo
    for (int i = 0; i < qtdnumeros; i++) {
        
        fgets(linha, 50, stdin);
        linha[strcspn(linha, "\n")] = '\0';

        // Verifica se a linha começa com um ponto (.)
        if (linha[0] == '.') {
            
            for (int z = strlen(linha); z >= 0; z--) {
                linha[z + 1] = linha[z];
            }

            linha[0] = '0';
        }

        char *endptr;
        double num = strtod(linha, &endptr);

        fwrite(&num, sizeof(double), 1, file);
    }

    // Loop para ler os números do arquivo em ordem inversa
    for (int i = qtdnumeros - 1; i >= 0; i--) {
        double num;

        // Posiciona o ponteiro do arquivo no início do i-ésimo double
        fseek(file, i * sizeof(double), SEEK_SET);
        fread(&num, sizeof(double), 1, file);

        // Verifica se o número é um inteiro
        if (num == (int)num) {
           
            int n = (int)num;
            printf("%d\n", n);
        } else {
            printf("%g\n", num);
        }
    }

    // Fecha o arquivo
    fclose(file);

    return 0;
}