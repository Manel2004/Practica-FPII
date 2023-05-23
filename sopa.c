#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILAS 40
#define COLUMNAS 40

#define MAX_PALABRA 20



void benvinguda()
{
    printf("*****************************************************\n");
    printf("Us donem la benvinguda al joc de la sopa de lletres!\n");
    printf("Autors: Paula Recio, Manel Mendez, Roc Domingo\n");
    printf("*****************************************************\n");
}



void rendicio (char paraula[])
{
    if(paraula[]=='RENDICIO')
    {
        break;
    }
}


void leerPalabrasDeArchivo(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char palabra[MAX_WORD_LENGTH];
    while (fscanf(archivo, "%s", palabra) == 1) {
        printf("%s\n", palabra);
    }

    fclose(archivo);
}



int mida_taula()
{
    int mida;
    printf("De quina mida vols que sigui la sopa de lletres?\n");
    printf("RECORDATORI!! La mida de la sopa de lletres ha de ser de dimensions entre 10 i 40.\n");
    scanf("%d", &mida);

    while((mida < 10)||(mida > 40))
    {
        printf("Aquest valor no esta dins del rang. Torna a posar-la: ");
        scanf("%d", &mida);
    }
    return mida;
}



void generar_sopa_letras(char sopa[FILAS][COLUMNAS], int mida)
{

    char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i, j;
    
    // Generar letras aleatorias en la sopa
    for (i = 0; i < mida; i++) {
        for (j = 0; j < mida; j++) {
            sopa[i][j] = letras[rand() % 26];
        }
    }
}

void mostrar_sopa_letras(char sopa[FILAS][COLUMNAS], int mida)
{
    int i, j;
    
    // Mostrar la sopa en la consola
    for (i = 0; i < mida; i++) {
        for (j = 0; j < mida; j++) {
            printf("%c ", sopa[i][j]);
        }
        printf("\n");
    }
}



void insertarPalabra(char sopa[FILAS][COLUMNAS], char palabra[MAX_PALABRA], int fila, int columna, int direccion) {
    int longitud = strlen(palabra);
    int i;

    switch (direccion) {
        case 0:  // Horizontal hacia la derecha
            for (i = 0; i < longitud; i++) {
                sopa[fila][columna + i] = palabra[i];
            }
            break;
        case 1:  // Vertical hacia abajo
            for (i = 0; i < longitud; i++) {
                sopa[fila + i][columna] = palabra[i];
            }
            break;
        case 2:  // Diagonal hacia abajo y hacia la derecha
            for (i = 0; i < longitud; i++) {
                sopa[fila + i][columna + i] = palabra[i];
            }
            break;
        // Puedes agregar más direcciones según tus necesidades
    }
}













int main()
{
    char sopa[FILAS][COLUMNAS];
    
    benvinguda();
    
    int mida;
    mida = mida_taula();
    
    // Semilla para generar números aleatorios
    srand(time(NULL));
    
    // Generar la sopa de letras
    generar_sopa_letras(sopa, mida);
    
    // Mostrar la sopa de letras en la consola
    mostrar_sopa_letras(sopa, mida);
    
    insertarPalabra()
    
    
    
    return 0;
}
