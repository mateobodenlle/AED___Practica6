//AED - Practica6
//Solución con Backtracking
//Propietario: mateobodenlle

//Versión 0
//-----------------------------------//

//Librerías:
#include <stdio.h>
#include <stdlib.h>
//Constantes y globales
#define N 3 //Tamaño de la matriz
#define valorDefecto (-1)

//Definición de matriz
typedef int matriz[N][N];
matriz B = {{11,17,8},
            {9, 7, 6},
            {13,15,16}};

//Implementación de funciones de Backtracking
short criterio(int nivel, int s[N]) {
    for (int i = 0; i < nivel; i++)
        if (s[nivel] == s[i]) return 0;
    return 1;
}

int masHermanos(int nivel, int s[N]) {
    return s[nivel]<(N-1);
}

int retroceder(int *nivel, int s[N],int* bact){
    (*bact)-=B[*nivel][s[*nivel]];
    s[*nivel]=0;
    (*nivel)-=1;
}

int generar(int nivel, int s[N],int bact) {
    s[nivel]++;
    if (s[nivel]==0)
        bact+=B[nivel][s[nivel]];
    else
        bact+=B[nivel][s[nivel]]-B[nivel][s[nivel]-1];
}

int solucion(int nivel, int s[N]){
    return (nivel==(N-1) && criterio(nivel,s));
}

//Algoritmo de Backtracking
void backtracking(int s[N]){
    int nivel = 0;
    for (int i = 0; i < N; i++) s[i] = valorDefecto;
    int voa = -999;
    int soa[N] = {valorDefecto,valorDefecto,valorDefecto};
    int bact = 0;

    while(nivel!=-1){
        generar(nivel,s,bact);
        if (solucion(nivel,s) /*&& (bact>voa)*/){
            voa = bact;
            for (int i = 0; i<N; i++) soa[i] = s[i];
            printf("\nSolucion encontrada! \t"); for (int i = 0; i<N; i++) printf("%d ",s[i]);
        }
        if (criterio(nivel,s) && (nivel<(N-1)))
            nivel++;
        while (!masHermanos(nivel,s)&&(nivel>=0))
            retroceder(&nivel,s,&bact);

    }
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

    printf("\n\nFin del programa. Gracias.");
}
