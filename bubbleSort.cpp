#include <stdio.h>
#include <time.h>

#define TAM 5000

FILE* abrir_arquivo(const char* nome_arq) {
    FILE* ARQ = fopen(nome_arq, "r");
    return ARQ; 
}

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {

    double tempo_decorrido = 0.0;
    int v_original[TAM], v_ordenado[TAM], i;
    int tam_ordenar, repeticao;
    clock_t begin, end;

    FILE* ARQ = abrir_arquivo("arq_teste.txt");

    if (ARQ == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 0;
    }
    
    int tam_do_vetor = 0;
    while (tam_do_vetor < TAM && fscanf(ARQ, "%d,", &v_original[tam_do_vetor]) > 0) {
        tam_do_vetor++;
    }
    fclose(ARQ);

    if (tam_do_vetor != TAM) {
        printf("Erro na leitura do arquivo");
        return 0;
    }

    for (tam_ordenar = 500; tam_ordenar <= 5000; tam_ordenar += 500) {

        double soma_tempos = 0.0;

        for (repeticao = 0; repeticao < 1000; repeticao++) { 

            for (i = 0; i < tam_ordenar; i++) {
                v_ordenado[i] = v_original[i];
            }

            begin = clock();
            bubbleSort(v_ordenado, tam_ordenar);
            end = clock();

            soma_tempos += (double)(end - begin) / CLOCKS_PER_SEC;
        }

        double tempo_medio = soma_tempos / 1000;
        printf("Para %d elementos ==> Tempo medio: %f segundos\n", tam_ordenar, tempo_medio);
    }

    printf("\nVetor final ordenado:\n");
    for (i = 0; i < TAM; i++) {
        printf("%d%s", v_ordenado[i], (i == TAM - 1 ? "" : ", "));
    }
    printf("\n");

    return 0;
}
