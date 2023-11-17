#include <stdio.h>

#define TAMANHO_TABULEIRO 10

void inicializarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Preencher o tabuleiro com espaços vazios ('0')
    for (int i = 0; i < TAMANHO_TABULEIRO; ++i) {
        for (int j = 0; j < TAMANHO_TABULEIRO; ++j) {
            tabuleiro[i][j] = '0';
        }
    }
}

void exibirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Exibir o tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; ++i) {
        for (int j = 0; j < TAMANHO_TABULEIRO; ++j) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializar o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Exibir o tabuleiro inicial
    printf("Tabuleiro Inicial:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
