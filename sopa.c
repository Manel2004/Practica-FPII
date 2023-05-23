#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILAS 40
#define COLUMNAS 40



void benvinguda()
{
    printf("*****************************************************\n");
    printf("Us donem la benvinguda al joc de la sopa de lletres!\n");
    printf("Autors: Paula Recio, Manel Mendez, Roc Domingo\n");
    printf("*****************************************************\n");
}


/* void llegir_fitxer()
{
     FILE* lectura_arxiu;
    char paraules[100];
    
    lectura_arxiu = fopen("paraules.txt", "r");
    
    if (arxiu == NULL)
    {
        printf("S'ha produït un error durant l'obertura del fitxer");
    }
    else
    {
    
        while (fscanf()
    
    
        
    }
}

  */


int mida_taula()
{
    int mida;
    printf("De quina mida vols que sigui la sopa de lletres?\n");
    printf("RECORDATORI!! La mida de la sopa de lletres ha de ser de dimensions entre 10 i 40.\n");
    scanf("%d", &mida);

    while((mida < 10)||(mida > 40))
    {
        printf("Aquest valor no esta dins del rang.");
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
    
    return 0;
}
