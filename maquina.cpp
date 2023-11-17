//parte da máquina
// Função para posicionar os navios da máquina aleatóriamente
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
    }
}
