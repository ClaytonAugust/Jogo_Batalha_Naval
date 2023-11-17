#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

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
            printf("Linha ou coluna invalida!\n");
        } else if (tabuleiro[linha][coluna] != '-') {
            printf("Já existe um navio ai!\n");
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
                    printf("Não é possivel colocar o navio ai\n");
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
    printf("A máquina está posicionando seus navios...\n");
    srand(time(NULL));

    for (int i = 0; i < navios; i++) {
        int linha, coluna;
        do {
            linha = rand() % linhas;
            coluna = rand() % colunas;
        } while (tabuleiro[linha][coluna] != '-'
                || (linha > 0 && tabuleiro[linha - 1][coluna] == 'S')
                || (coluna > 0 && tabuleiro[linha][coluna - 1] == 'S')
                || (linha < linhas - 1 && tabuleiro[linha + 1][coluna] == 'S')
                || (coluna < colunas - 1 && tabuleiro[linha][coluna + 1] == 'S'));

        tabuleiro[linha][coluna] = 'S';

        for (int j = 1; j < navios - i; j++) {
            if (linha + j < linhas) {
                tabuleiro[linha + j][coluna] = 'S';
            }
        }
    }

}

void exibirTabuleiroMaquina(char tabuleiro[linhas][colunas]) {
    printf("  ");
    for (int i = 0; i < colunas; ++i) {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < linhas; ++i) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < colunas; ++j) {
            if (tabuleiro[i][j] == 'S') {
                printf("- ");
            } else if (tabuleiro[i][j] == 'X' || tabuleiro[i][j] == 'O') {
                printf("%c ", tabuleiro[i][j]);
            } else {
                printf("  "); 
            }
        }
        printf("\n");
    }
}

void limparBuffer(){
    int c;
    while ((c= getchar()) != '\n' && c != EOF);
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
    sleep(2);
    printf("Jogador, Coloque seus navios:\n");
	sleep(1);    
    colocarNavios(jogador_board);
    sleep(3);
    printf("Aguarde enquanto a maquina posiciona seus navios...\n");
    sleep(3);
    maquinaColocarNavios(maquina_board);
    sleep(3);
    do {
        printf("\n Tabuleiro do Jogador:\n");
        exibirTabuleiro(jogador_board);
        sleep(1);
        printf("\n Tabuleiro da Maquina:\n");
        exibirTabuleiroMaquina(maquina_board);
        printf("\n");

        if (jogador == 1) {
            printf("Vez do Jogador, digite a linha e coluna para atirar: ");
            scanf(" %c %d", &c, &coluna);
            limparBuffer();
            linha = c - 'A';
            coluna--;
        } else {
            printf("Aguarde enquanto a maquina decide o tiro...\n");
            linha = rand() % linhas;
            coluna = rand() % colunas;
        }
		sleep(7);
        if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
            printf("Linha ou coluna invalida!\n");
        } else {
            if (jogador == 1) {
                if (verificarTiro(maquina_board, linha, coluna)) {
                    printf("Acertou!\n");
                    hits++;
                    sleep(3);
                } else {
                    printf("Errou!\n");
                    sleep(3);
                }
            } else {
                if (verificarTiro(jogador_board, linha, coluna)) {
                    printf("Você foi atingido! Maquina acertou!\n");
                    hits++;
                    sleep(3);
                } else {
                    printf("Maquina errou!\n");
                    sleep(3);
                }
            }
            shots++;
            if (hits < navios) {
                jogador = 3 - jogador;
            }
        }
    } while (hits < navios);

    printf("\nJogador %d venceu em %d tiros!\n", jogador, shots);

    return 0;
}
