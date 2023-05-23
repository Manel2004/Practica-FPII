#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PALABRA 9
#define MAX_PARAULES 10

typedef struct {
    int fila;
    int columna;
    int direccio;
} Trobada;

void benvinguda() {
    printf("******************************************************\n");
    printf("Us donem la benvinguda al joc de la sopa de lletres!\n");
    printf("Autors: xxxxx, yyyyy, zzzzz\n");
    printf("******************************************************\n");
}

void carregarParaules(FILE* fitxer, char paraules[MAX_PARAULES][MAX_PALABRA], int* numParaules) {
    char paraula[MAX_PALABRA];
    int i = 0;

    while (fgets(paraula, MAX_PALABRA, fitxer) != NULL) {
        paraula[strcspn(paraula, "\n")] = '\0';  // Eliminar el salto de línea
        strcpy(paraules[i], paraula);
        i++;
    }

    *numParaules = i;
}

void ordenarParaules(char paraules[MAX_PARAULES][MAX_PALABRA], int numParaules) {
    int i, j;
    char temp[MAX_PALABRA];

    for (i = 0; i < numParaules - 1; i++) {
        for (j = i + 1; j < numParaules; j++) {
            if (strcmp(paraules[i], paraules[j]) > 0) {
                strcpy(temp, paraules[i]);
                strcpy(paraules[i], paraules[j]);
                strcpy(paraules[j], temp);
            }
        }
    }
}

void mostrarParaules(char paraules[MAX_PARAULES][MAX_PALABRA], int numParaules) {
    int i;

    printf("Hi ha un total de %d paraules:\n", numParaules);
    for (i = 0; i < numParaules; i++) {
        printf("%s\n", paraules[i]);
    }
}

void mostrarSopaLetras(char sopa[MAX_PARAULES][MAX_PARAULES], int mida) {
    int i, j;

    printf("Sopa de lletres:\n");
    for (i = 0; i < mida; i++) {
        for (j = 0; j < mida; j++) {
            printf("%c ", sopa[i][j]);
        }
        printf("\n");
    }
}

int trobarParaula(char sopa[MAX_PARAULES][MAX_PARAULES], int mida, char paraula[MAX_PALABRA], Trobada* trobada) {
    int i, j, k, longitud;
    int encontrada;

    longitud = strlen(paraula);

    // Búsqueda horizontal hacia la derecha
    for (i = 0; i < mida; i++) {
        for (j = 0; j <= mida - longitud; j++) {
            encontrada = 1;
            for (k = 0; k < longitud; k++) {
                if (sopa[i][j + k] != paraula[k]) {
                    encontrada = 0;
                    break;
                }
            }
            if (encontrada == 1) {
                trobada->fila = i;
                trobada->columna = j;
                trobada->direccio = 1;
                return 1;
            }
        }
    }

    // Búsqueda horizontal hacia la izquierda
    for (i = 0; i < mida; i++) {
        for (j = mida - 1; j >= longitud - 1; j--) {
            encontrada = 1;
            for (k = 0; k < longitud; k++) {
                if (sopa[i][j - k] != paraula[k]) {
                    encontrada = 0;
                    break;
                }
            }
            if (encontrada == 1) {
                trobada->fila = i;
                trobada->columna = j;
                trobada->direccio = -1;
                return 1;
            }
        }
    }

    // Búsqueda vertical hacia abajo
    for (i = 0; i <= mida - longitud; i++) {
        for (j = 0; j < mida; j++) {
            encontrada = 1;
            for (k = 0; k < longitud; k++) {
                if (sopa[i + k][j] != paraula[k]) {
                    encontrada = 0;
                    break;
                }
            }
            if (encontrada == 1) {
                trobada->fila = i;
                trobada->columna = j;
                trobada->direccio = 2;
                return 1;
            }
        }
    }

    // Búsqueda vertical hacia arriba
    for (i = mida - 1; i >= longitud - 1; i--) {
        for (j = 0; j < mida; j++) {
            encontrada = 1;
            for (k = 0; k < longitud; k++) {
                if (sopa[i - k][j] != paraula[k]) {
                    encontrada = 0;
                    break;
                }
            }
            if (encontrada == 1) {
                trobada->fila = i;
                trobada->columna = j;
                trobada->direccio = -2;
                return 1;
            }
        }
    }

    return 0;
}

void mostrarSopaConTrobada(char sopa[MAX_PARAULES][MAX_PARAULES], int mida, Trobada trobada, char paraula[MAX_PALABRA]) {
    int i, j, k, fila, columna, direccio;

    fila = trobada.fila;
    columna = trobada.columna;
    direccio = trobada.direccio;

    printf("Sopa de lletres amb la paraula trobada marcada:\n");
    for (i = 0; i < mida; i++) {
        for (j = 0; j < mida; j++) {
            if (i == fila && j == columna) {
                for (k = 0; k < strlen(paraula); k++) {
                    printf("%c ", sopa[i][j]);
                    if (direccio == 1) {
                        j++;
                    } else if (direccio == -1) {
                        j--;
                    } else if (direccio == 2) {
                        i++;
                    } else if (direccio == -2) {
                        i--;
                    }
                }
                j--;
            } else {
                printf("%c ", sopa[i][j]);
            }
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    FILE* fitxer;
    char paraules[MAX_PARAULES][MAX_PALABRA];
    int numParaules, mida, i, trobada;
    char sopa[MAX_PARAULES][MAX_PARAULES];
    Trobada trobadaInfo;
    char paraula[MAX_PALABRA];

    if (argc != 2) {
        printf("Ús: %s <nom_fitxer>\n", argv[0]);
        return 1;
    }

    fitxer = fopen(argv[1], "r");
    if (fitxer == NULL) {
        printf("No s'ha pogut obrir el fitxer.\n");
        return 1;
    }

    benvinguda();

    carregarParaules(fitxer, paraules, &numParaules);
    fclose(fitxer);

    ordenarParaules(paraules, numParaules);

    mostrarParaules(paraules, numParaules);

    printf("Introdueix la mida de la sopa de lletres (entre 10 i 40): ");
    scanf("%d", &mida);

    // Generar la sopa de letras
    for (i = 0; i < mida; i++) {
        for (int j = 0; j < mida; j++) {
            sopa[i][j] = 'A' + rand() % 26;  // Generar una letra aleatoria en mayúscula
        }
    }

    mostrarSopaLetras(sopa, mida);

    while (1) {
        printf("Has trobat una paraula? (S/N): ");
        char resposta[2];
        scanf("%s", resposta);
        if (strcmp(resposta, "N") == 0 || strcmp(resposta, "n") == 0) {
            printf("Introdueix la paraula 'RENDICIO' per veure la solucio o una paraula trobada: ");
            scanf("%s", paraula);
            if (strcmp(paraula, "RENDICIO") == 0) {
                printf("Has decidit rendir-te. La solucio es:\n");
                mostrarSopaLetras(sopa, mida);
                break;
            } else {
                trobada = trobarParaula(sopa, mida, paraula, &trobadaInfo);
                if (trobada) {
                    printf("Enhorabona! Has trobat la paraula.\n");
                    mostrarSopaConTrobada(sopa, mida, trobadaInfo, paraula);
                } else {
                    printf("La paraula no ha estat trobada.\n");
                }
            }
        } else {
            printf("Introdueix la fila i columna inicial, i la direccio (1: dreta, -1: esquerra, 2: avall, -2: amunt): ");
            int fila, columna, direccio;
            scanf("%d %d %d", &fila, &columna, &direccio);
            trobadaInfo.fila = fila;
            trobadaInfo.columna = columna;
            trobadaInfo.direccio = direccio;
            mostrarSopaConTrobada(sopa, mida, trobadaInfo, paraules[i]);
            i++;
        }
    }

    return 0;
}
