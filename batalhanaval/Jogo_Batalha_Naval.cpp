#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#define linhas 10
#define colunas 10
#define navios 5

// Função para atualizar o arquivo de ranking com o nome do jogador e o número de turnos que ele levou para vencer.
void atualizarRanking(char *arquivo, char *jogador_nome, int jogador_turnos) {
    FILE *ranking = fopen(arquivo, "a"); // Esse comando vai abrir o ranking.txt como editavel.
    fprintf(ranking, "%s venceu em %d turnos!\n", jogador_nome, jogador_turnos); // Então armazenara o dado dessa frase, utilizando o nome do jogador e também os turnos.
    fclose(ranking);
}

// Função para inicializar o tabuleiro visível da máquina com espaços vazios.
void inicializarTabuleiroVisivel(char tabuleiro_visivel[linhas][colunas]) {
    for (int i = 0; i < linhas; ++i) { // Essa função utiliza o I como um indice para as linhas.
        for (int j = 0; j < colunas; ++j) {// Essa função utiliza o J como um indice para as colunas.
            tabuleiro_visivel[i][j] = '-';// Aonde ele da o valor de "-" e então aumenta o J, no final deixando algo como uma matriz de "-".
        }
    }
}

// Função para exibir o tabuleiro visível da máquina.
void exibirTabuleiroVisivel(char tabuleiro_visivel[linhas][colunas]) {
    // Exibir os números das colunas.
	printf("  ");
    for (int i = 0; i < colunas; ++i) { // Essa função utiliza o I como um indice para as colunas.
        printf("%d ", i + 1);
    }
    printf("\n");
	
	// Exibir o tabuleiro do jogo.
    for (int i = 0; i < linhas; ++i) { // Essa função utiliza o I como um indice para as linhas.
        printf("%c ", 'A' + i);
        for (int j = 0; j < colunas; ++j) { // Essa função utiliza o I como um indice para as colunas.
            printf("%c ", tabuleiro_visivel[i][j]); // Se printa cada espaço com o valor que ele tem no vetor.
        }
        printf("\n"); // Quebra a linha
    }
}


// Função para inicializar o tabuleiro do jogador com espaços vazios
void inicializarTabuleiro(char tabuleiro[linhas][colunas]) {
    for (int i = 0; i < linhas; ++i) {  // Essa função utiliza o I como um indice para as linhas.
        for (int j = 0; j < colunas; ++j) { // Essa função utiliza o J como um indice para as colunas.
            tabuleiro[i][j] = '-'; // Aonde ele da o valor de "-" e então aumenta o J, no final deixando algo como uma matriz de "-".
        }
    }
}

// Função para exibir o tabuleiro do jogador.
void exibirTabuleiro(char tabuleiro[linhas][colunas]) {
	// Exibir os números das colunas
    printf("  ");
    for (int i = 0; i < colunas; ++i) { // Essa função utiliza o I como um indice para as colunas.
        printf("%d ", i + 1); // Se printa cada espaço com o valor que ele tem no Vetor.
    }
    printf("\n"); // Quebra a linha
    
	// Exibir o tabuleiro do jogo
    for (int i = 0; i < linhas; ++i) { // Essa função utiliza o I como um indice para as linhas.
        printf("%c ", 'A' + i);
        for (int j = 0; j < colunas; ++j) { // Essa função utiliza o J como um indice para as colunas.
            printf("%c ", tabuleiro[i][j]); // Se printa cada espaço com o valor que ele tem no Vetor.
        }
        printf("\n"); // Quebra a linha
    }
}

// Função para exibir os acertos da máquina no tabuleiro visível.
void exibirAcertosMaquina(char tabuleiro_visivel[linhas][colunas], char machine_tabuleiro[linhas][colunas]) {
    for (int i = 0; i < linhas; ++i) {  // Essa função utiliza o I como um indice para as linhas.
        for (int j = 0; j < colunas; ++j) { // Essa função utiliza o J como um indice para as colunas.
            if (machine_tabuleiro[i][j] == 'S') { // Se no tabuleiro da maquina estiver com "S", ele vai copiar como '-'.
                tabuleiro_visivel[i][j] = '-';
            } else {
                tabuleiro_visivel[i][j] = machine_tabuleiro[i][j]; // Se não for um navio ('S'), ele copiará, servindo para mostrar o "O" e o "X".
            }
        }
    }
}

// Função para posicionar navios no tabuleiro do jogador.
void colocarNavios(char tabuleiro[linhas][colunas]) {
    int i, j, count = 0, linha, coluna;
    char c;
    while (count < navios) { // Looping enquanto o contador for menor que os navios.
        sleep(2); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
        printf("Coloque linha e coluna para colocar o navio %d (comprimento %d): ", count + 1, navios - count); // Vai falando o comprimento do navio e diminuindo conforme o contador.
        scanf(" %c %d", &c, &coluna); // Armazena a linha e a coluna

        linha = c - 'A';
        coluna--; // Diminui a coluna.

        if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) { // Se não for dito um número de 1 até 10 ou uma coluna de A até F.
            printf("Linha ou coluna inválida!\n"); 
        } else if (tabuleiro[linha][coluna] != '-') { // Se o campo não for invalido, porém não for algo "em branco" no caso '-', então tem um navio ali.
            printf("Já existe um navio aí!\n"); 
        } else {
            tabuleiro[linha][coluna] = 'S'; // A linha e coluna vai receber o 'S' que significa que um navio foi colocado
            for (i = 1; i < navios - count; i++) { // Caso não caiba o navio no padrão, que é pra cima, então vai usar os espaços pra baixo.
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
                count++; // Aumenta o contador
            }
        }
        exibirTabuleiro(tabuleiro); // Mostra o tabuleiro com os navios posicionados
    }
}

void posicionarNaviosMaquina(char tabuleiro[linhas][colunas]) {
    printf("A máquina está posicionando seus navios...\n");
    sleep(2); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
    for (int i = 0; i < navios; i++) { // Codigo rodará até o indice ser igual a navios.
        int linha, coluna;
        do {
            linha = rand() % linhas; // Será sorteado a posição da linha.
            coluna = rand() % colunas; // Será sorteado a posição da coluna.
        } while (tabuleiro[linha][coluna] != '-');  // Enquanto a linha e coluna for '-' (em branco)
        tabuleiro[linha][coluna] = 'S';
        for (int j = 1; j < navios - i; j++) { // Aqui ele checa as posições e caso não tenha como colocar pra cima, ele coloca pra baixo.
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
    if (tabuleiro[linha][coluna] == 'S') { // Se a linha e coluna for um 'S' (Navio) então o 'S' virara 'X'.
        tabuleiro[linha][coluna] = 'X';
        return 1; 
    } else if(tabuleiro[linha][coluna] == 'X'){
        tabuleiro[linha][coluna] = 'X'; // Se a linha e coluna for 'X' é porque já foi acertada, então continuará 'X'.
        return 0;
    } else{
        tabuleiro[linha][coluna] = 'O'; // Se a linha e coluna não for 'S' e nem 'X' é porque foi tiro ao oceano, então virará 'O'.
        return 0;
    }
}

int main() {
    
    setlocale(LC_ALL, "Portuguese");
    
    char tabuleiro_visivel[linhas][colunas], jogador_tabuleiro[linhas][colunas], maquina_tabuleiro[linhas][colunas];
    int resposta, linha, coluna, acertos_jogador = 0, acertos_maquina = 0, jogador_turnos = 0, maquina_turnos = 0, hits = 0, jogador = 1;
    char c, jogador_nome[50];

    printf("\n1-JOGAR\n 2-RANKING\n 3-CREDITOS\n 4-SAIR\n"); // Menu, aonde cada escolha vai ser usada como um caminho diferente.
    scanf("%d", &resposta); // Armazena a resposta
    
    if (resposta == 1) { // Se a resposta for JOGAR(1), então começara o jogo Batalha Naval.
        printf("Jogo de Batalha Naval\n");
        sleep(3); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
        printf("Digite o seu nome:"); 
        scanf("%s", jogador_nome); // Armazena o nome do Jogador.
        inicializarTabuleiroVisivel(tabuleiro_visivel);  // Inicia o tabuleiro visivel da máquina.
        exibirTabuleiroVisivel(tabuleiro_visivel); // Exibe um tabuleiro em branco
        sleep(2); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
        srand(time(NULL)); // Comando utilizado para resetar o sorteador do srand, anteriormente usado para colocar os navios de máquina, isso impede que o codigo se repita.
        inicializarTabuleiro(jogador_tabuleiro);  // Inicia o tabuleiro do jogador.
        inicializarTabuleiro(maquina_tabuleiro); // Inicia o tabuleiro da máquina.
        printf("%s, Coloque os seus navios:\n", jogador_nome);  
        colocarNavios(jogador_tabuleiro); // Inicia a função de colocar os navios.
        sleep(3); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
        printf("Aguarde enquanto a máquina posiciona seus navios...\n");
        posicionarNaviosMaquina(maquina_tabuleiro); // Inicia a função de posicionar navios da maquina.
        sleep(5); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
        do {
            printf("\n Tabuleiro de %s:\n", jogador_nome);
            exibirTabuleiro(jogador_tabuleiro); // Inicia a função de mostrar o tabuleiro do jogador.
            sleep(3); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
            printf("\n Tabuleiro da Máquina:\n");
            exibirAcertosMaquina(tabuleiro_visivel, maquina_tabuleiro); // Inicia a função de mostrar o tabuleiro da máquina.
            exibirTabuleiro(tabuleiro_visivel);
            sleep(3); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
            if (jogador == 1) { // Se o jogador for 1, significa que é a sua vez de jogar, o 1 e o 2 é utilizado pra simplificar o conceito de turnos.
                printf("Vez de %s, digite a linha e coluna para atirar: ", jogador_nome);
                scanf(" %c %d", &c, &coluna); // Armazena a linha e coluna que o jogador quer atirar.
                linha = c - 'A';
                coluna--;
                jogador_turnos++; // É adcionado o turno para o jogador, sendo posteriormente usado para Ranking.
            } else {
                printf("Aguarde enquanto a máquina decide o tiro...\n");
                linha = rand() % linhas; // Máquina sorteia a linha que vai atirar de maneira aleatoria.
                coluna = rand() % colunas; // Máquina sorteia a coluna que vai atirar de maneira aleatoria.
                maquina_turnos++; // É adcionado o turno para a maquina, porém não utilizado para Ranking.
            }
            sleep(2); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.    
            if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) { // Se não for uma linha existente, logo é invalida.
                printf("Linha ou coluna inválida!\n");
            } else {
                if (jogador == 1){
                    if (verificarTiro(maquina_tabuleiro, linha, coluna)) { // Aqui o codigo procura se a função retorna true (1).
                        sleep(2); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
                        printf("Acertou!\n"); // Se o codigo retornar 1, logo um navio inimigo foi acertado!
                        acertos_jogador++; // É adcionado um acerto para o jogador, aonde será utilizado posteriormente para vencer o jogo.
                    } else { // Caso o codigo retorne falso.
                        sleep(2); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
                        printf("Errou!\n"); // Se o codigo retornar 0, logo o tiro errou!
                    }
                } else {
                    if (verificarTiro(jogador_tabuleiro, linha, coluna)) { // Aqui o codigo procura se a função retorna true (1).
                        sleep(2); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
                        printf("%s foi atingido! Máquina acertou!\n", jogador_nome);  // Se o codigo retornar 1, logo o seu navio foi acertado!
                        acertos_maquina++; // É adcionado um acerto para a máquina, aonde será utilizado posteriormente para vencer o jogo.
                    } else {// Caso o codigo retorne falso.
                        sleep(2); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
                        printf("Máquina errou!\n"); // Se o codigo retornar 0, logo o tiro errou!
                    }
                };
            }
            sleep(3); // Uma pausa usando o comando sleep, puramente "cosmetico", para não ficar tão rapido o codigo.
            if (acertos_jogador >= 15){ // A cada final de loop, ele observa se os acertos chegaram igual ou maior que 15, significando que não resta mais navios inimigos.
                printf("%s venceu em %d turnos!\n", jogador_nome, jogador_turnos); // Mostra a mensagem final na tela, do nome e também os turnos levados para a vítoria.
                atualizarRanking("ranking.txt", jogador_nome, jogador_turnos); // Puxa a função para então adcionar o resultado da partida no Ranking.
                break;
            } else if (acertos_maquina >= 15){ // A cada final de loop, ele observa se os acertos chegaram igual ou maior que 15, significando que não resta mais navios do jogador.
                printf("A máquina venceu em %d turnos!\n", maquina_turnos); // Mostra a mensagem final na tela, da quantidades de turnos que a máquina levou pra vencer.
                break;
            }
            jogador = 3 - jogador; // É usado todo final de loop pra trocar a vez, se em um loop era a vez do jogador (1) logo o codigo com a soma, vai mudar para 2, sendo a vez da máquina.
            
        } while(1); //É um Do While "infinito", apenas se encerrando caso ou o jogador ou máquina consiga 15 acertos.
    }
    if (resposta == 2) { // Se o úsuario escolher para ver o Ranking(2) então fará esse IF.
    	int status = system("atualizar_ranking.exe"); // O codigo rodará o atualizar_ranking.exe, um programa separado aonde organiza o ranking, colocando ele de forma ascendente, aonde o menor número(turno) fica em cima//
        FILE *ranking = fopen("ranking.txt", "r"); // O ranking.txt será aberto apenas para leitura.
        char caractere;
        while ((caractere = fgetc(ranking)) != EOF) { //Enquanto não for final do arquivo (END OF FILE), ele estará pegando os caracteres.
            printf("%c", caractere); // O codigo mostrará o Ranking atual.
        }
        fclose(ranking); // Fecha o arquivo ranking.txt
    }
    else if (resposta == 3) { // Se o úsuario escolher para ver os Creditos(3) então fará esse IF.
        FILE *creditos = fopen("creditos.txt", "r"); // O creditos.txt será aberto apenas para leitura.
        char caractere;
        while ((caractere = fgetc(creditos)) != EOF) { //Enquanto não for final de arquivo (END OF FILE), ele estará pegando os caracteres.
            printf("%c", caractere);// O codigo mostrará os creditos.
        }
        fclose(creditos); // Fecha o arquivo creditos.txt
    }
}
