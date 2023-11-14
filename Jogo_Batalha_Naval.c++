#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define linhas 10
#define colunas 10
#define navios 5

//Parte de fazer a tabela
void initialize_board(char board[linhas][colunas]) {
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            board[i][j] = '-';
        }
    }
}

void print_board(char board[linhas][colunas]) {
    int i, j;
    printf("  ");
    for (i = 0; i < colunas; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (i = 0; i < linhas; i++) {
        printf("%c ", 'A' + i);
        for (j = 0; j < colunas; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
//Função para colocar navios
void place_navios(char board[linhas][colunas]) {
    int i, j, count = 0, row, col;
    char c;
    while (count < navios) {
        printf("Enter row and column for ship %d (length %d): ", count + 1, navios - count);
        scanf(" %c %d", &c, &col);
        row = c - 'A';
        col--;
        if (row < 0 || row >= linhas || col < 0 || col >= colunas) {
            printf("Invalid row or column!\n");
        } else if (board[row][col] != '-') {
            printf("There is already a ship there!\n");
        } else {
            board[row][col] = 'S';
            for (i = 1; i < navios - count; i++) {
                if (row + i < linhas && board[row + i][col] == '-') {
                    board[row + i][col] = 'S';
                } else if (row - i >= 0 && board[row - i][col] == '-') {
                    board[row - i][col] = 'S';
                } else if (col + i < colunas && board[row][col + i] == '-') {
                    board[row][col + i] = 'S';
                } else if (col - i >= 0 && board[row][col - i] == '-') {
                    board[row][col - i] = 'S';
                } else {
                    printf("Cannot place ship there!\n");
                    board[row][col] = '-';
                    i = navios;
                }
            }
            if (board[row][col] == 'S') {
                count++;
            }
        }
        print_board(board);
    }
}

int check_shot(char board[linhas][colunas], int row, int col) {
    if (board[row][col] == 'S') {
        board[row][col] = 'X';
        return 1;
    } else {
        board[row][col] = 'O';
        return 0;
    }
}

int main() {
    char player1_board[linhas][colunas], player2_board[linhas][colunas];
    int i, j, row, col, shots = 0, hits = 0, player = 1;
    char c;
    srand(time(NULL));
    initialize_board(player1_board);
    initialize_board(player2_board);
    printf("Battleship Game\n");
    printf("Player 1, place your navios:\n");
    place_navios(player1_board);
    printf("Player 2, place your navios:\n");
    place_navios(player2_board);
    do {
        printf("\nPlayer %d's board:\n", player);
        if (player == 1) {
            print_board(player2_board);
        } else {
            print_board(player1_board);
        }
        printf("Player %d, enter row and column to shoot: ", player);
        scanf(" %c %d", &c, &col);
        row = c - 'A';
        col--;
        if (row < 0 || row >= linhas || col < 0 || col >= colunas) {
            printf("Invalid row or column!\n");
        } else {
            if (player == 1) {
                if (check_shot(player2_board, row, col)) {
                    printf("Hit!\n");
                    hits++;
                } else {
                    printf("Miss!\n");
                }
            } else {
                if (check_shot(player1_board, row, col)) {
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