#include <stdio.h>
#include <stdlib.h>

/**
 * Estrutura para armazenar o ponto de início de um intervalo
 * e seu índice original na lista de entrada.
 */
typedef struct {
    int start;
    int original_index;
} StartInfo;

/**
 * Função de comparação para qsort.
 * Compara dois elementos StartInfo com base em seus pontos de início.
 */
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
    // Alternativa mais concisa, mas com risco de overflow para números muito grandes:
    // return infoA->start - infoB->start;
}

/**
 * Nota: A assinatura da função segue o padrão do LeetCode.
 * O chamador deve liberar a memória do ponteiro retornado.
 * returnSize é um ponteiro de saída para informar o tamanho do array retornado.
 */
int* findRightInterval(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize) {
    // Define o tamanho do array de retorno
    *returnSize = intervalsSize;
    if (intervalsSize == 0) {
        return NULL;
    }

    // Aloca memória para o array de resultado
    int* result = (int*)malloc(intervalsSize * sizeof(int));
    if (result == NULL) {
        // Falha na alocação de memória
        *returnSize = 0;
        return NULL;
    }

    // 1. Criar e popular o array de structs StartInfo
    StartInfo* starts = (StartInfo*)malloc(intervalsSize * sizeof(StartInfo));
    if (starts == NULL) {
        // Falha na alocação, liberar o que já foi alocado
        free(result);
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < intervalsSize; i++) {
        starts[i].start = intervals[i][0];
        starts[i].original_index = i;
    }

    // 2. Ordenar o array de structs com base nos pontos de início
    qsort(starts, intervalsSize, sizeof(StartInfo), compareStartInfo);

    // 3. Iterar sobre cada intervalo original e usar busca binária
    for (int i = 0; i < intervalsSize; i++) {
        int end_point = intervals[i][1];
        
        // Implementação da busca binária (lower_bound)
        int low = 0;
        int high = intervalsSize - 1;
        int best_index = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2; // Evita overflow
            if (starts[mid].start >= end_point) {
                // Este é um candidato válido. Guardamos seu índice e tentamos
                // encontrar um ainda melhor (menor) à esquerda.
                best_index = starts[mid].original_index;
                high = mid - 1;
            } else {
                // O ponto de início é muito pequeno, precisamos procurar à direita.
                low = mid + 1;
            }
        }
        
        result[i] = best_index;
    }
    
    // Libera a memória do array auxiliar que não é mais necessário
    free(starts);
    
    return result;
}


// --- Função Principal para Teste ---
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

int main() {
    // Exemplo: intervals = [[3,4],[2,3],[1,2]]
    int intervalsSize = 3;
    int intervalsColSize[] = {2, 2, 2};
    
    // Alocando memória para o array de ponteiros
    int** intervals = (int**)malloc(intervalsSize * sizeof(int*));
    for(int i = 0; i < intervalsSize; i++) {
        intervals[i] = (int*)malloc(intervalsColSize[i] * sizeof(int));
    }

    // Populando os dados
    intervals[0][0] = 3; intervals[0][1] = 4;
    intervals[1][0] = 2; intervals[1][1] = 3;
    intervals[2][0] = 1; intervals[2][1] = 2;

    int returnSize;
    int* result = findRightInterval(intervals, intervalsSize, intervalsColSize, &returnSize);

    printf("Entrada: [[3,4],[2,3],[1,2]]\n");
    printf("Saída: ");
    print_array(result, returnSize); // Esperado: [-1, 0, 1]

    // Liberando a memória alocada
    free(result);
    for(int i = 0; i < intervalsSize; i++) {
        free(intervals[i]);
    }
    free(intervals);

    return 0;
}