#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define linhas 10
#define colunas 10
#define navios 5

//Parte de fazer a tabela
void inicializarTabuleiro(char tabuleiro1[linhas][colunas]) {
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            tabuleiro1[i][j] = '-';
        }
    }
}

void exibirTabuleiro1(char Tabuleiro1[linhas][colunas]) {
    int i, j;
    printf("  ");
    for (i = 0; i < colunas; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (i = 0; i < linhas; i++) {
        printf("%c ", 'A' + i);
        for (j = 0; j < colunas; j++) {
            printf("%c ", Tabuleiro1[i][j]);
        }
        printf("\n");
    }
}
//Função para colocar navios
void colocarNavios(char Tabuleiro[linhas][colunas]) {
    int i, j, count = 0, linha, coluna;
    char c;
    while (count < navios) {
        printf("coloque a linha e a coluna para colocar o navil %d (comprimento %d): ", count + 1, navios - count);
        scanf(" %c %d", &c, &coluna);

        linha = c - 'A';
        coluna--;
        if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
            printf("linha ou coluna inválida!\n");
        } else if (Tabuleiro[linha][coluna] != '-') {
            printf("já existe um navil ai!\n");
        } else {
            Tabuleiro[linha][coluna] = 'S';
            for (i = 1; i < navios - count; i++) {
                if (linha + i < linhas && Tabuleiro[linha + i][coluna] == '-') {
                    Tabuleiro[linha + i][coluna] = 'S';
                } else if (linha - i >= 0 && Tabuleiro[linha - i][coluna] == '-') {
                    Tabuleiro[linha - i][coluna] = 'S';
                } else if (coluna + i < colunas && Tabuleiro[linha][coluna + i] == '-') {
                    Tabuleiro[linha][coluna + i] = 'S';
                } else if (coluna - i >= 0 && Tabuleiro[linha][coluna - i] == '-') {
                    Tabuleiro[linha][coluna - i] = 'S';
                } else {
                    printf("não é possível colocar o navil ai!\n");
                    Tabuleiro[linha][coluna] = '-';
                    i = navios;
                }
            }
            
        }
        exibirTabuleiro(Tabuleiro);
    }
}

int check_shot(char board[linhas][colunas], int linha, int col) {
    if (board[linha][col] == 'S') {
        board[linha][col] = 'X';
        return 1;
    } else {
        board[linha][col] = 'O';
        return 0;
    }
}

int main() {
    char player1_board[linhas][colunas], player2_board[linhas][colunas];
    int i, j, linha, col, shots = 0, hits = 0, player = 1;
    char c;
    srand(time(NULL));
    inicializarTabuleiro(player1_board);
    inicializarTabuleiro(player2_board);
    printf("Battleship Game\n");
    printf("Player 1, place your navios:\n");
    exibirTabuleiro(player1_board);
    printf("Player 2, place your navios:\n");
    exibirTabuleiro(player2_board);
    do {
        printf("\nPlayer %d's board:\n", player);
        if (player == 1) {
           exibirTabuleiro(player2_board);
        } else {
            exibirTabuleiro(player1_board);
        }
        printf("Player %d, enter linha and column to shoot: ", player);
        scanf(" %c %d", &c, &col);
        linha = c - 'A';
        col--;
        if (linha < 0 || linha >= linhas || col < 0 || col >= colunas) {
            printf("Invalid row or column!\n");
        } else {
            if (player == 1) {
                if (check_shot(player2_board, linha, col)) {
                    printf("Hit!\n");
                    hits++;
                } else {
                    printf("Miss!\n");
                }
            } else {
                if (check_shot(player1_board, linha, col)) {
                    printf("Hit!\n");
                    hits++;
                } else {
                    printf("Miss!\n");
                }
            }
            shots++;
            if (hits < navios) {
                player = 3 - player;
            }
        }
    } while (hits < navios);
    printf("\nPlayer %d won in %d shots!\n", player, shots);
    return 0;
}