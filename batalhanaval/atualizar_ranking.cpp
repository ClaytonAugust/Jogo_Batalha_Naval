#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 5
#define MAX_NAME_LENGTH 50
#define MAX_LINE_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int turns;
} Player;

void removeSpaceBeforeVenceu(char *name) {
    char *venceuPos = strstr(name, " venceu");
    if (venceuPos != NULL) {
        memmove(venceuPos + 1, venceuPos, strlen(venceuPos) + 1);
        *venceuPos = ' ';
    }
}

void readPlayersFromFile(Player players[MAX_LINES], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_LINES; ++i) {
        char line[MAX_LINE_LENGTH];
        if (fgets(line, sizeof(line), file) == NULL) {
            break;
        }

        removeSpaceBeforeVenceu(players[i].name);

        // Ajuste na leitura dos turnos
        int result = sscanf(line, "%s venceu em %d turnos!", players[i].name, &players[i].turns);

        if (result != 2) {
            fprintf(stderr, "Erro ao ler dados do arquivo na linha %d:\n%s", i + 1, line);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}

void writePlayersToFile(Player players[MAX_LINES], const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_LINES && players[i].name[0] != '\0'; ++i) {
        fprintf(file, "%s venceu em %d turnos!\n", players[i].name, players[i].turns);
    }

    fclose(file);
}

int comparePlayers(const void *a, const void *b) {
    return ((Player *)a)->turns - ((Player *)b)->turns;
}

int main() {
    Player players[MAX_LINES];
    int numPlayers;

    readPlayersFromFile(players, "ranking.txt");

    for (numPlayers = 0; numPlayers < MAX_LINES && players[numPlayers].name[0] != '\0'; ++numPlayers);

    qsort(players, numPlayers, sizeof(Player), comparePlayers);

    writePlayersToFile(players, "ranking.txt");

    return 0;
}
