#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define linhas 10
#define colunas 10
#define navios 5

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

void colocarNavios(char tabuleiro[linhas][colunas]) {
    int i, j, count = 0, linha, coluna;

    while (count < navios) {
        linha = rand() % linhas;
        coluna = rand() % colunas;

        if (tabuleiro[linha][coluna] == '-') {
            tabuleiro[linha][coluna] = 'S';
            for (i = 1; i < navios - count; i++) {
                if (linha + i < linhas && tabuleiro[linha + i][coluna] == '-') {
                    tabuleiro[linha + i][coluna] = 'S';
                } else {
                    break;
                }
            }
            count++;
        }
    }
}

int verificarTiro(char tabuleiro[linhas][colunas], int linha, int coluna) {
    if (tabuleiro[linha][coluna] == 'S') {
        tabuleiro[linha][coluna] = 'X';
        return 1;
    } else {
        tabuleiro[linha][coluna] = 'O';
        return 0;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    char player_board[linhas][colunas], computer_board[linhas][colunas];
    int i, j, linha, coluna, shots = 0, hits = 0, player = 1;
    char c;

    srand(time(NULL));

    inicializarTabuleiro(player_board);
    inicializarTabuleiro(computer_board);

    printf("Jogo de Batalha Naval\n");

    printf("Jogador, Coloque seus navios:\n");
    colocarNavios(player_board);

    printf("Máquina, Coloque seus navios:\n");
    colocarNavios(computer_board);

    do {
        printf("\nTabuleiro do jogador:\n");
        exibirTabuleiro(player_board);

        printf("\nTabuleiro da máquina:\n");
        exibirTabuleiro(computer_board);

        if (player == 1) {
            printf("Jogador, entre com a linha e a coluna para atirar: ");
            scanf(" %c %d", &c, &coluna);
            linha = c - 'A';
        } else {
            printf("Máquina está atirando...\n");
            linha = rand() % linhas;
            coluna = rand() % colunas;
            printf("A máquina atirou em %c%d\n", 'A' + linha, coluna + 1);
        }

        coluna--;

        if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
            printf("Linha ou coluna inválida!\n");
        } else {
            if (player == 1) {
                if (verificarTiro(computer_board, linha, coluna)) {
                    printf("Hit!\n");
                    hits++;
                } else {
                    printf("Miss!\n");
                }
            } else {
                if (verificarTiro(player_board, linha, coluna)) {
                    printf("Hit!\n");
                    hits++;
                } else {
                    printf("Miss!\n");
                }
            }
            shots++;

            if (hits < navios) {
                player = 3 - player; // Alternar entre jogador e máquina
            }
        }
    } while (hits < navios);

    if (player == 1) {
        printf("\nVocê ganhou em %d tiros!\n", shots);
    } else {
        printf("\nA máquina ganhou em %d tiros!\n", shots);
    }

    return 0;
}
