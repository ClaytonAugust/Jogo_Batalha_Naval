#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_TABULEIRO 10
#define NUM_NAVIOS 5

// Função para criar o tabuleiro vazio
void criarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = '-';
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para posicionar os navios do jogador
void posicionarNaviosJogador(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Posicione seus navios:\n");
    for (int i = 0; i < NUM_NAVIOS; i++) {
        int linha, coluna;
        do {
            printf("Digite a linha (0-9): ");
            scanf("%d", &linha);
            printf("Digite a coluna (0-9): ");
            scanf("%d", &coluna);

            if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO && tabuleiro[linha][coluna] == '-') {
                tabuleiro[linha][coluna] = 'X';
                break;
            } else {
                printf("Posição inválida. Tente novamente.\n");
            }
        } while (1);
    }
}

// Função para posicionar os navios da máquina
void posicionarNaviosMaquina(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("A máquina está posicionando seus navios...\n");
    srand(time(NULL));
    for (int i = 0; i < NUM_NAVIOS; i++) {
        int linha, coluna;
        do {
            linha = rand() % TAMANHO_TABULEIRO;
            coluna = rand() % TAMANHO_TABULEIRO;
        } while (tabuleiro[linha][coluna] != '-');
        tabuleiro[linha][coluna] = 'M';
    }
}

// Função principal do jogo
void jogoBatalhaNaval() {
    printf("Bem-vindo ao jogo de Batalha Naval!\n");

    // Criação dos tabuleiros
    char tabuleiroJogador[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    char tabuleiroMaquina[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Posicionamento dos navios
    criarTabuleiro(tabuleiroJogador);
    criarTabuleiro(tabuleiroMaquina);
    posicionarNaviosJogador(tabuleiroJogador);
    posicionarNaviosMaquina(tabuleiroMaquina);

    // Loop principal do jogo
    while (1) {
        // Exibir tabuleiro do jogador
        printf("Seu tabuleiro:\n");
        exibirTabuleiro(tabuleiroJogador);

        // Exibir tabuleiro da máquina (escondendo os navios)
        printf("Tabuleiro da Máquina:\n");
        for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
            for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
                if (tabuleiroMaquina[i][j] == 'M') {
                    printf("O ");
                } else {
                    printf("%c ", tabuleiroMaquina[i][j]);
                }
            }
            printf("\n");
        }
        printf("\n");

        // Verificar vitória ou derrota
        int jogadorGanhou = 1, maquinaGanhou = 1;
        for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
            for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
                if (tabuleiroMaquina[i][j] == 'M') {
                    jogadorGanhou = 0;
                }
                if (tabuleiroJogador[i][j] == 'X') {
                    maquinaGanhou = 0;
                }
            }
        }
        if (jogadorGanhou) {
            printf("Parabéns! Você venceu!\n");
            break;
        } else if (maquinaGanhou) {
            printf("Você perdeu! A máquina venceu.\n");
            break;
        }

        // Turno do jogador
        while (1) {
            int linhaTiro, colunaTiro;
            printf("Digite a linha para o tiro (0-9): ");
            scanf("%d", &linhaTiro);
            printf("Digite a coluna para o tiro (0-9): ");
            scanf("%d", &colunaTiro);

            if (linhaTiro >= 0 && linhaTiro < TAMANHO_TABULEIRO && colunaTiro >= 0 && colunaTiro < TAMANHO_TABULEIRO) {
                if (tabuleiroMaquina[linhaTiro][colunaTiro] == 'M') {
                    printf("Você acertou um navio da máquina!\n");
                    tabuleiroMaquina[linhaTiro][colunaTiro] = 'X';
                } else if (tabuleiroMaquina[linhaTiro][colunaTiro] == '-') {
                    printf("Você errou o tiro.\n");
                    tabuleiroMaquina[linhaTiro][colunaTiro] = 'O';
                } else {
                    printf("Você já atirou nessa posição. Tente novamente.\n");
                    continue;
                }
                break;
            } else {
                printf("Posição inválida. Tente novamente.\n");
            }
        }

        // Turno da máquina
        while (1) {
            int linhaTiroMaquina = rand() % TAMANHO_TABULEIRO;
            int colunaTiroMaquina = rand() % TAMANHO_TABULEIRO;

            if (tabuleiroJogador[linhaTiroMaquina][colunaTiroMaquina] == 'X') {
                continue; // A máquina já atirou nessa posição, tentar novamente
            }

            if (tabuleiroJogador[linhaTiroMaquina][colunaTiroMaquina] == '-') {
                printf("A máquina acertou em (%d, %d)!\n", linhaTiroMaquina, colunaTiroMaquina);
                tabuleiroJogador[linhaTiroMaquina][colunaTiroMaquina] = 'X';
            } else {
                printf("A máquina errou o tiro em (%d, %d).\n", linhaTiroMaquina, colunaTiroMaquina);
                tabuleiroJogador[linhaTiroMaquina][colunaTiroMaquina] = 'O';
            }

            break;
        }
    }
}

// Função principal
int main() {
    jogoBatalhaNaval();
    return 0;
}
