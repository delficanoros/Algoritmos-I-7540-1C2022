#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "utiles.h"
#include "papeleo.h"


const char FUEGOS = 'F', MEDIAS = 'M', BOTELLAS_DE_GRITOS = 'G', INTERRUPTORES_AHUYENTA_RANDALL = 'I', MIKE = 'W';
const int FUEGOS_NIVEL_1 = 10, FUEGOS_NIVEL_2 = 5, FUEGOS_NIVEL_3 = 3, MEDIAS_NIVEL_1 = 5, MEDIAS_NIVEL_2 = 4, MEDIAS_NIVEL_3 = 3;
const int PAPELEOS_NIVEL_1 = 2, PAPELEOS_NIVEL_2 = 3, PAPELEOS_NIVEL_3 = 4;
const int GRITOS_NIVEL_1 = 4, GRITOS_NIVEL_2 = 3, GRITOS_NIVEL_3 = 2, INTERRUPTORES_NIVEL_1 = 1, INTERRUPTORES_NIVEL_2 = 1, INTERRUPTORES_NIVEL_3 = 0;
const int MARTILLOS_NIVEL_1 = 4, MARTILLOS_NIVEL_2 = 5, MARTILLOS_NIVEL_3 = 6, EXTINTORES_NIVEL_1 = 4, EXTINTORES_NIVEL_2 = 2, EXTINTORES_NIVEL_3 = 2;
const int TOPE_OBSTACULOS_1 = 15, TOPE_OBSTACULOS_2 = 9, TOPE_OBSTACULOS_3 = 6, TOPE_HERRAMIENTAS_1 = 5, TOPE_HERRAMIENTAS_2 = 4, TOPE_HERRAMIENTAS_3 = 2;
const int MARTILLOS_OBSEQUIO_JASMIN = 1, MOVIMIENTOS_OBSEQUIO_RAYO = 10, PAPELEOS_OBSEQUIO_STITCH = 1, FUEGOS_OBSEQUIO_OLAF_1 = 2, FUEGOS_OBSEQUIO_OLAF_2 = 1;

#define OLAF 'O'
#define STITCH 'S'
#define JASMIN 'J'
#define PAPELEOS 'P'
#define RAYO_MCQUEEN 'R'
#define VACIO ' '
#define PAREDES '*'
#define NIVEL_ACTUAL_1 1
#define NIVEL_ACTUAL_2 2
#define NIVEL_ACTUAL_3 3
#define NIVEL_1 0
#define NIVEL_2 1
#define NIVEL_3 2
#define MAXIMO_MOVIMIENTOS_NIVEL_1 40
#define MAXIMO_MOVIMIENTOS_NIVEL_2 30
#define MAXIMO_MOVIMIENTOS_NIVEL_3 20
#define DIMENSION_NIVEL_1 22
#define DIMENSION_NIVEL_2 17
#define DIMENSION_NIVEL_2 17
#define DIMENSION_NIVEL_3 12
#define DIMENSION_NIVEL_3 12
#define TERMINA_POSICION_OBJETOS 2
#define EMPIEZA_POSICION_OBJETOS 1
#define MAX_NIVELES 3
#define MAX_TERRENO 40
#define MAX_OBJETOS 100


/*Pre: se reciben las coordenadas de las paredes y obstaculos. 
 *Pos: calcula la distancia entre una coordenada de una pared con una coordenada de un obstáculo 
 *
 */
int calculo_distancia_manhattan(int fila_paredes, int columna_paredes, int fila_obstaculo, int columna_obstaculo){
    int distancia_completa = 0;
    int filas = abs(fila_paredes  - fila_obstaculo);
    int columnas = abs(columna_paredes - columna_obstaculo);
    distancia_completa = filas + columnas;
    return distancia_completa;
}
/*Pre: recibe los topes ya previamente inicializados en cero y el personaje del tp1.
 *Pos: le asigna a valores a algunos de los topes que se utilizan en el programa, varia dependiendo del nivel. Si el personaje adquirido en el primer desafio es Olaf (O) se elimina
 *         como obsequio una cierta cantidad de fuegos como recompensa del nivel uno y dos.
 */
void asignar_topes(int numero_nivel, int* tope_medias, int* tope_fuegos, int* tope_interruptores, int* tope_gritos, 
                int* tope_obstaculos, int* tope_herramientas, int* tope_papeleos, char personaje_tp1){
    if(numero_nivel == NIVEL_ACTUAL_1){
        (*tope_medias) = MEDIAS_NIVEL_1;
        (*tope_fuegos) = FUEGOS_NIVEL_1;
        (*tope_interruptores) = INTERRUPTORES_NIVEL_1;
        (*tope_gritos) = GRITOS_NIVEL_1;
        (*tope_obstaculos) = TOPE_OBSTACULOS_1;        
        (*tope_herramientas) = TOPE_HERRAMIENTAS_1; 
        (*tope_papeleos) = PAPELEOS_NIVEL_1;
        if(personaje_tp1 == OLAF){
            (*tope_fuegos) -= FUEGOS_OBSEQUIO_OLAF_1;
            (*tope_obstaculos) -= FUEGOS_OBSEQUIO_OLAF_1;
        }
    } else if(numero_nivel == NIVEL_ACTUAL_2){
        (*tope_medias) = MEDIAS_NIVEL_2;
        (*tope_fuegos) = FUEGOS_NIVEL_2;
        (*tope_interruptores) = INTERRUPTORES_NIVEL_2;
        (*tope_gritos) = GRITOS_NIVEL_2;
        (*tope_obstaculos) = TOPE_OBSTACULOS_2;
        (*tope_herramientas) = TOPE_HERRAMIENTAS_2;     
        (*tope_papeleos) = PAPELEOS_NIVEL_2;
        if(personaje_tp1 == OLAF){
            (*tope_fuegos) -= FUEGOS_OBSEQUIO_OLAF_2;
            (*tope_obstaculos) -= FUEGOS_OBSEQUIO_OLAF_2;
        }
    } else if(numero_nivel == NIVEL_ACTUAL_3){
        (*tope_medias) = MEDIAS_NIVEL_3;
        (*tope_fuegos) = FUEGOS_NIVEL_3;
        (*tope_interruptores) = INTERRUPTORES_NIVEL_3;
        (*tope_gritos) = GRITOS_NIVEL_3;
        (*tope_obstaculos) = TOPE_OBSTACULOS_3;
        (*tope_herramientas) = TOPE_HERRAMIENTAS_3;     
        (*tope_papeleos) = PAPELEOS_NIVEL_3;
    }
}

/* Pre: recibe las posiciones de las paredes y obstaculos.
 * Pos: devuelve verdadero si los fuegos son adyacentes pero no diagonales a una pared, utilizando el calculo manhattan. En caso contrario devuelve un false.
 */
bool fuegos_pared(char matriz_nivel[MAX_TERRENO][MAX_TERRENO], coordenada_t paredes[MAX_PAREDES], int fila, int columna, int tope_paredes){
    bool es_fuegos_pared = true;
    for(int i = 0; i < tope_paredes; i++){
           if(calculo_distancia_manhattan(paredes[i].fil, paredes[i].col, fila, columna) == 1){
                    es_fuegos_pared = false;
                } 
            }
    return es_fuegos_pared;
}

/* Pre: recibe el tamaño de la matriz dependiendo del nivel predeterminado y la fila y columna estan inicializadas en cero.
 * Pos: devuelve una posicion aleatoria dentro de la matriz donde ningun objeto o pared la ocupan. 
 */
void asignar_coordenada_aleatoria(int dimension, int* fila, int* columna, char matriz_nivel[MAX_TERRENO][MAX_TERRENO]){
    do{
        (*fila) = rand()% (dimension-TERMINA_POSICION_OBJETOS) + EMPIEZA_POSICION_OBJETOS;
        (*columna) = rand()% (dimension-TERMINA_POSICION_OBJETOS) + EMPIEZA_POSICION_OBJETOS;
    } while(matriz_nivel[*fila][*columna] != VACIO);
}

/* Pre: recibe la posicion aleatoria (no ocupada) dentro de la dimension de la matriz, que tipo de objeto es, su vector y la posicion dentro de el. 
 * Pos: asigna la posicion posicion en la matriz, su fila y columna, y el tipo de herramienta o obstaculo es.
 */
void asignar_valores(int fila, int columna, char matriz_nivel[MAX_TERRENO][MAX_TERRENO], char objeto, objeto_t objetos[MAX_OBJETOS], int posicion){
    matriz_nivel[fila][columna] = objeto;
    objetos[posicion].tipo = objeto;
    objetos[posicion].posicion.fil = fila;
    objetos[posicion].posicion.col = columna;

}

/*Pre: se recibe su respectiva dimension del nivel, el tope de las paredes y los topes correspondientes de cada obstaculo. Tambien, el vector de paredes y obstaculos, y la matriz.
 *Pos: se les asigna a las medias y fuegos una posicion aleatoria en el nivel en algun lugar donde no haya alguna pared u otro objeto. También se les asigna una constante que se utiliza para su posicion en la matriz:
 *      Fuego(F) y Medias(M). Además, en el caso de los fuegos se verifica que los fuegos esten próximos a una pared de forma adyacente y no diagonal. 
 */
void inicializar_obstaculos(coordenada_t paredes[MAX_PAREDES], int tope_paredes, objeto_t obstaculos[MAX_OBSTACULOS], int dimension, char matriz_nivel[MAX_TERRENO][MAX_TERRENO], 
                                int tope_medias, int tope_fuegos){
    int fila = 0, columna = 0;
    for(int i = 0; i < tope_medias; i++){
        char objeto = MEDIAS;
        asignar_coordenada_aleatoria(dimension, &fila, &columna, matriz_nivel);
        asignar_valores(fila, columna, matriz_nivel, objeto, obstaculos, i);
    }
    for(int i = tope_medias; i < tope_medias + tope_fuegos; i++){    
        char objeto = FUEGOS;
        do{
            asignar_coordenada_aleatoria(dimension, &fila, &columna, matriz_nivel);
        } while(fuegos_pared(matriz_nivel, paredes, fila, columna, tope_paredes) == true);
        asignar_valores(fila, columna, matriz_nivel, objeto, obstaculos, i);
    }
}
/* Pre: se recibe su respectiva dimension del nivel, el tope paredes correspondiente y los topes para cada herramienta. Ademas, se recibe el vector herramientas y la matriz.
 * Pos: le asigno una coordenada aleatoria que no se superponga con ningun otro objeto o pared y le asigno una constante a las herramientas. Esto se utiliza para su posición en la matriz:
 *      Botellas de grito(G) y Interruptores Ahuyenta Randall(I). 
 */
void inicializar_herramientas(objeto_t herramientas[MAX_HERRAMIENTAS], int dimension, char matriz_nivel[MAX_TERRENO][MAX_TERRENO], int tope_gritos, int tope_interruptores){
    int fila = 0, columna = 0;
    for(int i = 0; i < tope_gritos; i++){
        char objeto = BOTELLAS_DE_GRITOS;
        asignar_coordenada_aleatoria(dimension, &fila, &columna, matriz_nivel);
        asignar_valores(fila, columna, matriz_nivel, objeto, herramientas, i);
    }

    for(int j = tope_gritos; j < tope_gritos + tope_interruptores; j++){
        char objeto = INTERRUPTORES_AHUYENTA_RANDALL;
        asignar_coordenada_aleatoria(dimension, &fila, &columna, matriz_nivel);
        asignar_valores(fila, columna, matriz_nivel, objeto, herramientas, j);
    }

}
/*Pre: recibe el vector papeleos y la matriz con su dimension correspondiente. Tambien, el tope_papeleos para el nivel_actual, el personaje asignado en el primer tp y el numero del nivel.
 *Pos: le asigno una coordenada aleatoria a los Papeleos(P) evitando que se superponga con una pared u objeto, y le asigno una constante (P) para que puedan figurar en la matriz. Tambien si el nivel actual 
 *      es tres y el personaje del tp1 es stitch, se resta un papeleo del nivel como obsequio.
 */
void inicializar_papeleos(papeleo_t papeleos[MAX_PAPELEOS], int dimension, char matriz_nivel[MAX_TERRENO][MAX_TERRENO], int* tope_papeleos, char personaje_tp1, int numero_nivel){
    int fila = 0, columna = 0;
    if(personaje_tp1 == STITCH && numero_nivel == NIVEL_ACTUAL_3){
        (*tope_papeleos) = (*tope_papeleos) - PAPELEOS_OBSEQUIO_STITCH;
    }
    for(int i = 0; i < (*tope_papeleos); i++){
        asignar_coordenada_aleatoria(dimension, &fila, &columna, matriz_nivel);
        matriz_nivel[fila][columna] = PAPELEOS;
        papeleos[i].id_papeleo = PAPELEOS;
        papeleos[i].posicion.fil = fila;        
        papeleos[i].posicion.col = columna;
        papeleos[i].recolectado = false;
    }
}

/*Pre: se recibe un entero.
 *Pos: la funcion obtiene de un entero, su caracter.
 */
char casteo_id_papeleos(int numero){
    char caracter;
    caracter = (char) (numero);
    return caracter;
}


/*Pre: se recibe el nivel actual
 *Pos: se inicializan por nivel cada una de las características del jugador: cantidad de movimientos, martillos y extintores. 
 *     Los interruptores 'ahuyenta randall' comienzan inicialimente desactivados. La cantidad de movimientos restantes en un nivel, son acumulables para el proximo.
 */
void inicializar_jugador(jugador_t* jugador, int nivel_actual, juego_t* juego){
    jugador->posicion = juego->niveles[nivel_actual - 1].pos_inicial_jugador;
    jugador->ahuyenta_randall = false;
    if(nivel_actual == NIVEL_ACTUAL_1){
        jugador->movimientos = MAXIMO_MOVIMIENTOS_NIVEL_1;
        jugador->martillos = MARTILLOS_NIVEL_1;
        jugador->extintores = EXTINTORES_NIVEL_1;
    } else if(nivel_actual == NIVEL_ACTUAL_2){
        jugador->movimientos = MAXIMO_MOVIMIENTOS_NIVEL_1 + MAXIMO_MOVIMIENTOS_NIVEL_2;
        jugador->martillos = MARTILLOS_NIVEL_2;
        jugador->extintores = EXTINTORES_NIVEL_3;
    } else if(nivel_actual == NIVEL_ACTUAL_3){
        jugador->movimientos = MAXIMO_MOVIMIENTOS_NIVEL_1 + MAXIMO_MOVIMIENTOS_NIVEL_2 + MAXIMO_MOVIMIENTOS_NIVEL_3;
        jugador->martillos = MARTILLOS_NIVEL_3;
        jugador->extintores = EXTINTORES_NIVEL_3;
    }
}

/*Pre: Se recibe el personaje obtenido en el desafio de llegar a la facultad para poder dar el examén.
 *Pos: Si el personaje obtenido es Jasmín: se recibe un martillo extra en cada uno de los niveles, gracias al genio de la lámpara.
 *     Si el personaje obtenido es Rayo Mcqueen: se recibe 10 moviemientos extras en el nivel inicial, gracias a su extrema velocidad.
 */
void obsequios(juego_t* juego, char personaje_tp1){
    if(personaje_tp1 == JASMIN){
            juego->jugador.martillos += MARTILLOS_OBSEQUIO_JASMIN;     
    } else if(personaje_tp1 == RAYO_MCQUEEN){
        if(juego->nivel_actual == NIVEL_ACTUAL_1){
            juego->jugador.movimientos += MOVIMIENTOS_OBSEQUIO_RAYO;
        }
    } 
}

/*Pre: se recibe el nivel actual.
 *Pos: se determina el tamaño de la matriz de cada nivel
  */
int dimension_paredes(int nivel_actual){
    int dimension = -1;
    if(nivel_actual == NIVEL_ACTUAL_1){
        (dimension) = DIMENSION_NIVEL_1;
    } else if(nivel_actual == NIVEL_ACTUAL_2){
        (dimension) = DIMENSION_NIVEL_2;
    } else if(nivel_actual == NIVEL_ACTUAL_3){
        (dimension) = DIMENSION_NIVEL_3;
    }
    return dimension;
}

/*Pre: se recibe la matriz y su tope.
 *Pos: se recorre la matriz y se reemplaza los valores dentro por vacios(espacios).
 */
void inicializar_matriz(char matriz_nivel[MAX_TERRENO][MAX_TERRENO], int tope){
    for (int i = 0; i < tope; i++){
        for (int j = 0; j < tope; j++){
            matriz_nivel[i][j] = VACIO;
        }
    }
}

/*Pre: se recibe la dimension del nivel actual y la matriz ya llenada con las posicion del jugador, obstaculos, herramientas y papeleos.
 *Pos: se imprime por pantalla la matriz completa con sus paredes y las posiciones de los distintos objetos, papeleos y jugador.
 */ 
void imprimir_matriz_paredes(int dimension, char matriz_nivel[MAX_TERRENO][MAX_TERRENO]){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            printf(" %c ", matriz_nivel [i][j]);
        } printf("\n");
    }
}

/*Pre: se recibe la matriz con su respectivo tamaño
 *Pos: se determinan las paredes de la matriz utilizando un caracter especial.
 */
void inicializar_paredes(nivel_t nivel, char matriz_nivel[MAX_TERRENO][MAX_TERRENO]){
    for(int i = 0; i < (nivel.tope_paredes); i++){
        matriz_nivel[nivel.paredes[i].fil] [nivel.paredes[i].col] = PAREDES;
    }
}


/*Pre: se recibe el personaje previamente adquirido en el primer desafio
 *Pos: Se llama a los procedimientos que inicializan cada uno de los tres niveles y al jugador. Además, se llama al procedimiento que 
 *      entrega algunos de los obsquios adquiridos por el personaje obtenido en el desafio de poder llegar a la facultad
 */
void inicializar_juego(juego_t* juego, char personaje_tp1){
    juego->nivel_actual = NIVEL_ACTUAL_1;
    juego->personaje_tp1 = personaje_tp1;

    inicializar_nivel(&juego->niveles[NIVEL_1], NIVEL_ACTUAL_1, personaje_tp1);
    inicializar_nivel(&juego->niveles[NIVEL_2], NIVEL_ACTUAL_2, personaje_tp1);
    inicializar_nivel(&juego->niveles[NIVEL_3], NIVEL_ACTUAL_3, personaje_tp1);
    inicializar_jugador(&juego->jugador, juego->nivel_actual, juego);
    obsequios(juego, personaje_tp1);
}

/*Pre: Se recibe el numero del nivel a iniciar y el personaje adquirido en el TP1.
 *Pos: Se llama a la funcion de obtener_paredes ubicada en utiles.h, se determina el tamaño de la matriz del nivel y sus paredes. Además, se asignan 
 *     algunos de los topes utilizados en cada uno de los niveles, se inicializan los obstaculos, herramientas, papeleos y la coordenada aleatoria del jugador. 
 */
void inicializar_nivel(nivel_t* nivel, int numero_nivel, char personaje_tp1){
    obtener_paredes(numero_nivel, nivel->paredes, &(nivel->tope_paredes), &(nivel->pos_inicial_jugador));
    int dimension = -1;
    dimension = dimension_paredes(numero_nivel);
    char matriz_nivel[MAX_TERRENO][MAX_TERRENO];
    inicializar_matriz(matriz_nivel, dimension);
    inicializar_paredes(*nivel, matriz_nivel);
    
    matriz_nivel[nivel->pos_inicial_jugador.fil][nivel->pos_inicial_jugador.col] = MIKE;
    
    int tope_medias = 0, tope_fuegos = 0, tope_interruptores = 0, tope_gritos = 0;
    asignar_topes(numero_nivel, &tope_medias, &tope_fuegos, &tope_interruptores, &tope_gritos, &nivel->tope_obstaculos, &nivel->tope_herramientas, &nivel->tope_papeleos, personaje_tp1);

    inicializar_obstaculos(nivel->paredes, nivel->tope_paredes, nivel->obstaculos, dimension, matriz_nivel, tope_medias, tope_fuegos);
    inicializar_herramientas(nivel->herramientas, dimension, matriz_nivel, tope_gritos, tope_interruptores);
    inicializar_papeleos(nivel->papeleos, dimension, matriz_nivel, &nivel->tope_papeleos, personaje_tp1, numero_nivel);
}

/*Pre: Se reciben los niveles a imprimir, con sus respectivos elementos y jugador.
 *Pos: Se imprimen por pantalla cada matriz con su respectiva dimensión, posicion de las paredes, personajes, objetos, papeleos y jugador inicial.
 */
void imprimir_terreno(juego_t juego){
    int nivel = juego.nivel_actual-1;
    char matriz_nivel[MAX_TERRENO][MAX_TERRENO];
    int dimension = dimension_paredes(juego.nivel_actual);

    printf("Movimientos: %i\n", juego.jugador.movimientos);
    printf("Martillos: %i\n", juego.jugador.martillos);
    printf("Extintores: %i\n", juego.jugador.extintores);
    printf("Papeleos: %i\n", juego.niveles[nivel].tope_papeleos);

    inicializar_matriz(matriz_nivel, dimension);
    inicializar_paredes(juego.niveles[nivel], matriz_nivel);

    matriz_nivel[juego.niveles[nivel].pos_inicial_jugador.fil][juego.niveles[nivel].pos_inicial_jugador.col] = MIKE;
    
    for(int i = 0; i < juego.niveles[nivel].tope_obstaculos; i++){
        matriz_nivel[juego.niveles[nivel].obstaculos[i].posicion.fil][juego.niveles[nivel].obstaculos[i].posicion.col] = juego.niveles[nivel].obstaculos[i].tipo;
    }
    for(int i = 0; i < juego.niveles[nivel].tope_herramientas; i++){
        matriz_nivel[juego.niveles[nivel].herramientas[i].posicion.fil][juego.niveles[nivel].herramientas[i].posicion.col] = juego.niveles[nivel].herramientas[i].tipo;
    }
    for(int i = 0; i < juego.niveles[nivel].tope_papeleos; i++){
        matriz_nivel[juego.niveles[nivel].papeleos[i].posicion.fil][juego.niveles[nivel].papeleos[i].posicion.col] = casteo_id_papeleos(juego.niveles->papeleos[i].id_papeleo);
    }
    imprimir_matriz_paredes(dimension, matriz_nivel);
}