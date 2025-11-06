#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 500

int particionar(int *V, int inicio, int fim){
    int esq, dir, temp, indicePivo;
    indicePivo = inicio + rand() % (fim - inicio + 1);
    
    temp = V[inicio];
    V[inicio] = V[indicePivo];
    V[indicePivo] = temp;
    
    int pivo = V[inicio];
    
    esq = inicio + 1;
    dir = fim;

    while(esq <= dir){
        while(esq <= fim && V[esq] <= pivo) 
            esq++;
        while(V[dir] > pivo)
            dir--;
        
        if(esq < dir){
            temp = V[esq];
            V[esq] = V[dir];
            V[dir] = temp;
        }
    }
    
    temp = V[inicio];
    V[inicio] = V[dir];
    V[dir] = temp;
    
    return dir; 
}

void quickSort(int *V, int inicio, int fim){
    int pivo_posicao;
    if(inicio < fim){ 
        pivo_posicao = particionar(V, inicio, fim);
        quickSort(V, inicio, pivo_posicao - 1);
        quickSort(V, pivo_posicao + 1, fim);
    }
}

int main(){
    int V[TAMANHO];
    int copia[TAMANHO];
    FILE *arquivo;
    clock_t inicio, fim;
    double tempo_total;
    
    arquivo = fopen("arq_teste.txt", "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    
    for (int i = 0; i < TAMANHO; i++) {
        fscanf(arquivo, "%d ,", &V[i]);
    }
    
    fclose(arquivo);

    srand(time(NULL));
    
    inicio = clock();

    for (int rep = 0; rep < 1000; rep++) {
        for (int i = 0; i < TAMANHO; i++) {
            copia[i] = V[i];
        }
        quickSort(copia, 0, TAMANHO - 1);
    }

    fim = clock();
    tempo_total = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo total para ordenar o vetor 1000 vezes: %.6f segundos\n", tempo_total);
    
    printf("\nVetor ordenado (primeiros %d elementos):\n", TAMANHO);
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", copia[i]);
    }
    printf("\n");
    
    return 0;
}
