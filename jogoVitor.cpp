#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10
#define SHIPS 5

void initialize_board(char board[ROWS][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board[i][j] = '-';
        }
    }
}

void print_board(char board[ROWS][COLS]) {
    int i, j;
    printf("  ");
    for (i = 0; i < COLS; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (i = 0; i < ROWS; i++) {
        printf("%c ", 'A' + i);
        for (j = 0; j < COLS; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void place_ships(char board[ROWS][COLS]) {
    int i, j, count = 0, row, col;
    char c;
    while (count < SHIPS) {
        printf("Enter row and column for ship %d (length %d): ", count + 1, SHIPS - count);
        scanf(" %c %d", &c, &col);
        row = c - 'A';
        col--;
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            printf("Invalid row or column!\n");
        } else if (board[row][col] != '-') {
            printf("There is already a ship there!\n");
        } else {
            board[row][col] = 'S';
            for (i = 1; i < SHIPS - count; i++) {
                if (row + i < ROWS && board[row + i][col] == '-') {
                    board[row + i][col] = 'S';
                } else if (row - i >= 0 && board[row - i][col] == '-') {
                    board[row - i][col] = 'S';
                } else if (col + i < COLS && board[row][col + i] == '-') {
                    board[row][col + i] = 'S';
                } else if (col - i >= 0 && board[row][col - i] == '-') {
                    board[row][col - i] = 'S';
                } else {
                    printf("Cannot place ship there!\n");
                    board[row][col] = '-';
                    i = SHIPS;
                }
            }
            if (board[row][col] == 'S') {
                count++;
            }
        }
        print_board(board);
    }
}

int check_shot(char board[ROWS][COLS], int row, int col) {
    if (board[row][col] == 'S') {
        board[row][col] = 'X';
        return 1;
    } else {
        board[row][col] = 'O';
        return 0;
    }
}

int main() {
    char player1_board[ROWS][COLS], player2_board[ROWS][COLS];
    int i, j, row, col, shots = 0, hits = 0, player = 1;
    char c;
    srand(time(NULL));
    initialize_board(player1_board);
    initialize_board(player2_board);
    printf("Battleship Game\n");
    printf("Player 1, place your ships:\n");
    place_ships(player1_board);
    printf("Player 2, place your ships:\n");
    place_ships(player2_board);
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
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
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
            if (hits < SHIPS) {
                player = 3 - player;
            }
        }
    } while (hits < SHIPS);
    printf("\nPlayer %d won in %d shots!\n", player, shots);
    return 0;
}
