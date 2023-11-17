#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define linhas 10
#define colunas 10
#define navios 5

void inicializarTabuleiro1(char tabuleiro1[linhas][colunas]) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            tabuleiro1[i][j] = '-';
        }
    }
}

void exibirTabuleiro1(char tabuleiro1[linhas][colunas]) {
    printf("  ");
    for (int i = 0; i < colunas; ++i) {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < linhas; ++i) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < colunas; ++j) {
            printf("%c ", tabuleiro1[i][j]);
        }
        printf("\n");
    }
}

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
    char c;
    while (count < navios) {
        printf("Coloque linha e coluna para colocar o navio %d (comprimento %d): ", count + 1, navios - count);
        scanf(" %c %d", &c, &coluna);

        linha = c - 'A';
        coluna--;

        if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
            printf("Linha ou coluna inválida!\n");
        } else if (tabuleiro[linha][coluna] != '-') {
            printf("Já existe um navio lá!\n");
        } else {
            tabuleiro[linha][coluna] = 'S';
            for (i = 1; i < navios - count; i++) {
                if (linha + i < linhas && tabuleiro[linha + i][coluna] == '-') {
                    tabuleiro[linha + i][coluna] = 'S';
                } else if (linha - i >= 0 && tabuleiro[linha - i][coluna] == '-') {
                    tabuleiro[linha - i][coluna] = 'S';
                } else if (coluna + i < colunas && tabuleiro[linha][coluna + i] == '-') {
                    tabuleiro[linha][coluna + i] = 'S';
                } else if (coluna - i >= 0 && tabuleiro[linha][coluna - i] == '-') {
                    tabuleiro[linha][coluna - i] = 'S';
                } else {
                    printf("Não é possível colocar o navio lá!\n");
                    tabuleiro[linha][coluna] = '-';
                    i = navios;
                }
            }
            if (tabuleiro[linha][coluna] == 'S') {
                count++;
            }
        }
        exibirTabuleiro(tabuleiro);
    }
}

void maquinaColocarNavios(char tabuleiro[linhas][colunas]) {
    int count = 0;
    while (count < navios) {
        int linha = rand() % linhas;
        int coluna = rand() % colunas;

        if (tabuleiro[linha][coluna] == '-') {
            tabuleiro[linha][coluna] = 'S';
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
    char tabuleiro1[linhas][colunas], jogador_board[linhas][colunas], maquina_board[linhas][colunas];
    int linha, coluna, shots = 0, hits = 0, jogador = 1;
    char c;
    inicializarTabuleiro1(tabuleiro1);
    exibirTabuleiro1(tabuleiro1);
    srand(time(NULL));
    inicializarTabuleiro(jogador_board);
    inicializarTabuleiro(maquina_board);
    printf("Jogo de Batalha Naval\n");
    printf("Jogador, Coloque seus navios:\n");
    colocarNavios(jogador_board);
    printf("Aguarde enquanto a máquina posiciona seus navios...\n");
    maquinaColocarNavios(maquina_board);
    
    do {
        printf("\njogador's tabuleiro:\n");
        exibirTabuleiro(jogador_board);
        printf("\nMáquina's tabuleiro:\n");
        exibirTabuleiro(tabuleiro1);

        if (jogador == 1) {
            printf("jogador, enter linha and column to shoot: ");
            scanf(" %c %d", &c, &coluna);
            linha = c - 'A';
            coluna--;
        } else {
            printf("Aguarde enquanto a máquina decide o tiro...\n");
            linha = rand() % linhas;
            coluna = rand() % colunas;
        }

        if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
            printf("Invalid linha or column!\n");
        } else {
            if (jogador == 1) {
                if (verificarTiro(maquina_board, linha, coluna)) {
                    printf("Hit!\n");
                    hits++;
                } else {
                    printf("Miss!\n");
                }
            } else {
                if (verificarTiro(jogador_board, linha, coluna)) {
                    printf("Máquina acertou!\n");
                    hits++;
                } else {
                    printf("Máquina errou!\n");
                }
            }
            shots++;
            if (hits < navios) {
                jogador = 3 - jogador;
            }
        }
    } while (hits < navios);

    printf("\njogador %d won in %d shots!\n", jogador, shots);

    return 0;
}
