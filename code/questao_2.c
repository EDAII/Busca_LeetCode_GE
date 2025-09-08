int findMin(int* numero, int numeroTamanho) {
    int l = 0, r = numeroTamanho - 1;

    while (l < r) {
        int m = l + (r - l) / 2;
        if (numero[m] < numero[r]) {
            r = m;
        } else if (numero[m] > numero[r]) {
            l = m + 1;
        } else {
            r--;
        }
    }
    return numero[l];
}

// Em casos de muita repetição a complexidade fica O(n), mesmo a busca binária tendo complexidade O(logN)