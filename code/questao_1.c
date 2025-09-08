#include <stdio.h>
#include <stdlib.h>

// A estrutura para armazenar o ponto de início e o índice original permanece a mesma.
typedef struct {
    int start;
    int original_index;
} StartInfo;

// A função de comparação para qsort permanece a mesma.
int compareStartInfo(const void *a, const void *b) {
    StartInfo *infoA = (StartInfo *)a;
    StartInfo *infoB = (StartInfo *)b;
    
    if (infoA->start < infoB->start) {
        return -1;
    }
    if (infoA->start > infoB->start) {
        return 1;
    }
    return 0;
}

// A função principal da solução permanece a mesma.
int* findRightInterval(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize) {
    *returnSize = intervalsSize;
    if (intervalsSize == 0) {
        return NULL;
    }

    int* result = (int*)malloc(intervalsSize * sizeof(int));
    if (result == NULL) {
        *returnSize = 0;
        return NULL;
    }

    StartInfo* starts = (StartInfo*)malloc(intervalsSize * sizeof(StartInfo));
    if (starts == NULL) {
        free(result);
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < intervalsSize; i++) {
        starts[i].start = intervals[i][0];
        starts[i].original_index = i;
    }

    qsort(starts, intervalsSize, sizeof(StartInfo), compareStartInfo);

    for (int i = 0; i < intervalsSize; i++) {
        int end_point = intervals[i][1];
        
        int low = 0;
        int high = intervalsSize - 1;
        int best_index = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (starts[mid].start >= end_point) {
                best_index = starts[mid].original_index;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        result[i] = best_index;
    }
    
    free(starts);
    return result;
}

// Função auxiliar para imprimir o resultado de forma legível.
void print_array(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


// =================================================================
// FUNÇÃO MAIN MELHORADA PARA ENTRADA INTERATIVA
// =================================================================
int main() {
    int intervalsSize;
    
    // 1. Pergunta ao usuário quantos intervalos deseja inserir
    printf("Quantos intervalos você deseja inserir? ");
    // Valida se a entrada é um número
    if (scanf("%d", &intervalsSize) != 1 || intervalsSize <= 0) {
        printf("Entrada inválida. Por favor, insira um número inteiro positivo.\n");
        return 1; // Encerra o programa com código de erro
    }

    // 2. Aloca memória dinamicamente para os intervalos com base na entrada
    int** intervals = (int**)malloc(intervalsSize * sizeof(int*));
    if (intervals == NULL) {
        fprintf(stderr, "Falha na alocação de memória.\n");
        return 1;
    }
    // O LeetCode exige este array, então o criamos
    int* intervalsColSize = (int*)malloc(intervalsSize * sizeof(int));
    if (intervalsColSize == NULL) {
        fprintf(stderr, "Falha na alocação de memória.\n");
        free(intervals);
        return 1;
    }

    // 3. Pede ao usuário para digitar cada intervalo
    printf("Digite os %d intervalos no formato 'inicio fim', um por linha:\n", intervalsSize);
    for (int i = 0; i < intervalsSize; i++) {
        intervalsColSize[i] = 2; // Cada intervalo tem 2 colunas
        intervals[i] = (int*)malloc(2 * sizeof(int));
        if (intervals[i] == NULL) {
            fprintf(stderr, "Falha na alocação de memória para o intervalo %d.\n", i);
            // Libera toda a memória alocada até agora antes de sair
            for (int j = 0; j < i; j++) {
                free(intervals[j]);
            }
            free(intervals);
            free(intervalsColSize);
            return 1;
        }

        printf("Intervalo %d: ", i + 1);
        if (scanf("%d %d", &intervals[i][0], &intervals[i][1]) != 2) {
            printf("Formato de entrada inválido. Encerrando.\n");
            // Libera a memória antes de sair
            for (int j = 0; j <= i; j++) {
                free(intervals[j]);
            }
            free(intervals);
            free(intervalsColSize);
            return 1;
        }
    }

    // 4. Chama a função da solução e imprime o resultado
    int returnSize;
    int* result = findRightInterval(intervals, intervalsSize, intervalsColSize, &returnSize);

    if (result != NULL) {
        printf("\nResultado final (array de índices):\n");
        print_array(result, returnSize);
    } else {
        printf("\nNão foi possível processar o resultado.\n");
    }

    // 5. Libera toda a memória alocada dinamicamente
    free(result);
    for (int i = 0; i < intervalsSize; i++) {
        free(intervals[i]); // Libera cada linha (cada intervalo)
    }
    free(intervals); // Libera o array de ponteiros
    free(intervalsColSize);

    return 0;
}