#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#define linhas 10
#define colunas 10
#define navios 5

void atualizarRanking(char *arquivo, char *jogador_nome, int jogador_turnos) {
    FILE *ranking = fopen(arquivo, "a");
    fprintf(ranking, "%s venceu em %d turnos!\n", jogador_nome, jogador_turnos);
    fclose(ranking);
}

void inicializarTabuleiroVisivel(char tabuleiro_visivel[linhas][colunas]) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            tabuleiro_visivel[i][j] = '-';
        }
    }
}

void exibirTabuleiroVisivel(char tabuleiro_visivel[linhas][colunas]) {
    printf("  ");
    for (int i = 0; i < colunas; ++i) {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < linhas; ++i) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < colunas; ++j) {
            printf("%c ", tabuleiro_visivel[i][j]);
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

void exibirAcertosMaquina(char tabuleiro_visivel[linhas][colunas], char machine_tabuleiro[linhas][colunas]) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (machine_tabuleiro[i][j] == 'S') {
                tabuleiro_visivel[i][j] = '-';
            } else {
                tabuleiro_visivel[i][j] = machine_tabuleiro[i][j];
            }
        }
    }
}

void colocarNavios(char tabuleiro[linhas][colunas]) {
    int i, j, count = 0, linha, coluna;
    char c;
    while (count < navios) {
        sleep(2);
        printf("Coloque linha e coluna para colocar o navio %d (comprimento %d): ", count + 1, navios - count);
        scanf(" %c %d", &c, &coluna);

        linha = c - 'A';
        coluna--;

        if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
            printf("Linha ou coluna inválida!\n");
        } else if (tabuleiro[linha][coluna] != '-') {
            printf("Já existe um navio aí!\n");
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
                    printf("Não é possível colocar o navio aí\n");
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

void posicionarNaviosMaquina(char tabuleiro[linhas][colunas]) {
    printf("A máquina está posicionando seus navios...\n");
    sleep(2);
    for (int i = 0; i < navios; i++) {
        int linha, coluna;
        do {
            linha = rand() % linhas;
            coluna = rand() % colunas;
        } while (tabuleiro[linha][coluna] != '-');
        tabuleiro[linha][coluna] = 'S';
        for (int j = 1; j < navios - i; j++) {
            if (linha + j < linhas && tabuleiro[linha + j][coluna] == '-') {
                tabuleiro[linha + j][coluna] = 'S';
            } else if (linha - j >= 0 && tabuleiro[linha - j][coluna] == '-') {
                tabuleiro[linha - j][coluna] = 'S';
            } else if (coluna + j < colunas && tabuleiro[linha][coluna + j] == '-') {
                tabuleiro[linha][coluna + j] = 'S';
            } else if (coluna - j >= 0 && tabuleiro[linha][coluna - j] == '-') {
                tabuleiro[linha][coluna - j] = 'S';
            } else {
                i--; 
                break;
            }
        }
    }
}

int verificarTiro(char tabuleiro[linhas][colunas], int linha, int coluna) {
    if (tabuleiro[linha][coluna] == 'S') {
        tabuleiro[linha][coluna] = 'X';
        return 1;
    } else if(tabuleiro[linha][coluna] == 'X'){
        tabuleiro[linha][coluna] = 'X';
        return 0;
    } else{
        tabuleiro[linha][coluna] = 'O';
        return 0;
    }
}

int main() {
    
    setlocale(LC_ALL, "Portuguese");
    
    char tabuleiro_visivel[linhas][colunas], jogador_tabuleiro[linhas][colunas], maquina_tabuleiro[linhas][colunas];
    int resposta, linha, coluna, acertos_jogador = 0, acertos_maquina = 0, jogador_turnos = 0, maquina_turnos = 0, hits = 0, jogador = 1;
    char c, jogador_nome[50];

    printf("\n1-JOGAR\n 2-RANKING\n 3-CREDITOS\n 4-SAIR\n");
    scanf("%d", &resposta);
    
    if (resposta == 1) {
        printf("Jogo de Batalha Naval\n");
        sleep(3);
        printf("Digite o seu nome:");
        scanf("%s", jogador_nome);
        inicializarTabuleiroVisivel(tabuleiro_visivel);
        exibirTabuleiroVisivel(tabuleiro_visivel);
        sleep(2);
        srand(time(NULL));
        inicializarTabuleiro(jogador_tabuleiro);
        inicializarTabuleiro(maquina_tabuleiro);
        printf("%s, Coloque os seus navios:\n", jogador_nome);   
        colocarNavios(jogador_tabuleiro);
        sleep(3);
        printf("Aguarde enquanto a máquina posiciona seus navios...\n");
        posicionarNaviosMaquina(maquina_tabuleiro);
        sleep(5);
        do {
            printf("\n Tabuleiro de %s:\n", jogador_nome);
            exibirTabuleiro(jogador_tabuleiro);
            sleep(3);
            printf("\n Tabuleiro da Máquina:\n");
            exibirAcertosMaquina(tabuleiro_visivel, maquina_tabuleiro);
            exibirTabuleiro(tabuleiro_visivel);
            sleep(3);
            if (jogador == 1) {
                printf("Vez de %s, digite a linha e coluna para atirar: ", jogador_nome);
                scanf(" %c %d", &c, &coluna);
                linha = c - 'A';
                coluna--;
                jogador_turnos++;
            } else {
                printf("Aguarde enquanto a máquina decide o tiro...\n");
                linha = rand() % linhas;
                coluna = rand() % colunas;
                maquina_turnos++;
            }
            sleep(2);   
            if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
                printf("Linha ou coluna inválida!\n");
            } else {
                if (jogador == 1){
                    if (verificarTiro(maquina_tabuleiro, linha, coluna)) {
                        sleep(2);
                        printf("Acertou!\n");
                        acertos_jogador++;
                    } else {
                        sleep(2);
                        printf("Errou!\n");
                    }
                } else {
                    if (verificarTiro(jogador_tabuleiro, linha, coluna)) {
                        sleep(2);
                        printf("%s foi atingido! Máquina acertou!\n", jogador_nome);
                        acertos_maquina++;
                    } else {
                        sleep(2);
                        printf("Máquina errou!\n");
                    }
                };
            }
            sleep(3);
            if (acertos_jogador >= 15){
                printf("%s venceu em %d turnos!\n", jogador_nome, jogador_turnos);
                atualizarRanking("ranking.txt", jogador_nome, jogador_turnos);
                break;
            } else if (acertos_maquina >= 15){
                printf("A máquina venceu em %d turnos!\n", maquina_turnos);
                break;
            }
            jogador = 3 - jogador;
            
        } while(1);
    }
    if (resposta == 2) {
    	int status = system("atualizar_ranking.exe");
        FILE *ranking = fopen("ranking.txt", "r");
        char caractere;
        while ((caractere = fgetc(ranking)) != EOF) {
            printf("%c", caractere);
        }
        fclose(ranking);
    }
    else if (resposta == 3) {
        FILE *creditos = fopen("creditos.txt", "r");
        char caractere;
        while ((caractere = fgetc(creditos)) != EOF) {
            printf("%c", caractere);
        }
        fclose(creditos);
    }

    return 0;
}
