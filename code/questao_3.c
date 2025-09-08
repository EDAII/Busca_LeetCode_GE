#include <stdio.h>
#include <stdlib.h> // Para malloc e free
#include <limits.h> // Para INT_MIN e INT_MAX
#include <math.h>   // Para fmax e fmin

// Função auxiliar para encontrar o máximo de dois inteiros
int max(int a, int b) {
    return a > b ? a : b;
}

// Função auxiliar para encontrar o mínimo de dois inteiros
int min(int a, int b) {
    return a < b ? a : b;
}

// O algoritmo principal permanece inalterado e otimizado.
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int m = nums1Size;
    int n = nums2Size;

    int low = 0;
    int high = m;

    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (m + n + 1) / 2 - partitionX;

        int maxX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minX = (partitionX == m) ? INT_MAX : nums1[partitionX];

        int maxY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minY = (partitionY == n) ? INT_MAX : nums2[partitionY];

        if (maxX <= minY && maxY <= minX) {
            if ((m + n) % 2 == 0) {
                return ((double)max(maxX, maxY) + min(minX, minY)) / 2.0;
            } else {
                return (double)max(maxX, maxY);
            }
        } else if (maxX > minY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }
    
    return -1.0; 
}

// Função main() agora interage com o usuário
int main() {
    int m, n, i;

    // Entrada da primeira matriz
    printf("Digite o tamanho da primeira matriz (m): ");
    scanf("%d", &m);
    
    // Alocação dinâmica de memória para a primeira matriz
    int *nums1 = (int *)malloc(m * sizeof(int));
    if (nums1 == NULL) {
        printf("Erro na alocacao de memoria.\n");
        return 1;
    }

    printf("Digite os %d elementos da primeira matriz (separados por espaco): ", m);
    for (i = 0; i < m; i++) {
        scanf("%d", &nums1[i]);
    }

    // Entrada da segunda matriz
    printf("Digite o tamanho da segunda matriz (n): ");
    scanf("%d", &n);
    
    // Alocação dinâmica de memória para a segunda matriz
    int *nums2 = (int *)malloc(n * sizeof(int));
    if (nums2 == NULL) {
        printf("Erro na alocacao de memoria.\n");
        // Libera a primeira matriz antes de sair
        free(nums1);
        return 1;
    }

    printf("Digite os %d elementos da segunda matriz (separados por espaco): ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &nums2[i]);
    }

    // Calcula e exibe o resultado
    printf("\nCalculando a mediana...\n");
    double result = findMedianSortedArrays(nums1, m, nums2, n);
    printf("A mediana das duas matrizes e: %f\n", result);

    // Libera a memória alocada dinamicamente
    free(nums1);
    free(nums2);

    return 0;
}