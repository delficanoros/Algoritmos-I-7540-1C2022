#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "utiles.h"
#include "papeleo.h"


const char FUEGOS = 'F';
const char MEDIAS = 'M';
const char BOTELLAS_DE_GRITOS = 'G';
const char INTERRUPTORES_AHUYENTA_RANDALL = 'I';
const char MIKE = 'W';
const char USAR_MARTILLO = 'Z';
const char USAR_EXTINTOR = 'C';
const char ACCION_IZQUIERDA = 'A';
const char ACCION_DERECHA = 'D';
const char ACCION_ARRIBA = 'W';
const char ACCION_ABAJO = 'S';
const char ROTACION_HORARIA = 'E';
const char ROTACION_ANTIHORARIA = 'Q';
const int FUEGOS_NIVEL_1 = 10, FUEGOS_NIVEL_2 = 5, FUEGOS_NIVEL_3 = 3;
const int MEDIAS_NIVEL_1 = 5, MEDIAS_NIVEL_2 = 4, MEDIAS_NIVEL_3 = 3;
const int PAPELEOS_NIVEL_1 = 2, PAPELEOS_NIVEL_2 = 3, PAPELEOS_NIVEL_3 = 4;
const int GRITOS_NIVEL_1 = 4, GRITOS_NIVEL_2 = 3, GRITOS_NIVEL_3 = 2;
const int INTERRUPTORES_NIVEL_1 = 1, INTERRUPTORES_NIVEL_2 = 1, INTERRUPTORES_NIVEL_3 = 0;
const int MARTILLOS_NIVEL_1 = 4, MARTILLOS_NIVEL_2 = 5, MARTILLOS_NIVEL_3 = 6;
const int EXTINTORES_NIVEL_1 = 4, EXTINTORES_NIVEL_2 = 2, EXTINTORES_NIVEL_3 = 2;
const int TOPE_OBSTACULOS_1 = 15, TOPE_OBSTACULOS_2 = 9, TOPE_OBSTACULOS_3 = 6;
const int TOPE_HERRAMIENTAS_1 = 5, TOPE_HERRAMIENTAS_2 = 4, TOPE_HERRAMIENTAS_3 = 2;
const int MARTILLOS_OBSEQUIO_JASMIN = 1, MOVIMIENTOS_OBSEQUIO_RAYO = 10, PAPELEOS_OBSEQUIO_STITCH = 1, FUEGOS_OBSEQUIO_OLAF_1 = 2, FUEGOS_OBSEQUIO_OLAF_2 = 1;
const int GANA_MOVIMIENTOS_BOTELLAS = 7;
const int PIERDE_MOVIMIENTOS_MEDIAS = 10;
const int MOVIMIENTOS_DIVISIBLE_RANDALL_1 = 7, MOVIMIENTOS_DIVISIBLE_RANDALL_2 = 5, MOVIMIENTOS_DIVISIBLE_RANDALL_3 = 3;
const int UTILIZO_HERRAMIENTA = 1;
const int RESTO_PAPELEO = 1;
const int MAXIMO_MOVIMIENTOS_REALIZADOS_PAREDES_1 = 40, MAXIMO_MOVIMIENTOS_REALIZADOS_PAREDES_2 = 30, MAXIMO_MOVIMIENTOS_REALIZADOS_PAREDES_3 = 20;

#define OLAF 'O'
#define STITCH 'S'
#define JASMIN 'J'
#define PAPELEOS 'P'
#define RAYO_MCQUEEN 'R'
#define VACIO ' '
#define PAREDES '*'
#define NIVEL_1 0
#define NIVEL_2 1
#define NIVEL_3 2
#define MAXIMO_MOVIMIENTOS_NIVEL_1 40
#define MAXIMO_MOVIMIENTOS_NIVEL_2 30
#define MAXIMO_MOVIMIENTOS_NIVEL_3 20
#define DIMENSION_NIVEL_1 22
#define DIMENSION_NIVEL_2 17
#define DIMENSION_NIVEL_3 12
#define TERMINA_POSICION_OBJETOS 2
#define EMPIEZA_POSICION_OBJETOS 1
#define TIEMPO_GRAVEDAD 0.25f
#define MAX_NIVELES 3
#define MAX_TERRENO 40
#define MAX_OBJETOS 100
#define VALOR_INVALIDO -1
#define SE_ESTA_JUGANDO 0
#define JUEGO_PERDIDO -1
#define JUEGO_GANADO 1
#define NIVEL_GANADO 1


/*Pre: --
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
/*Pre: --
 *Pos: le asigna a valores a algunos de los topes que se utilizan en el programa, varia dependiendo del nivel. Si el personaje adquirido en el primer desafio es Olaf (O) se elimina
 *         como obsequio una cierta cantidad de fuegos como recompensa del nivel uno y dos.
 */
void asignar_topes(int numero_nivel, int* tope_medias, int* tope_fuegos, int* tope_interruptores, int* tope_gritos, 
                int* tope_obstaculos, int* tope_herramientas, int* tope_papeleos, char personaje_tp1){
    if(numero_nivel == 1){
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
    } else if(numero_nivel == 2){
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
    } else if(numero_nivel == 3){
        (*tope_medias) = MEDIAS_NIVEL_3;
        (*tope_fuegos) = FUEGOS_NIVEL_3;
        (*tope_interruptores) = INTERRUPTORES_NIVEL_3;
        (*tope_gritos) = GRITOS_NIVEL_3;
        (*tope_obstaculos) = TOPE_OBSTACULOS_3;
        (*tope_herramientas) = TOPE_HERRAMIENTAS_3;     
        (*tope_papeleos) = PAPELEOS_NIVEL_3;
    }
}

/* Pre: --
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

/* Pre: --
 * Pos: devuelve una posicion aleatoria dentro de la matriz donde ningun objeto o pared la ocupan. 
 */
void asignar_coordenada_aleatoria(int dimension, int* fila, int* columna, char matriz_nivel[MAX_TERRENO][MAX_TERRENO]){
    do{
        (*fila) = rand()% (dimension-TERMINA_POSICION_OBJETOS) + EMPIEZA_POSICION_OBJETOS;
        (*columna) = rand()% (dimension-TERMINA_POSICION_OBJETOS) + EMPIEZA_POSICION_OBJETOS;
    } while(matriz_nivel[*fila][*columna] != VACIO);
}

/* Pre: --
 * Pos: asigna la posicion posicion en la matriz, su fila y columna, y el tipo de herramienta o obstaculo es.
 */
void asignar_valores(int fila, int columna, char matriz_nivel[MAX_TERRENO][MAX_TERRENO], char objeto, objeto_t objetos[MAX_OBJETOS], int posicion){
    matriz_nivel[fila][columna] = objeto;
    objetos[posicion].tipo = objeto;
    objetos[posicion].posicion.fil = fila;
    objetos[posicion].posicion.col = columna;

}

/* Pre: --
 * Pos: se les asigna a las medias y fuegos una posicion aleatoria en el nivel en algun lugar donde no haya alguna pared u otro objeto. También se les asigna una constante que se utiliza para su posicion en la matriz:
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
        } while(fuegos_pared(matriz_nivel, paredes, fila, columna, tope_paredes));
        asignar_valores(fila, columna, matriz_nivel, objeto, obstaculos, i);
    }
}
/* Pre: --
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
/* Pre: --
 * Pos: le asigno una coordenada aleatoria a los Papeleos evitando que se superponga con una pared u objeto y asigno que los papeleos aparezcan enumerados en el nivel. 
 *      Tambien si el nivel actual es tres y el personaje del tp1 es stitch, se resta un papeleo del nivel como obsequio.
 */
void inicializar_papeleos(papeleo_t papeleos[MAX_PAPELEOS], int dimension, char matriz_nivel[MAX_TERRENO][MAX_TERRENO], int* tope_papeleos, char personaje_tp1, int numero_nivel){
    int fila = 0, columna = 0;
    if(personaje_tp1 == STITCH && numero_nivel == 3){
        (*tope_papeleos) = (*tope_papeleos) - PAPELEOS_OBSEQUIO_STITCH;
    }
    for(int i = 0; i < (*tope_papeleos); i++){
        asignar_coordenada_aleatoria(dimension, &fila, &columna, matriz_nivel);
        matriz_nivel[fila][columna] = PAPELEOS;
        papeleos[i].id_papeleo = i+1;
        papeleos[i].posicion.fil = fila;        
        papeleos[i].posicion.col = columna;
        papeleos[i].recolectado = false;
    }
}

/*Pre: --
 *Pos: devuelve la variable caracter con formato de valores numericos, empezando por el 1. 
 */
char casteo_id_papeleos(int numero){
    char caracter = (char)(numero + 48);
    return caracter;
}

/*Pre: se recibe el nivel actual
 *Pos: se inicializan por nivel cada una de las características del jugador: cantidad de movimientos, martillos y extintores. 
 *     Los interruptores 'ahuyenta randall' comienzan inicialimente desactivados. La cantidad de movimientos restantes en un nivel, son acumulables para el proximo.
 */
void inicializar_jugador(jugador_t* jugador, int nivel_actual, juego_t* juego){
    jugador->posicion = juego->niveles[nivel_actual - 1].pos_inicial_jugador;
    jugador->ahuyenta_randall = false;
    jugador->movimientos_realizados = 0;
    if(nivel_actual == 1){
        jugador->movimientos = MAXIMO_MOVIMIENTOS_NIVEL_1;
        jugador->martillos = MARTILLOS_NIVEL_1;
        jugador->extintores = EXTINTORES_NIVEL_1;
    } else if(nivel_actual == 2){
        jugador->movimientos = jugador->movimientos + MAXIMO_MOVIMIENTOS_NIVEL_2;
        jugador->martillos = MARTILLOS_NIVEL_2;
        jugador->extintores = EXTINTORES_NIVEL_3;
    } else if(nivel_actual == 3){
        jugador->movimientos = jugador->movimientos + MAXIMO_MOVIMIENTOS_NIVEL_3;
        jugador->martillos = MARTILLOS_NIVEL_3;
        jugador->extintores = EXTINTORES_NIVEL_3;
    }
}

/*Pre: Se recibe el personaje obtenido en el desafio de llegar a la facultad para poder dar el examén.
 *Pos: Si el personaje obtenido es Jasmín: se recibe un martillo extra en cada uno de los niveles, gracias al genio de la lámpara.
 *     Si el personaje obtenido es Rayo Mcqueen: se recibe 10 moviemientos extras en el nivel inicial, gracias a su extrema velocidad.
 */
void recibir_obsequios(juego_t* juego, char personaje_tp1){
    if(personaje_tp1 == JASMIN){
            juego->jugador.martillos += MARTILLOS_OBSEQUIO_JASMIN;     
    } else if(personaje_tp1 == RAYO_MCQUEEN){
        if(juego->nivel_actual == 1){
            juego->jugador.movimientos += MOVIMIENTOS_OBSEQUIO_RAYO;
        }
    } 
}

/* Pre: recibe el caracter que el usuario ingreso.
 * Pos: verifica que el caracter sea valido. Ellos son: A, D, Q, E, Z y C.
 */
bool es_caracter_valido(char caracter_ingresado){
    return (caracter_ingresado == USAR_MARTILLO || caracter_ingresado == USAR_EXTINTOR || caracter_ingresado == ACCION_DERECHA || 
            caracter_ingresado == ACCION_IZQUIERDA || caracter_ingresado == ROTACION_HORARIA || caracter_ingresado == ROTACION_ANTIHORARIA);
}

/* Pre: --
 * Pos: Pide al usuario que ingrese un caracter valido y verifica que lo sea, sino vuelve a preguntar.
 */
void leer_caracter_usuario(char* caracter_ingresado){
    printf("Ingrese uno de los siguientes caracteres:\n");
    printf("A para moverte hacia la izquierda\n");
    printf("D para moverte hacia la derecha\n");
    printf("Q para rotar antihorario\n");
    printf("E para rotar horario\n");
    printf("Z para utilizar martillo\n");
    printf("C para utilizar extintor\n");
    scanf(" %c", caracter_ingresado);
    while(!es_caracter_valido(*caracter_ingresado)){
        printf("El caracter ingresado no es valido, por favor vuelva a intentarlo\n");
        scanf(" %c", caracter_ingresado);
    }
}

/* Pre: --
 * Pos: suma un movimiento realizado y resta un movimiento a los restantes.
 */
void se_realizo_movimiento(int* movimientos_realizados, int* movimientos){
    (*movimientos_realizados) += 1;
    (*movimientos) -= 1;
}

/* Pre: --
 * Pos: devuelve un verdadero si el jugador se encuentra una coordenada arriba que la pared, devuelve falso si esto no se cumple.
 */
bool jugador_esta_arriba_pared(coordenada_t jugador, coordenada_t paredes){
    bool esta_arriba = false;
    if(jugador.fil + 1 == paredes.fil && jugador.col == paredes.col){
        esta_arriba = true;
    } 
    return esta_arriba;
}

/* Pre: --
 * Pos: devuelve un verdadero si el jugador tiene una posicion vacia por lo cual puede moverse hacia abajo, sino devuelve falso si hay una pared abajo. 
 */
bool puede_caer_jugador(coordenada_t posicion_jugador, int tope_paredes, coordenada_t paredes[MAX_PAREDES]){
    bool puede_caer = true;
    for(int i = 0; i < tope_paredes; i++){
        if(jugador_esta_arriba_pared(posicion_jugador, paredes[i])){
            puede_caer = false;
        } 
    }
    return puede_caer;
}

/* Pre: --
 * Pos: se recorre el tope paredes y devuelve true si el jugador se encuentra al lado de una pared, a su izquierda o derecha. En caso 
 *      contrario, devuelve un false si no hay pared.
 */
bool hay_pared(coordenada_t paredes[MAX_PAREDES], coordenada_t posicion_jugador, int tope_paredes, char caracter_ingresado){
    bool hay_pared = false;
    for(int i = 0; i < tope_paredes; i++){
        if(caracter_ingresado == ACCION_DERECHA && paredes[i].col == (posicion_jugador.col + 1) && (paredes[i].fil == posicion_jugador.fil)){
            hay_pared = true;
        } else if(caracter_ingresado == ACCION_IZQUIERDA && paredes[i].col == (posicion_jugador.col - 1) && (paredes[i].fil == posicion_jugador.fil)){
            hay_pared = true;   
        }
    }
    return hay_pared;
}

/* Pre: --
 * Pos: se devuelve verdadero si la pared ingresada forma parte del borde del mapa, sino devuelve falso.
 */
bool es_pared_borde(int tope_paredes, coordenada_t paredes, int dimension){
    bool pared_borde = false;
        if(paredes.fil == 0){
            pared_borde = true;
        } else if(paredes.fil == dimension - 1){
            pared_borde = true;
        } else if(paredes.col == dimension - 1){
            pared_borde = true;
        } else if(paredes.col == 0){
            pared_borde = true;
        }
    return pared_borde;
}

/* Pre: --
 * Pos: asigna una coordenada aleatoria a una cierta posicion dentro de la dimension del nivel
 */
void asigno_coordenada_aleatoria(coordenada_t* posicion, int dimension){
    posicion->fil = rand()% (dimension-TERMINA_POSICION_OBJETOS) + EMPIEZA_POSICION_OBJETOS;
    posicion->col = rand()% (dimension-TERMINA_POSICION_OBJETOS) + EMPIEZA_POSICION_OBJETOS;
}

/* Pre: --
 * Pos: verifica que dos posiciones sean iguales y devuelve verdadero si esto pasa, sino falso 
 */
bool posiciones_son_iguales(coordenada_t posicion, coordenada_t posicio_auxiliar){
    bool esta_ocupada = false;
    if(posicion.fil == posicio_auxiliar.fil && posicion.col == posicio_auxiliar.col){
        esta_ocupada = true;
    }
    return esta_ocupada;
}

/* Pre: --
 * Pos: recorre los vectores de objetos, papeleos y paredes, y la posicion del jugador. Verifica si la coordenada de alguna posicion de algun
 *     vector es igual a la coordenada ingresada. Si es asi, devuelve verdadero, si no coincide con ninguna coordenada, devuelve false.
 */
bool posicion_ocupada(nivel_t nivel, coordenada_t posicion_auxiliar){
    bool coordenada_ocupada = false;
    for(int i = 0; i < nivel.tope_herramientas; i++){
        if(posiciones_son_iguales(nivel.herramientas[i].posicion, posicion_auxiliar)){
            coordenada_ocupada = true;
        }
    }
    for(int i = 0; i < nivel.tope_obstaculos; i++){
        if(posiciones_son_iguales(nivel.obstaculos[i].posicion, posicion_auxiliar)){
            coordenada_ocupada = true;
        }
    }
    for(int i = 0; i < nivel.tope_paredes; i++){
        if(posiciones_son_iguales(nivel.paredes[i], posicion_auxiliar)){
            coordenada_ocupada = true;
        }
    }
    for(int i = 0; i < nivel.tope_papeleos; i++){
        if(posiciones_son_iguales(nivel.papeleos[i].posicion, posicion_auxiliar)){
            coordenada_ocupada = true;
        }
    }
    if(posiciones_son_iguales(nivel.pos_inicial_jugador, posicion_auxiliar)){
        coordenada_ocupada = true;
    }
    return coordenada_ocupada;
}

/* Pre: --
 * Pos: crea una nueva coordenada aleatoria dentro de la dimension de la matriz y chequea que no este ocupada, utilizando una coordenada 
 *      auxiliar. Luego le asigna ese valor a la ultima posicion del vector paredes. Al final, aumenta el tope de las paredes.
 */
void crear_pared_aleatoria(nivel_t* nivel, int dimension){
    coordenada_t aux;
    aux.fil = VALOR_INVALIDO;
    aux.col = VALOR_INVALIDO;
    do{
        asigno_coordenada_aleatoria(&aux, dimension);
    } while(posicion_ocupada(*nivel, aux));
    nivel->paredes[nivel->tope_paredes].fil = aux.fil;
    nivel->paredes[nivel->tope_paredes].col = aux.col;
    (nivel->tope_paredes)++;
}

/* Pre: --
 * Pos: dependiendo del nivel el que se este jugando y la cantidad de movimientos realizados por el usuario, si es menor o igual a una 
 *      cierta cantidad, se llama a la funcion que genera una nueva pared en una posicion aleatoria y libre.
 */
void crear_pared_aleatoria_por_nivel(nivel_t* nivel, int dimension, int nivel_actual, int movimientos_realizados){
    if(nivel_actual == NIVEL_1){
        if(movimientos_realizados <= MAXIMO_MOVIMIENTOS_REALIZADOS_PAREDES_1){
            crear_pared_aleatoria(nivel, dimension);
        }
    } else if(nivel_actual == NIVEL_2){
        if(movimientos_realizados <= MAXIMO_MOVIMIENTOS_REALIZADOS_PAREDES_2){
            crear_pared_aleatoria(nivel, dimension);
        }
    } else if(nivel_actual == NIVEL_3){
        if(movimientos_realizados <= MAXIMO_MOVIMIENTOS_REALIZADOS_PAREDES_3){
            crear_pared_aleatoria(nivel, dimension);
        }
    }
}

/* Pre: -- 
 * Pos: asigna un valor aleatorio a una variable, entre el 0 y el tope de papeleos de ese nivel. Este proceso se repite hasta 
 *      encontrar un papeleo que no haya sido recolectado.
 */
int papeleo_aleatorio(nivel_t nivel){
    int i;
    do{
        i = rand()% (nivel.tope_papeleos) + 0;   
    } while(nivel.papeleos[i].recolectado == true);
    return i;
}

/* Pre: los movimientos realizados por el jugador deben poder ser divisibles por un cierto numero dependiendo del nivel
 * Pos: se asigna un papeleo aleatorio no recolectado y se le declara una coordenada aleatoria en una posicion libre.
 */
void intercambio_papeleos(nivel_t* nivel, int divisor_nivel, int dimension, int movimientos_realizados){
    int i = VALOR_INVALIDO;
    papeleo_t aux[MAX_PAPELEOS];
    if(movimientos_realizados % divisor_nivel == 0){
        i = papeleo_aleatorio(*nivel);

        do{
            asigno_coordenada_aleatoria(&aux[i].posicion, dimension);
        } while(posicion_ocupada(*nivel, aux[i].posicion));
    }
    nivel->papeleos[i].posicion.fil = aux[i].posicion.fil;
    nivel->papeleos[i].posicion.col = aux[i].posicion.col;
}

/* Pre: --
 * Pos: se asigna el valor del divisor correspondiente por nivel y se llama al procedimiento que realiza el intercambio del papeleo. 
 */
void intercambiar_papeleos_randall(nivel_t* nivel, int nivel_actual, int dimension, int movimientos_realizados, bool ahuyenta_randall){
    if(ahuyenta_randall == false){
        if(nivel_actual == NIVEL_1){
            int divisor_nivel = MOVIMIENTOS_DIVISIBLE_RANDALL_1;
            intercambio_papeleos(nivel, divisor_nivel, dimension, movimientos_realizados);
        } else if(nivel_actual == NIVEL_2){
            int divisor_nivel = MOVIMIENTOS_DIVISIBLE_RANDALL_2;
            intercambio_papeleos(nivel, divisor_nivel, dimension, movimientos_realizados);
        } else if(nivel_actual == NIVEL_3){
            int divisor_nivel = MOVIMIENTOS_DIVISIBLE_RANDALL_3;
            intercambio_papeleos(nivel, divisor_nivel, dimension, movimientos_realizados);
        }
    }
}

/* Pre: --
 * Pos: si el jugador se encuentra sobre un Fuego, el jugador se queda sin movimientos. En cambio, si el jugador se encuentra arriba 
 *      de una Media, pierde 10 movimientos.
 */
void interaccion_jugador_arriba_obstaculos(objeto_t obstaculo[MAX_OBSTACULOS], int tope_obstaculos, int* movimientos, coordenada_t posicion_jugador){
    for(int i = 0; i < tope_obstaculos; i++){
        if(obstaculo[i].tipo == FUEGOS && posiciones_son_iguales(posicion_jugador, obstaculo[i].posicion)){
            (*movimientos) = 0; 
        } else if(obstaculo[i].tipo == MEDIAS && posiciones_son_iguales(posicion_jugador, obstaculo[i].posicion)){
            (*movimientos) -= PIERDE_MOVIMIENTOS_MEDIAS;
        }
    }
}

/* Pre: --
 * Pos: Si el jugador se encuentra arriba de una Botella de gritos, gana 7 movimientos y si se para sobre un 'Interruptor Ahuyenta Randall' se 
 *      activa en caso que este desactivado o lo desactiva en caso contrario.
 */
void interaccion_jugador_arriba_herramientas(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, jugador_t* jugador){
    for(int i = 0; i < tope_herramientas; i++){
        if(herramientas[i].tipo == BOTELLAS_DE_GRITOS && posiciones_son_iguales(jugador->posicion, herramientas[i].posicion)){
            jugador->movimientos += GANA_MOVIMIENTOS_BOTELLAS;
        }
        if(herramientas[i].tipo == INTERRUPTORES_AHUYENTA_RANDALL && posiciones_son_iguales(jugador->posicion, herramientas[i].posicion)){
            if(jugador->ahuyenta_randall != false){
                jugador->ahuyenta_randall = false;
            } else{
                jugador->ahuyenta_randall = true;
            }
        }
    }
}

/* Pre: --
 * Pos: Si el jugador se encuentra arriba de un papeleo no recolectado y tiene el menor id_papeleo, cambia su estado de recolectado a verdadero. 
 *      En cambio, si hay un papeleo menor que todavia no fue recolectado y se quiere recolectar uno mayor, no se puede ya que se debe recolectar el menor primero.
 */
void interaccion_jugador_arriba_papeleos(papeleo_t papeleos[MAX_PAPELEOS], coordenada_t posicion_jugador, int tope_papeleos){
    int i = 0;
    if(posiciones_son_iguales(posicion_jugador, papeleos[i].posicion)){
        if(i == 0 && papeleos[i].recolectado == false){
            papeleos[i].recolectado = true;
        }
    }
    for(int i = 1; i < tope_papeleos; i++){
        if(posiciones_son_iguales(posicion_jugador, papeleos[i].posicion)){
            if(papeleos[i-1].recolectado == true && papeleos[i].recolectado == false){
                papeleos[i].recolectado = true;
            }
        }
    }
}

/* Pre: --
 * Pos: llama a las funciones que realizan las distintas interacciones que tendra el jugador si se para sobre algun objeto. 
 */
void interaccion_jugador_objeto(nivel_t* nivel, jugador_t* jugador){
    interaccion_jugador_arriba_obstaculos(nivel->obstaculos,nivel->tope_obstaculos, &(jugador->movimientos), jugador->posicion);
    interaccion_jugador_arriba_herramientas(nivel->herramientas, nivel->tope_herramientas, jugador);
    interaccion_jugador_arriba_papeleos(nivel->papeleos, jugador->posicion, nivel->tope_papeleos);
}

/* Pre: --
 * Pos: devuelve true si el objeto se encuentra a la derecha del jugador. 
 */
bool objeto_esta_derecha(coordenada_t objeto, coordenada_t jugador){
    return jugador.fil == objeto.fil && jugador.col == objeto.col - 1;
}

/* Pre: --
 * Pos: devuelve verdadero si el objeto se encuentra a la izquierda del jugador. 
 */
bool objeto_esta_izquierda(coordenada_t objeto, coordenada_t jugador){
    return jugador.fil == objeto.fil && jugador.col == objeto.col + 1;
}

/* Pre: --
 * Pos: si el objeto ingresado se encuentra abajo del jugador devuelve verdadero.
 */
bool objeto_esta_abajo(coordenada_t objeto, coordenada_t jugador){
    return jugador.col == objeto.col && jugador.fil == objeto.fil - 1;
}

/* Pre: --
 * Pos: si el objeto se encuentra arriba del jugador devuelve verdadero.
 */
bool objeto_esta_arriba(coordenada_t objeto, coordenada_t jugador){
    return jugador.col == objeto.col && jugador.fil == objeto.fil + 1;
}

/* Pre: --
 * Pos: se comprueba que la posicion debajo del jugador se encuentra vacia permitiendole al jugador moverse a esa posicion hasta que 
 *      se encuentre con alguna pared debajo de el. Por cada posicion que cae, se verifica si el jugador se encuentra sobre algun 
 *      objeto y si hay, se realiza la interaccion que el jugador tenga con el. Ademas, se detiene el tiempo y se imprime el terreno
 *      para mostrar la animacion del jugador cayendo.
 */
void caer_personaje(juego_t* juego){
    while(puede_caer_jugador(juego->jugador.posicion, juego->niveles[juego->nivel_actual-1].tope_paredes, juego->niveles[juego->nivel_actual-1].paredes)){  
        juego->jugador.posicion.fil += 1;
        detener_el_tiempo(TIEMPO_GRAVEDAD);
        interaccion_jugador_objeto(&(juego->niveles[juego->nivel_actual-1]), &(juego->jugador));
        imprimir_terreno(*juego);
    }
}

/* Pre: --
 * Pos: se llama al procedimiento que permite que el jugador caiga en caso de que no haya una pared debajo de el, se llama al procedimiento que suma un
 *      movimiento realizado y resta un movimiento, y se crea una pared aleatoria. 
 */
void ejecutar_movimiento(juego_t* juego, char caracter_ingresado, int dimension){
    caer_personaje(juego);
    se_realizo_movimiento(&(juego->jugador.movimientos_realizados), &(juego->jugador.movimientos));
    crear_pared_aleatoria_por_nivel(&(juego->niveles[juego->nivel_actual-1]), dimension, juego->nivel_actual-1, juego->jugador.movimientos_realizados); 
}

/* Pre: --
 * Pos: dependiendo el caracter ingresado, se realizan las acciones hacia la izquiera o derecha. Si hay en la direccion que el    
 *      jugador se quiere desplazar, el movimiento no va a ser posible. Se llama al procedimiento que realiza las distintas acciones cuando el jugador se mueve.
 */
coordenada_t desplazar_personaje(juego_t* juego, char caracter_ingresado, int dimension){
    if(caracter_ingresado == ACCION_DERECHA && !hay_pared(juego->niveles[juego->nivel_actual-1].paredes, juego->jugador.posicion, juego->niveles[juego->nivel_actual-1].tope_paredes, caracter_ingresado)){
        juego->jugador.posicion.col += 1;
        ejecutar_movimiento(juego, caracter_ingresado, dimension);
    } else if(caracter_ingresado == ACCION_IZQUIERDA && !hay_pared(juego->niveles[juego->nivel_actual-1].paredes, juego->jugador.posicion, juego->niveles[juego->nivel_actual-1].tope_paredes, caracter_ingresado)){
        juego->jugador.posicion.col -= 1;
        ejecutar_movimiento(juego, caracter_ingresado, dimension);
    }
    return juego->jugador.posicion;
}

/* Pre: --
 * Pos: se rotan las coordenadas del nivel en sentido horario o antihorario, dependiendo del caracter ingresado por el jugador.
 */
void realizar_rotacion(coordenada_t* coordenada, char caracter_ingresado, int dimension){
    coordenada_t aux_coordenada;
    if(caracter_ingresado == ROTACION_HORARIA){ 
        aux_coordenada.fil = coordenada->col;
        aux_coordenada.col = abs(coordenada->fil - (dimension - 1));
        coordenada->fil = aux_coordenada.fil;
        coordenada->col = aux_coordenada.col;
    } else if(caracter_ingresado == ROTACION_ANTIHORARIA){
        aux_coordenada.col = coordenada->fil;
        aux_coordenada.fil = abs(coordenada->col - (dimension - 1));
        coordenada->fil = aux_coordenada.fil;
        coordenada->col = aux_coordenada.col;
    }
}

/* Pre: --
 * Pos: se recorren todas las posiciones de los vectores de herramientas, obstaculos, papeleos, paredes y la posicion del jugador, y 
 *      se llama a la funcion que los rota en sentido horario o antihorario dependiendo lo pedido por el usuario.
 */
void rotar_matriz(jugador_t* jugador, nivel_t* nivel, char caracter_ingresado, int dimension){
    realizar_rotacion(&(jugador->posicion), caracter_ingresado, dimension);
    for(int i = 0; i < nivel->tope_obstaculos; i++){
        realizar_rotacion(&(nivel->obstaculos[i].posicion), caracter_ingresado, dimension);
    }
    for(int i = 0; i < nivel->tope_herramientas; i++){
        realizar_rotacion(&(nivel->herramientas[i].posicion), caracter_ingresado, dimension);
    }
    for(int i = 0; i < nivel->tope_papeleos; i++){
        realizar_rotacion(&(nivel->papeleos[i].posicion), caracter_ingresado, dimension);
    }
    for(int i = 0; i < nivel->tope_paredes; i++){
        realizar_rotacion(&(nivel->paredes[i]), caracter_ingresado, dimension);
    }
}

/* Pre: --
 * Pos: verifica que el caracter sea uno valido: A, D, W o S, devuelve verdadero en ese caso. 
 */
bool caracter_valido_martillo(char caracter_ingresado){
    return caracter_ingresado == ACCION_DERECHA || caracter_ingresado == ACCION_IZQUIERDA || caracter_ingresado == ACCION_ARRIBA || caracter_ingresado == ACCION_ABAJO;
}

/* Pre: --
 * Pos: se elimina la pared ingresada y se resta uno de su respectivo tope. Tambien, se resta del total, la herramienta que se utilizo.
 */
void eliminar_pared(coordenada_t* paredes, coordenada_t paredes_modificada, int* tope_paredes, int* martillos){ 
    (*paredes) = paredes_modificada;
    (*martillos) -= UTILIZO_HERRAMIENTA;
    (*tope_paredes)--;
}

/* Pre: --
 * Pos: Se le pregunta al usuario hacia donde desea romper la pared, se verifica que el caracter ingresado sea valido, sino se vuelve 
 *      a preguntar. Si la pared que se quiere eliminar no es un borde y se encuentra en la direccion correcta a la que quiere
 *      eliminar el usuario, entonces se realiza dicha accion, esto es igual para las cuatro direcciones.     
 */
void utilizar_martillo(coordenada_t posicion_jugador, coordenada_t paredes[MAX_PAREDES], int* tope_paredes, char* caracter_ingresado, int dimension, int* martillos){
    printf("\n");
    printf("Vas a utilizar un MARTILLO!\n");
    printf("Puedes usar:\n");
    printf("D para romper una pared a tu derecha\n");
    printf("A para romper una pared a tu izquierda\n");
    printf("W para romper una pared arriba\n");
    printf("S para romper una pared abajo\n");
    printf("\n");
    scanf(" %c", caracter_ingresado);

    while(!caracter_valido_martillo(*caracter_ingresado)){
        printf("El caracter ingresado no es valido, por favor vuelva a intentarlo\n");
        scanf(" %c", caracter_ingresado);
    }

    for(int i = 0; i < (*tope_paredes); i++){
        if(!es_pared_borde(*tope_paredes, paredes[i], dimension)){
            if(((*caracter_ingresado) == ACCION_DERECHA && objeto_esta_derecha(paredes[i], posicion_jugador)) || ((*caracter_ingresado)  == ACCION_IZQUIERDA && objeto_esta_izquierda(paredes[i], posicion_jugador)) || 
                ((*caracter_ingresado) == ACCION_ARRIBA && objeto_esta_arriba(paredes[i], posicion_jugador)) || ((*caracter_ingresado)  == ACCION_ABAJO && objeto_esta_abajo(paredes[i], posicion_jugador))){
                eliminar_pared(&(paredes[i]), paredes[*tope_paredes - 1], tope_paredes, martillos);
            }
        }
    }
}

/* Pre: se recibe el caracter ingresado por el usuario cuando se le consulta en que direccion quiere eliminar la pared
 * Pos: verifica que el caracter sea uno valido: A, D o W , devuelve verdadero en ese caso.
 */
bool caracter_valido_extintor(char caracter_ingresado){
    return caracter_ingresado == ACCION_DERECHA || caracter_ingresado == ACCION_IZQUIERDA || caracter_ingresado == ACCION_ARRIBA;
}

/* Pre: --
 * Pos: se elimina el obstaculo ingresado y se resta uno de su respectivo tope. Tambien, se resta una herramienta del total.
 */
void eliminar_obstaculo(objeto_t* obstaculo, objeto_t obstaculo_modificado, int* tope_obstaculos, int* herramienta){ 
    (*obstaculo) = obstaculo_modificado;
    (*herramienta) -= UTILIZO_HERRAMIENTA;
    (*tope_obstaculos)--;
}

/* Pre: --
 * Pos: Se le pregunta al usuario hacia donde desea extinguir el fuego, se verifica que el caracter ingresado sea valido, sino se vuelve 
 *      a preguntar. Si el fuego se encuentra en la direccion correcta a la que quiere eliminar el usuario, entonces se realiza dicha 
 *      accion, esto es igual para las tres direcciones.
 */
void utilizar_extintor(coordenada_t posicion_jugador, objeto_t obstaculo[MAX_OBSTACULOS], int* tope_obstaculos, char* caracter_ingresado, int* extintores){
    printf("\n");
    printf("Vas a utilizar un EXTINTOR!\n");
    printf("Puedes usar:\n");
    printf("D para extinguir un fuego a tu derecha\n");
    printf("A para extinguir un fuego a tu izquierda\n");
    printf("W para extinguir un fuego arriba\n");
    printf("\n");
    scanf(" %c", caracter_ingresado);

    while(!caracter_valido_extintor(*caracter_ingresado)){
        printf("El caracter ingresado no es valido, por favor vuelva a intentarlo\n");
        scanf(" %c", caracter_ingresado);
    }
    for(int i = 0; i < (*tope_obstaculos); i++){
        if(obstaculo[i].tipo == FUEGOS){   
            if(((*caracter_ingresado) == ACCION_DERECHA && objeto_esta_derecha(obstaculo[i].posicion, posicion_jugador)) || ((*caracter_ingresado)  == ACCION_IZQUIERDA && objeto_esta_izquierda(obstaculo[i].posicion, posicion_jugador)) || 
            ((*caracter_ingresado) == ACCION_ARRIBA && objeto_esta_arriba(obstaculo[i].posicion, posicion_jugador))){
                eliminar_obstaculo(&(obstaculo[i]), obstaculo[*tope_obstaculos - 1], tope_obstaculos, extintores);
            } 
        }   
    }
}

/* Pre: --
 * Pos: Si el caracter ingresado es para moverse a la derecha o izquierda: se realiza la accion que lo desplaza hacia aquella direccion.
 *      Si el caracter ingresado es rotar la matriz en sentido horario o antihorario: se llama a la funcion que realiza la rotacion, permite al personaje caer
 *          en caso que no hay una pared debajo, se llama a la funcion que suma los movimientos y se crea una pared aleatoria en una posicion aleatoria y libre 
 *      Si el caracter ingresado es para utilizar un martillo y el jugador todavia no utilizo todos: se llama a la funcion que se encarga de eliminar la pared correspondiente,
 *          y resta un martillo del total, tambien si no hay una pared debajo, el personaje cae hasta encontrar alguna. Si no hay suficientes martillos, se le avisa al usuario por pantalla.
 *      Si el caracter ingresado es para utilizar un extintor y el jugador todavia no utilizo todos: se llama a la funcion que se encarga de extinguir el fuego correspondiente,
 *          y se resta un extintor del total. Si no hay extintores suficientes, se le avisa al usuario por pantalla.
 *      
 */
void realizar_movimientos(juego_t* juego, char caracter_ingresado, int dimension){
    if(caracter_ingresado == ACCION_DERECHA || caracter_ingresado == ACCION_IZQUIERDA){
        desplazar_personaje(juego, caracter_ingresado, dimension);
    } else if (caracter_ingresado == ROTACION_HORARIA || caracter_ingresado == ROTACION_ANTIHORARIA){
        rotar_matriz(&(juego->jugador), &(juego->niveles[juego->nivel_actual-1]), caracter_ingresado, dimension);
        caer_personaje(juego);
        se_realizo_movimiento(&(juego->jugador.movimientos_realizados), &(juego->jugador.movimientos));
        crear_pared_aleatoria_por_nivel(&(juego->niveles[juego->nivel_actual-1]), dimension, (juego->nivel_actual-1), juego->jugador.movimientos_realizados);
    } else if(caracter_ingresado == USAR_MARTILLO){
        if((juego->jugador.martillos) > 0){
            utilizar_martillo(juego->jugador.posicion, juego->niveles[juego->nivel_actual-1].paredes, &(juego->niveles[juego->nivel_actual-1].tope_paredes), &caracter_ingresado, dimension, &(juego->jugador.martillos));
            caer_personaje(juego);
        } else if((juego->jugador.martillos) <= 0){
            printf("Te quedaste sin martillos, no se puede romper más paredes\n");
        }   
    } else if(caracter_ingresado == USAR_EXTINTOR){
        if((juego->jugador.extintores) > 0){
        utilizar_extintor(juego->jugador.posicion, juego->niveles[juego->nivel_actual-1].obstaculos, &(juego->niveles[juego->nivel_actual-1].tope_obstaculos), &caracter_ingresado, &(juego->jugador.extintores));
        } else if((juego->jugador.extintores) <= 0){
            printf("Te quedaste sin extintores, no podes extinguir más fuegos por este nivel\n");
        }
    }
}



/*Pre: --
 *Pos: se determina el tamaño de la matriz de cada nivel
  */
int dimension_paredes(int nivel_actual){
    int dimension = -1;
    if(nivel_actual == 1){
        (dimension) = DIMENSION_NIVEL_1;
    } else if(nivel_actual == 2){
        (dimension) = DIMENSION_NIVEL_2;
    } else if(nivel_actual == 3){
        (dimension) = DIMENSION_NIVEL_3;
    }
    return dimension;
}

/*Pre: --
 *Pos: se recorre la matriz y se reemplaza los valores dentro por vacios(espacios).
 */
void vaciar_matriz(char matriz_nivel[MAX_TERRENO][MAX_TERRENO]){
    for (int i = 0; i < MAX_TERRENO; i++){
        for (int j = 0; j < MAX_TERRENO; j++){
            matriz_nivel[i][j] = VACIO;
        }
    }
}

/*Pre: la matriz debe estar previamente cargada
 *Pos: se imprime por pantalla la matriz completa con sus paredes y las posiciones de los distintos objetos, papeleos y jugador.
 */ 
void imprimir_matriz_paredes(int dimension, char matriz_nivel[MAX_TERRENO][MAX_TERRENO]){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            printf(" %c ", matriz_nivel [i][j]);
        } printf("\n");
    }
}

/*Pre: --
 *Pos: se determinan las paredes de la matriz utilizando un caracter especial.
 */
void inicializar_paredes(nivel_t nivel, char matriz_nivel[MAX_TERRENO][MAX_TERRENO]){
    for(int i = 0; i < (nivel.tope_paredes); i++){
        matriz_nivel[nivel.paredes[i].fil][nivel.paredes[i].col] = PAREDES;
    }
}

/* Pre: --
 * Pos: se asigna el valor de las paredes dependiendo del nivel actual, se vacia la matriz por completo y se inicializan las paredes con el caracter '*'.
 */
void inicializar_matriz(nivel_t nivel, int* dimension, char matriz_nivel[MAX_TERRENO][MAX_TERRENO], int nivel_actual){
    (*dimension) = dimension_paredes(nivel_actual);
    vaciar_matriz(matriz_nivel);
    inicializar_paredes(nivel, matriz_nivel);
}

/*Pre: --
 *Pos: Se llama a la funcion de obtener_paredes ubicada en utiles.h, se determina el tamaño de la matriz del nivel y sus paredes. Además, se asignan 
 *     algunos de los topes utilizados en cada uno de los niveles, se inicializan los obstaculos, herramientas, papeleos y la coordenada aleatoria del jugador. 
 */
void inicializar_nivel(nivel_t* nivel, int numero_nivel, char personaje_tp1){
    obtener_paredes(numero_nivel, nivel->paredes, &(nivel->tope_paredes), &(nivel->pos_inicial_jugador));
    int dimension = VALOR_INVALIDO;
    char matriz_nivel[MAX_TERRENO][MAX_TERRENO];
    
    inicializar_matriz(*(nivel), &dimension, matriz_nivel, numero_nivel);

    matriz_nivel[nivel->pos_inicial_jugador.fil][nivel->pos_inicial_jugador.col] = MIKE;

    int tope_medias = 0, tope_fuegos = 0, tope_interruptores = 0, tope_gritos = 0;
    asignar_topes(numero_nivel, &tope_medias, &tope_fuegos, &tope_interruptores, &tope_gritos, &nivel->tope_obstaculos, &nivel->tope_herramientas, &nivel->tope_papeleos, personaje_tp1);

    inicializar_obstaculos(nivel->paredes, nivel->tope_paredes, nivel->obstaculos, dimension, matriz_nivel, tope_medias, tope_fuegos);
    inicializar_herramientas(nivel->herramientas, dimension, matriz_nivel, tope_gritos, tope_interruptores);
    inicializar_papeleos(nivel->papeleos, dimension, matriz_nivel, &nivel->tope_papeleos, personaje_tp1, numero_nivel);
}

/*Pre: --
 *Pos: Se llama a los procedimientos que inicializan cada uno de los tres niveles y al jugador. Además, se llama al procedimiento que 
 *      entrega algunos de los obsquios adquiridos por el personaje obtenido en el desafio de poder llegar a la facultad
 */
void inicializar_juego(juego_t* juego, char personaje_tp1){
    juego->personaje_tp1 = personaje_tp1;

    
    inicializar_nivel(&juego->niveles[NIVEL_1], 1, personaje_tp1);
    inicializar_nivel(&juego->niveles[NIVEL_2], 2, personaje_tp1);
    inicializar_nivel(&juego->niveles[NIVEL_3], 3, personaje_tp1);
    inicializar_jugador(&juego->jugador, juego->nivel_actual, juego);
    recibir_obsequios(juego, personaje_tp1);
}


/* Pre: --
 * Pos: se asigna el valor del tamaño del nivel, se le pide al usuario que ingrese un carater, se llama a la funcion que realiza las acciones y movimientos 
 *      por los caracteres asignados, se cita al procedimiento que se encarga si el jugador cayo en una posicion donde habia un objeto y que se cumpla la funcion 
 *      del objeto sobre el jugador. Y por ultimo cada cierta cantidad de movimientos realizados, se intercambia de posicion un papeleo aleatorio que no haya sido recolectado.
 */
void realizar_jugada(juego_t* juego){
    char caracter_ingresado = VACIO;
    int dimension = dimension_paredes(juego->nivel_actual);
    leer_caracter_usuario(&(caracter_ingresado));
    realizar_movimientos(juego, caracter_ingresado, dimension);
    interaccion_jugador_objeto(&(juego->niveles[juego->nivel_actual-1]), &(juego->jugador));
    intercambiar_papeleos_randall(&(juego->niveles[juego->nivel_actual-1]), juego->nivel_actual-1, dimension, juego->jugador.movimientos_realizados, juego->jugador.ahuyenta_randall);
}

/*
 * El nivel se dará por terminado, si se recolectan todos los papeleos en el mismo.
 * Devolverá:
 * -> 0 si el estado es jugando.
 * -> 1 si el estado es ganado.
 */
int estado_nivel(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
    int estado_actual_nivel = VALOR_INVALIDO;
    if(papeleos[tope_papeleos - 1].recolectado == true){
        estado_actual_nivel = NIVEL_GANADO;
    } else{
        estado_actual_nivel = SE_ESTA_JUGANDO; 
    }
    return estado_actual_nivel;
}

/*
 * El juego se dará por ganado, si terminó todos los niveles. O perdido, si el personaje queda sin movimientos. 
 * Devolverá:
 * -> 0 si el estado es jugando. 
 * -> -1 si el estado es perdido.
 * -> 1 si el estado es ganado.
 */
int estado_juego(juego_t juego){
    int estado_actual_juego = SE_ESTA_JUGANDO;
    if(estado_nivel(juego.niveles[2].papeleos, juego.niveles[2].tope_papeleos) == NIVEL_GANADO){
        estado_actual_juego = JUEGO_GANADO;
    } else if(estado_nivel(juego.niveles[juego.nivel_actual-1].papeleos, juego.niveles[juego.nivel_actual-1].tope_papeleos) == SE_ESTA_JUGANDO && juego.jugador.movimientos > 0){
        estado_actual_juego = SE_ESTA_JUGANDO;
    } else if(juego.jugador.movimientos <= 0){
        estado_actual_juego = JUEGO_PERDIDO;
    }
    return estado_actual_juego;
}



/*Pre: Se reciben los niveles a imprimir, con sus respectivos elementos y jugador.
 *Pos: Se imprimen por pantalla cada matriz con su respectiva dimensión, posicion de las paredes, personajes, objetos, papeleos y jugador inicial.
 */
void imprimir_terreno(juego_t juego){
    int nivel = juego.nivel_actual - 1;
    char matriz_nivel[MAX_TERRENO][MAX_TERRENO];
    int dimension = VALOR_INVALIDO;
    inicializar_matriz(juego.niveles[juego.nivel_actual-1], &dimension, matriz_nivel, juego.nivel_actual);

    printf("El nivel actual es: %i\n", juego.nivel_actual);
    printf("Movimientos restantes: %i    |||    Movimientos realizados: %i\n", juego.jugador.movimientos, juego.jugador.movimientos_realizados);
    printf("Martillos: %i    |||    Extintores: %i\n", juego.jugador.martillos, juego.jugador.extintores);
    printf("Si el interruptor se encuentra activado, se mostrara un 1, en caso contrario un 0: %i\n", juego.jugador.ahuyenta_randall);
    
    for(int i = 0; i < juego.niveles[nivel].tope_obstaculos; i++){
        matriz_nivel[juego.niveles[nivel].obstaculos[i].posicion.fil][juego.niveles[nivel].obstaculos[i].posicion.col] = juego.niveles[nivel].obstaculos[i].tipo;
    }
    for(int i = 0; i < juego.niveles[nivel].tope_herramientas; i++){
        matriz_nivel[juego.niveles[nivel].herramientas[i].posicion.fil][juego.niveles[nivel].herramientas[i].posicion.col] = juego.niveles[nivel].herramientas[i].tipo;
    }
    for(int i = 0; i < juego.niveles[nivel].tope_papeleos; i++){
        if(juego.niveles[nivel].papeleos[i].recolectado == false){
            matriz_nivel[juego.niveles[nivel].papeleos[i].posicion.fil][juego.niveles[nivel].papeleos[i].posicion.col] = casteo_id_papeleos(juego.niveles[nivel].papeleos[i].id_papeleo);
        }
    }

    matriz_nivel[juego.jugador.posicion.fil][juego.jugador.posicion.col] = MIKE;

    imprimir_matriz_paredes(dimension, matriz_nivel);
}