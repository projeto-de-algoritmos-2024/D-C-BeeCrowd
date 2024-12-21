#include <stdio.h>
#include <string.h>

void divide_and_conquer(const char* str, int inicio, int fim) {
    // Caso base: string de um único caractere
    if (inicio == fim) {
        if (str[inicio] == '@') {
            putchar('a');
        } else if (str[inicio] == '&') {
            putchar('e');
        } else if (str[inicio] == '!') {
            putchar('i');
        } else if (str[inicio] == '*') {
            putchar('o');
        } else if (str[inicio] == '#') {
            putchar('u');
        } else {
            putchar(str[inicio]);
        }
        return;
    }

    // Dividindo a string ao meio
    int mid = (inicio + fim) / 2;

    // Aplicação recursiva nas metades
    divide_and_conquer(str, inicio, mid);
    divide_and_conquer(str, mid + 1, fim);
}

int main() {
    char str[1000];

    while (fgets(str, sizeof(str), stdin)) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        if (strlen(str) == 0) {
            break; 
        }

        divide_and_conquer(str, 0, strlen(str) - 1);
        putchar('\n');
    }

    return 0;
}
