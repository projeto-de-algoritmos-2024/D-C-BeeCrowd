#include <stdio.h>

// Função para mesclar dois subarrays e contar as inversões
int merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;  
    int j = mid + 1;
    int k = left;    
    int inversions = 0; 

    while ((i <= mid) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            // Inversão encontrada
            temp[k++] = arr[j++];
            inversions += (mid - i + 1);
        }
    }

    // Copiar os elementos restantes do subarray esquerdo, se houver
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copiar os elementos restantes do subarray direito, se houver
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copiar os elementos mesclados de volta para o array original
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inversions;
}

// Função para contar inversões usando a abordagem de mergesort
int countInversions(int arr[], int temp[], int left, int right) {
    int inversions = 0;

    if (left < right) {
        int mid = (left + right) / 2;

        // Contar inversões no subarray esquerdo
        inversions += countInversions(arr, temp, left, mid);

        // Contar inversões no subarray direito
        inversions += countInversions(arr, temp, mid + 1, right);

        // Mesclar os dois subarrays e contar as inversões
        inversions += merge(arr, temp, left, mid, right);
    }

    return inversions;
}

int main() {
    int t; // Número de test cases
    scanf("%d", &t);

    while (t--) {
        int l; // Comprimento do trem
        scanf("%d", &l);

        int arr[l]; // Array representando a ordem atual dos carriages
        int temp[l]; // Array temporário para mesclagem
        for (int i = 0; i < l; i++) {
            scanf("%d", &arr[i]);
        }

        // Calcular o número de inversões usando a abordagem de mergesort
        int swaps = countInversions(arr, temp, 0, l - 1);

        // Imprimir o resultado
        printf("Optimal train swapping takes %d swaps.\n", swaps);
    }

    return 0;
}