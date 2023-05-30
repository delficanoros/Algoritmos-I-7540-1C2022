#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "tp1.h"
#include "papeleo.h"
#include "utiles.h"



int main(){

    srand ((unsigned)time(NULL));

    char personaje = ' ';
    indicar_personaje_tp1(&personaje);
    printf("El personaje obtenido en la primera prueba es: %c\n", personaje);
    char personaje_tp1 = personaje;
    
    juego_t juego;
    
    inicializar_juego(&juego, personaje_tp1);
    imprimir_terreno(juego);

    return 0;
}