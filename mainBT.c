//AED - Practica6
//Solución con Backtracking
//Propietario: mateobodenlle

//Versión 0
//-----------------------------------//

//Librerías:
#include <stdio.h>
#include <stdlib.h>
//Constantes
//#define N 3 //Tamaño de la matriz
#define N 6
#define valorDefecto (-1)

//Variables globales (contadores)
int nNodos = 0, nPasosCriterio = 0, nPasosGenerar = 0, nPasosSolucion = 0, nPasosHermanos = 0, nPasosRetroceder = 0;

//Definición de matriz
typedef int matriz[N][N];
/*
matriz B = {{11,17,8},
            {9, 7, 6},
            {13,15,16}};
*/


matriz B = {{11,17,8,16,20,14},
            {9,7,6,12,15,18},
            {13,15,16,1,16,18},
            {21,24,28,17,26,20},
            {10,14,12,11,15,13},
            {12,20,19,13,22,17}};
 

//Implementación de funciones de Backtracking
int criterio(int nivel, int s[N], int usada[N]) {
    nPasosCriterio++;
    return usada[s[nivel]]==1;
}

int masHermanos(int nivel, int s[N]) {
    nPasosHermanos++;
    return s[nivel]<(N-1);
}

int retroceder(int *nivel, int s[N],int* bact,int usada[N]){
    nPasosRetroceder++;
    (*bact)-=B[*nivel][s[*nivel]];
    usada[s[*nivel]]--;
    s[*nivel]=valorDefecto;
    (*nivel)--;
}

int generar(int nivel, int s[N],int* bact, int usada[N]) {
    if (s[nivel]!=-1)
        usada[s[nivel]]--;
    nPasosGenerar++;
    s[nivel]++;
    usada[s[nivel]]++;
    //nNodos++;
    if (s[nivel]==0)
        (*bact)+=B[nivel][s[nivel]];
    else
        (*bact)+=B[nivel][s[nivel]]-B[nivel][s[nivel]-1];
}

int solucion(int nivel, int s[N], int usada[N]){
    nPasosSolucion++;
    return (nivel==(N-1) && criterio(nivel,s,usada));
}

//Algoritmo de Backtracking
void backtracking(int s[N]){
    int nivel = 0;
    for (int i = 0; i < N; i++) s[i] = valorDefecto;
    int voa = -999;
    int soa[N] = {valorDefecto,valorDefecto,valorDefecto};
    int bact = 0;
    int usada[N] = {0,0,0};

    while(nivel!=-1){
        generar(nivel,s,&bact,usada);
        if (solucion(nivel,s,usada) && (bact>voa)){
            voa = bact;
            for (int i = 0; i<N; i++) soa[i] = s[i];
            //printf("\nSolucion encontrada! \t"); for (int i = 0; i<N; i++) printf("%d ",s[i]);
        }
        if (criterio(nivel,s,usada)) {
            if (nivel < (N - 1))
                nivel++;
            nNodos++;
        }
        while (!masHermanos(nivel,s)&&(nivel>=0))
            retroceder(&nivel,s,&bact,usada);

    }
    for (int i = 0; i<N; i++) s[i] = soa[i];
}

//Main
int main() {
    printf("Iniciando Backtracking :)\nUsaremos la matriz:\n");
    int s[N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d\t", B[i][j]);
        printf("\n");
    }

    backtracking(s);
    printf("\nSolucion: \t\t");
    for (int i = 0; i<N; i++) printf("%d ",s[i]);

    printf("\nStats: %d %d %d %d %d %d\n", nNodos,nPasosCriterio,nPasosGenerar,nPasosSolucion,nPasosHermanos,nPasosRetroceder);

    printf("\n\nFin del programa. Gracias.");
}