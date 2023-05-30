#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "tp1.h"
#include "papeleo.h"
#include "controlador.h"


#define SIN_MOVIMIENTOS 0
#define JUEGO_GANADO 1
#define SE_ESTA_JUGANDO 0
#define JUEGO_PERDIDO -1
#define NIVEL_GANADO 1

/* Pre: --
 * Pos: Se imprime por pantalla la introduccion y las instrucciones del juego.
 */
void introduccion_juego(){
    printf("Luego de todos los problemas que tuviste para llegar a FIUBA, finalmente pudiste rendir el examen. Ahora llego el momento de firmar la libreta, pero te diste cuenta que el dia que el profesor esta, vos no podes ir.\n");
    printf("Tu amigo, Mike Wazowski, acepta el pedido de llevar tu libreta a firmar.\n");
    printf("Al llegar al Departamento de Computación, Mike se encuentra con Roz, quien, una vez más, le recuerda que 'no ordeno su papeleo anoche...'. \n");
    printf("En venganza, repartio todos los papeleos por distintos niveles para complicarlo a Mike. Y, lamentablemente, Roz no le va a firmar nada a Mike hasta que el junte todo su papeleo.\n");
    printf("Sin posibilidad de evadir el desafio de Roz, llego el momento que Mike junte todo su papeleo y nosotros lo acompañaremos en esta aventura!!\n");
    printf("\n");
    printf("Para poder ganar el desafío, Mike debera pasar por tres habitaciones, donde debe recolectar su papeleo EN ORDEN.\n");
    printf("Estas, estaran delimitadas por los bordes del terreno, y además habrán paredes, obstáculos y herramientas que podran ayudarte o perjudicarte, en tu busqueda.\n");
    printf("Mike tendra una distinta cantidad de movimientos iniciales disponibles para cada nivel, y los movimientos restantes de uno, seran acumulados para el proximo nivel.\n");
    printf("Pero cuidado! La habitación podra rotar con tus movimientos.\n");
    printf("\n");
    printf("Utilizando los Martillos, podras eliminar las Paredes(*) interiores del nivel, pero no los bordes. Para poder eliminarlas, debes estar al lado.\n");
    printf("Utilizando los Extintores, podras extinguir algun Fuego(F) que tengas al lado, ya que si caes o pisas alguno, PERDES el juego\n");
    printf("Además, si pisas o caes sobre alguna Media(M), perderas 10 movimientos.\n");
    printf("Si pisas o caes sobre una Botella de Gritos(G), ganas 7 movimientos.");
    printf("Si pisas o caes sobre el Interruptor 'Ahuyenta Randall'(I), ese interruptor se activa si se encuentra desactivado o lo desactiva en caso contrario. Si el interruptor, no se encuentra activado, nuestro enemigo Randall, cada cierta cantidad de movimientos, hara que alguno de los papeleos, se transporte a una posición aleatoria, esto es posible por su habilidad de moverse sin ser visto al ser un camaleón.\n");
    printf("Además, durante cierta cantidad de movimientos, se generaran paredes en posiciones libres y aleatorias por todo el nivel\n");
    printf("\n");
    printf("\n");
}

/*Pre: --
 *Pos: se suma uno al contador del nivel actual, se llama a inicializar juego. 
 *      Se limpia la pantalla y se le avisa al usuario que paso al siguiente nivel, se imprime el terreno del siguiente nivel.
 */
void supero_nivel(juego_t* juego, char personaje){
    juego->nivel_actual++;
    inicializar_juego(juego, personaje);
    system("clear");
    printf("FELICIDADES, PASATE AL NIVEL %i!!!\n", juego->nivel_actual);
    imprimir_terreno(*juego);
}

int main(){
    srand((unsigned)time(NULL));
    char personaje = ' ';
    indicar_personaje_tp1(&personaje);
    printf("El personaje obtenido en la primera prueba es: %c\n", personaje);
    
    system("clear");
    juego_t juego;
    juego.nivel_actual = 1;
    introduccion_juego();
    inicializar_controlador();
    inicializar_juego(&juego, personaje);
    imprimir_terreno(juego);

    while(estado_juego(juego) == SE_ESTA_JUGANDO){
        realizar_jugada(&juego);
        system("clear");
        imprimir_terreno(juego);
        if(estado_nivel(juego.niveles[juego.nivel_actual-1].papeleos, juego.niveles[juego.nivel_actual-1].tope_papeleos) == NIVEL_GANADO && juego.nivel_actual <= 2){
            supero_nivel(&juego, personaje);
        }
    }
    terminar_controlador();

    return 0;
}