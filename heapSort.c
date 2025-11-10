#include <stdio.h>
#include <time.h>
#define TAM 5000

int preencher_vetor(int v[]){
	int tam_do_vetor=0;
	FILE* ARQ = fopen("arq_teste.txt", "r");
	
	if (ARQ == NULL) {
        return -1;
    }

	while(tam_do_vetor<TAM && fscanf(ARQ, "%d,", &v[tam_do_vetor]) > 0){
		tam_do_vetor++;
	}
    fclose(ARQ);
    return tam_do_vetor;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void heapify(int arr[], int n, int i) {
    int maior = i;       // Inicializa o maior como raiz
    int esq = 2 * i + 1; // filho esquerdo
    int dir = 2 * i + 2; // filho direito

    if (esq < n && arr[esq] > arr[maior])
        maior = esq;

    if (dir < n && arr[dir] > arr[maior])
        maior = dir;

    if (maior != i) {
        swap(&arr[i], &arr[maior]);

        heapify(arr, n, maior);
    }
}

void heapSort(int arr[], int n) {
	int i;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
	int i;
    printf("vetor v: ");
    for (i = 0; i < n; i++)
        printf("%d%s", arr[i], (i == n - 1 ? "" : ", "));
    printf("\n");
}

int main() {
	double tempo_decorrido=0.0;
    int v_original[TAM], v_ordenado[TAM], i, tam_ordenar, repeticao;
    clock_t begin, end;
    
    if (preencher_vetor(v_original) != TAM) {
        printf("Erro na leitura do arquivo.\n");
        return 0;
	}
    
    for(tam_ordenar=500; tam_ordenar<=5000; tam_ordenar+=500){
    	double soma_tempos = 0.0;
    	for(repeticao = 0; repeticao < 10; repeticao++){
    		for(i=0;i<tam_ordenar;i++){
    			v_ordenado[i] = v_original[i];
			}
    		begin = clock();
    		heapSort(v_ordenado, tam_ordenar);
    		end = clock();
    		
    		soma_tempos += (double)(end - begin) / CLOCKS_PER_SEC;
		}
    	double tempo_medio = soma_tempos / 10.0;
		printf("Tamanho %d: Tempo medio = %f segundos\n", tam_ordenar, tempo_medio);
	}

    printArray(v_ordenado, TAM);
    
    return 0;
}
