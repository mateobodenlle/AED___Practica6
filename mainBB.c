//AED - Practica6
//Solución con Backtracking
//Propietario: mateobodenlle

//Versión 0
//-----------------------------------//

//Librerías:
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

//Constantes
#define N 3 //Tamaño de la matriz
//#define N 6
#define valorDefecto (-1)

//Variables globales (contadores)
int nNodos = 1, nPasosCriterio = 0, nPasosGenerar = 0, nPasosSolucion = 0, nPasosHermanos = 0, nPasosRetroceder = 0;

//Estructura para el nodo
//typedef struct {
//    int tupla [N];
//    int nivel;
//    int bact;
//    int usadas[N];
//    float CI, BE, CS;
//}TIPOELEMENTO;
//typedef TIPOELEMENTO NODO;

//Definición de matriz
typedef int matriz[N][N];

matriz B = {{11, 17, 8},
            {9,  7,  6},
            {13, 15, 16}};



/*matriz B = {{11,17,8,16,20,14},
            {9,7,6,12,15,18},
            {13,15,16,1,16,18},
            {21,24,28,17,26,20},
            {10,14,12,11,15,13},
            {12,20,19,13,22,17}};
 */
//Implementación de funciones de BB
void CI_trivial(NODO *nodo, matriz B) {
    nodo->CI = nodo->bact;
}

void CS_trivial(NODO *nodo, matriz B) {
    int max = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (B[i][j] > max)
                max = B[i][j];
    if (nodo->nivel!=-1) nodo->CS = nodo->bact + (N - nodo->nivel) * max;
    else nodo->CS = nodo->bact + (N)*max;
}

void BE(NODO *nodo) {
    nodo->BE = (nodo->CS + nodo->CI) / 2;
}

int asignacionVoraz(NODO *nodo) {
    int bacum = 0;
    int max = 0;
    int k;
    for (int i = nodo->nivel; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (B[i][j] > max && nodo->usadas[j] == 0) {
                max = B[i][j];
                k = j;
            }
        }
        nodo->usadas[k] = 1;
        bacum += B[i][k];
    }
    return bacum;
}

int maximosTareas(NODO *nodo) {
    int bacum = 0;
    int max = 0;
    int k;
    for (int i = nodo->nivel; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (B[i][j] > max) {
                max = B[i][j];
                k = j;
            }
        }
        nodo->usadas[k] = 1;
        bacum += B[i][k];
    }
    return bacum;
}

void CI_precisa(NODO *nodo, matriz B) {
    nodo->CI = nodo->bact + asignacionVoraz(nodo);
}

void CS_precisa(NODO *nodo, matriz B) {
    nodo->CS = nodo->bact + maximosTareas(nodo);
}

int solucion(NODO nodo) {
    return (nodo.nivel == N);
}

void seleccionar(TLISTA LNV,NODO *n, TPOSICION*s) {
    TPOSICION p = primeroLista(LNV);
    recuperarElementoLista(LNV, p, n);

    *s = p;

    while (p != finLista(LNV)){
        NODO max;
        recuperarElementoLista(LNV, p, &max);

        if (n->BE < max.BE) {
            (*n) = max;
            (*s) = p;
        }

        p = siguienteLista(LNV, p);
    }
}

NODO solAsignacionVoraz(NODO x, matriz B) {
    int bMax,t;

    for (int i = x.nivel+1; i<N; i++){
        bMax = -1;
        for (int j=0; j<N; j++){

            if (!x.usadas[j] && B[i][j] > bMax){
                bMax = B[i][j];
                t = j;
            }
        }
        nNodos++;
        x.tupla[i]=t;
        x.usadas[t] = 1;
        x.bact = x.bact + bMax;
    }
    x.nivel = N-1;
    return x;
}

void asignacionTrivial(matriz B, NODO *s) {
    //INICIALIZACIÓN
    TLISTA LNV;
    NODO raiz, x, y;
    TPOSICION p;
    float C = 0;

    //Inicialización nodo raíz
    raiz.bact = 0;
    raiz.nivel = -1;

    for (int i = 0; i < N; i++) raiz.tupla[i] = -1;
    for (int i = 0; i < N; i++) raiz.usadas[i] = 0;
    CI_trivial(&raiz, B);
    CS_trivial(&raiz, B);
    BE(&raiz);

    //Variable de poda
    C = raiz.CI;
    *s = raiz;

    //Inicialización variable
    crearLista(&LNV);
    //Guardar raíz
    insertarElementoLista(&LNV, primeroLista(LNV), raiz);

    //ALGORITMO
    int iteraciones = 0;
    while (!esListaVacia(LNV)) {
        iteraciones++;
        seleccionar(LNV,&x,&p);
        suprimirElementoLista(&LNV, p);

        if (x.CS > C) {
            for (int i = 0; i < N; i++) {
                y.nivel = x.nivel + 1;
                for (int j = 0; j < N; j++) y.tupla[j] = x.tupla[j];
                for (int j = 0; j < N; j++) y.usadas[j] = x.usadas[j];
                if (!x.usadas[i]) {
                    y.tupla[y.nivel] = i;
                    y.usadas[i] = 1;
                    y.bact = x.bact + B[y.nivel][i];

                    //Calcular CI, CS, BE para y
                    CI_trivial(&y, B);
                    CS_trivial(&y, B);
                    BE(&y);
                    if (solucion(y) && y.bact > s->bact) {
                        (*s) = y;
                        if (C < y.CI) C = y.bact;
                        else if (!solucion(y) && y.CS > C) {
                            insertarElementoLista(&LNV, primeroLista(LNV), y); //Aquí igual hay q usar finLista()
                            if (C < y.CI) C = y.CI;
                        }
                    }
                    nNodos++;
                }
            }
        }
    }
}

void asignacionPrecisa(matriz B, NODO *s) {
//INICIALIZACIÓN
    TLISTA LNV;
    NODO raiz, x, y;
    TPOSICION p;
    float C = 0;

    //Inicialización nodo raíz
    raiz.bact = 0;
    raiz.nivel = -1;

    for (int i = 0; i < N; i++) raiz.tupla[i] = -1;
    for (int i = 0; i < N; i++) raiz.usadas[i] = 0;
    CI_precisa(&raiz, B);
    CS_precisa(&raiz, B);
    BE(&raiz);

    nNodos++;
    //Variable de poda
    C = raiz.CI;
    *s = raiz;

    //Inicialización variable
    crearLista(&LNV);
    //Guardar raíz
    insertarElementoLista(&LNV, primeroLista(LNV), raiz);

    //ALGORITMO
    int iteraciones = 0;
    while (!esListaVacia(LNV)) {
        seleccionar(LNV,&x,&p);
        suprimirElementoLista(&LNV, primeroLista(LNV));

        if (x.CS > C) {
            for (int i = 0; i < N; i++) {
                y.nivel = x.nivel + 1;
                for (int j = 0; j < N; j++) y.tupla[j] = x.tupla[j];
                for (int j = 0; j < N; j++) y.usadas[j] = x.usadas[j];
                if (!x.usadas[i]) {
                    y.tupla[y.nivel] = i;
                    y.usadas[i] = 1;
                    y.bact = x.bact + B[y.nivel][i];

                    //Calcular CI, CS, BE para y
                    CI_precisa(&y, B);
                    CS_precisa(&y, B);
                    BE(&y);
                    if ((!solucion(y)) && y.CS>=C && y.CS==y.CI){
                        nNodos++;
                        y = solAsignacionVoraz(y, B);
                        *s=y;
                        return;
                    }
                    if (solucion(y) && y.bact > s->bact) {
                        *s = y;
                        if (y.bact > C) {
                            C = y.bact;
                        }
                    } else if (!solucion(y) && y.CS > C) {
                        insertarElementoLista(&LNV, primeroLista(LNV), y);
                        if (y.CI > C) {
                            C = y.CI;
                        }
                    }
                    nNodos++;
                    }
            }
        } else if (x.CS==C && x.CS==x.CI){
            y.nivel = x.nivel;
            for (int j = 0; j < N; j++) {
                y.tupla[j] = x.tupla[j];
                y.usadas[j] = x.usadas[j];
            }
            y= solAsignacionVoraz(y, B);
            *s=y;

            return;
        }
    }
    printf("\n");
    for (int i = 0; i<N; i++) printf("%2d",s->tupla[i]);
}




//Main
int main() {
    printf("Iniciando BB :)\nUsaremos la matriz:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d\t", B[i][j]);
        printf("\n");
    }
    NODO s;
    //Inicializar nodo
    /*s.bact=0;
    s.nivel=-1;
    for (int i = 0; i<N; i++) s.tupla[i] = 0;
    for (int i = 0; i<N; i++)s.usadas[i] = 0;
*/
    printf("\n");
    asignacionPrecisa(B,&s);
    for (int i = 0; i<N; i++) printf("%d ",s.tupla[i]);
    printf("\n\nFin del programa. Gracias.");
}
