#include <stdio.h>

// Função para realizar os movimentos do jogo
int playGame(int arr[], int left, int right) {
    if (left >= right) {
        return 0; 
    }

    int mid = (left + right) / 2; 

    int swapsLeft = playGame(arr, left, mid); 
    int swapsRight = playGame(arr, mid + 1, right); 

    int inversoes = 0; 

    // Mesclar os subarrays ordenados
    int temp[right - left + 1];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] > arr[j]) {
            inversoes += (mid - i + 1);
            temp[k++] = arr[j++];
        } else {
            temp[k++] = arr[i++];
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
    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }

    return swapsLeft + swapsRight + inversoes;
}

int main() {
    int N;

    while (1) {
        // Leitura do tamanho do array
        scanf("%d", &N);

        if (N == 0) {
            break; // Fim da entrada
        }

        // Leitura dos elementos do array
        int arr[N];
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }

        // Determinar quem é o vencedor
        int totalSwaps = playGame(arr, 0, N - 1);

        // O vencedor é determinado pelo número total de movimentos
        if (totalSwaps % 2 == 0) {
            printf("Carlos\n");
        } else {
            printf("Marcelo\n");
        }
    }

    return 0;
}