#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define linhas 10
#define colunas 10

void inicializarTabuleiro(char tabuleiro[linhas][colunas]) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            tabuleiro[i][j] = '-';
        }
    }
}

void exibirTabuleiro(char tabuleiro[linhas][colunas]) {
    printf("  ");
    for (int i = 0; i < colunas; ++i) {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < linhas; ++i) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < colunas; ++j) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void colocarNavioAleatoriamente(char tabuleiro[linhas][colunas]) {
    srand(time(NULL));

    int linha = rand() % linhas;
    int coluna = rand() % colunas;

    tabuleiro[linha][coluna] = 'S';
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    char tabuleiro[linhas][colunas];
    inicializarTabuleiro(tabuleiro);

    colocarNavioAleatoriamente(tabuleiro);

    int tentativas = 0;

    while (1) {
        exibirTabuleiro(tabuleiro);

        char palpiteLinha;
        int palpiteColuna;

        printf("Faça um palpite (linha e coluna): ");
        scanf(" %c %d", &palpiteLinha, &palpiteColuna);

        int linha = palpiteLinha - 'A';
        int coluna = palpiteColuna - 1;

        if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
            printf("Palpite inválido. Tente novamente.\n");
            continue;
        }

        if (tabuleiro[linha][coluna] == 'S') {
            printf("Acertou!\n");
            break;
        } else {
            printf("Água. Tente novamente.\n");
        }

        ++tentativas;
    }

    printf("Parabéns! Você afundou o navio em %d tentativas.\n", tentativas);

    return 0;
}
