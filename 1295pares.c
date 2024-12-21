#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct {
    double x, y;
} Ponto;

// Função de comparação para ordenar os pontos pelo eixo X
int compararX(const void *a, const void *b) {
    Ponto *p1 = (Ponto *)a;
    Ponto *p2 = (Ponto *)b;
    return (p1->x < p2->x) ? -1 : (p1->x > p2->x);
}

// Função de comparação para ordenar os pontos pelo eixo Y
int compararY(const void *a, const void *b) {
    Ponto *p1 = (Ponto *)a;
    Ponto *p2 = (Ponto *)b;
    return (p1->y < p2->y) ? -1 : (p1->y > p2->y);
}

// Função para calcular a distância entre dois pontos
double distancia(Ponto a, Ponto b) {
    return hypot(a.x - b.x, a.y - b.y);
}

// Função para encontrar a menor distância em um conjunto de pontos por força bruta
double forcaBruta(Ponto pontos[], int n) {
    double menor_distancia = DBL_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = distancia(pontos[i], pontos[j]);
            if (dist < menor_distancia) {
                menor_distancia = dist;
            }
        }
    }
    return menor_distancia;
}

// Função para calcular a menor distância entre pontos na "faixa"
double faixaMaisProxima(Ponto faixa[], int tamanho, double d) {
    double menor_distancia = d;
    qsort(faixa, tamanho, sizeof(Ponto), compararY);

    for (int i = 0; i < tamanho; i++) {
        for (int j = i + 1; j < tamanho && (faixa[j].y - faixa[i].y) < menor_distancia; j++) {
            double dist = distancia(faixa[i], faixa[j]);
            if (dist < menor_distancia) {
                menor_distancia = dist;
            }
        }
    }
    return menor_distancia;
}

// Função recursiva principal para encontrar o par mais próximo
double parMaisProximoRecursivo(Ponto pontos[], int n) {
    if (n <= 3) {
        return forcaBruta(pontos, n);
    }

    int meio = n / 2;
    Ponto pontoMeio = pontos[meio];

    double dl = parMaisProximoRecursivo(pontos, meio);
    double dr = parMaisProximoRecursivo(pontos + meio, n - meio);

    double d = fmin(dl, dr);

    Ponto faixa[n];
    int faixa_tamanho = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(pontos[i].x - pontoMeio.x) < d) {
            faixa[faixa_tamanho++] = pontos[i];
        }
    }

    return fmin(d, faixaMaisProxima(faixa, faixa_tamanho, d));
}

// Função principal para encontrar o par mais próximo
double parMaisProximo(Ponto pontos[], int n) {
    qsort(pontos, n, sizeof(Ponto), compararX);
    return parMaisProximoRecursivo(pontos, n);
}

int main() {
    int n;

    while (scanf("%d", &n) && n != 0) {
        Ponto pontos[n];
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &pontos[i].x, &pontos[i].y);
        }

        double resultado = parMaisProximo(pontos, n);

        if (resultado >= 10000.0) {
            printf("INFINITY\n");
        } else {
            printf("%.4lf\n", resultado);
        }
    }

    return 0;
}
