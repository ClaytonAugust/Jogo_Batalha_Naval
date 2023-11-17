#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <stdio.h>

#define linhas 10
#define colunas 10
#define navios 5
//exibir tabuleiro ao iniciar o jogo
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
//parte da máquina
// Função para posicionar os navios da máquina aleatóriamente
// Função para posicionar os navios da máquina automaticamente
void posicionarNaviosMaquina(char tabuleiro[linhas][colunas]) {
    printf("A máquina está posicionando seus navios...\n");
    srand(time(NULL));
    for (int i = 0; i < navios; i++) {
        int linha, coluna;
        do {
            linha = rand() % linhas;
            coluna = rand() % colunas;
        } while (tabuleiro[linha][coluna] != '-');
        tabuleiro[linha][coluna] = 'M';
        for (int j = 1; j < navios - i; j++) {
            if (linha + j < linhas && tabuleiro[linha + j][coluna] == '-') {
                tabuleiro[linha + j][coluna] = 'M';
            } else if (linha - j >= 0 && tabuleiro[linha - j][coluna] == '-') {
                tabuleiro[linha - j][coluna] = 'M';
            } else if (coluna + j < colunas && tabuleiro[linha][coluna + j] == '-') {
                tabuleiro[linha][coluna + j] = 'M';
            } else if (coluna - j >= 0 && tabuleiro[linha][coluna - j] == '-') {
                tabuleiro[linha][coluna - j] = 'M';
            } else {
                i--;  // Se não for possível posicionar o navio, decrementa o índice e tenta novamente.
                break;
            }
        }
    }
}


//Parte de fazer o tabuleiro da posição onde está os návios do jogador
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
/*verificar aonde foi disparado se estiver com 'S' marcar 'X' para dizer que
foi atingido, senão coloca 'O' para dizer que errou e deixar marcado*/
int verificarTiro(char tabuleiro[linhas][colunas], int linha, int coluna) {
    if (tabuleiro[linha][coluna] == 'S') {
        tabuleiro[linha][coluna] = 'X';
        return 1;
    } else {
        tabuleiro[linha][coluna] = 'O';
        return 0;
    }
}

void fazerTiroMaquina(char tabuleiro[linhas][colunas]) {
    int linha, coluna;
    do {
        linha = rand() % linhas;
        coluna = rand() % colunas;
    } while (tabuleiro[linha][coluna] == 'X' || tabuleiro[linha][coluna] == 'O');
    
    printf("A máquina atira em %c%d: ", 'A' + linha, coluna + 1);

    if (verificarTiro(tabuleiro, linha, coluna)) {
        printf("Hit!\n");
    } else {
        printf("Miss!\n");
    }
}

//Função para o jogador colocar navios
void colocarNavios(char tabuleiro[linhas][colunas]) {
    int i, j, count = 0, linha, coluna;
    char c;
    while (count < navios) {
        printf("Coloque linha e coluna para colocar o navio %d (comprimento %d): ", count + 1, navios - count);
        scanf(" %c %d", &c, &coluna);

        linha = c - 'A';  /*Esta linha calcula a diferença entre o valor da variável c e o valor correspondente 
                            ao caractere 'A' na tabela ASCII. Isso é feito subtraindo o valor do caractere 'A' do valor do caractere armazenado em c. 
                            O resultado é atribuído à variável linha. Essa operação é frequentemente utilizada para converter um caractere em um valor
                            numérico que representa sua posição relativa no alfabeto.*/
                            
        coluna--;//Esta linha decrementa o valor da variável coluna em 1 unidade. O operador -- é o operador de decremento em C, e ele reduz o valor da variável em 1.
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

int main() {
    setlocale(LC_ALL, "Portuguese");
    char tabuleiro1[linhas][colunas], player1_board[linhas][colunas], player2_board[linhas][colunas];
    int i, j, linha, coluna, shots = 0, hits = 0, player = 1;
    char c;
    inicializarTabuleiro1(tabuleiro1);
    exibirTabuleiro1(tabuleiro1);
    srand(time(NULL));
    inicializarTabuleiro(player1_board);
    inicializarTabuleiro(player2_board);
    printf("Jogo de Batalha Naval\n");
    printf("Jogador1, Coloque seus navios:\n");
    colocarNavios(player1_board);
    printf("Jogador2, A máquina está posicionando seus navios...\n");
    posicionarNaviosMaquina(player2_board);

    do {
        printf("\nPlayer %d's tabuleiro:\n", player);
        if (player == 1) {
            exibirTabuleiro(player2_board);
        } else {
            exibirTabuleiro(player1_board);
        }

        if (player == 1) {
            printf("Player %d, enter linha and column to shoot: ", player);
            scanf(" %c %d", &c, &coluna);
            linha = c - 'A';
            coluna--;
        } else {
            fazerTiroMaquina(player1_board);
            linha = 0; // Atribuir um valor qualquer, pois não será utilizado para o jogador 2 (máquina).
            coluna = 0; // Atribuir um valor qualquer, pois não será utilizado para o jogador 2 (máquina).
        }

        if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
            printf("Invalid linha or column!\n");
        } else {
            if (player == 1) {
                if (verificarTiro(player2_board, linha, coluna)) {
                    printf("Hit!\n");
                    hits++;
                } else {
                    printf("Miss!\n");
                }
            } else {
                if (verificarTiro(player1_board, linha, coluna)) {
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