#include <stdio.h>
#include <stdbool.h>

const char OLAF = 'O';
const char STITCH = 'S';
const char JASMIN = 'J';
const char RAYO_MCQUEEN = 'R';
const char TRINEO = 'T';
const char NAVE_ESPACIAL = 'N';
const char CAMION = 'C';
const char ALFOMBRA = 'A';
const char BOLAS_DE_NIEVE = 'B';
const char PIUM_PIUM = 'P';
const char KUCHAU = 'K';
const char GENIO = 'G';
const char ERROR = 'E';
const int VALOR_MAX_HORA = 23;
const int VALOR_MIN_HORA = 00;
const float VALOR_MAX_MINUTOS = 0.59f;
const float VALOR_MIN_MINUTOS = 0.00f;
const float VALOR_LIM_MINUTOS = 0.30f;
const int VALOR_LIM_HORAS = 15;
const int PUNTAJE_GENIO = 12;
const int PUNTAJE_KUCHAU = 9;
const int PUNTAJE_BOLAS_DE_NIEVE = 3;
const int PUNTAJE_PIUM_PIUM = 6;
const int PUNTAJE_MANIFESTACION1 = 10;
const int PUNTAJE_MANIFESTACION2 = 20;
const int VALOR1_MIN_PUNTAJE = 13;
const int VALOR1_MAX_PUNTAJE = 41;
const int VALOR2_MAX_PUNTAJE = 68;

//Pre: la letra de tranporte debe ser: T, N, C o A; no puede ser otra.
//Pos: devuelve un true cuando el transporte es valido, si es false repregunta.
bool es_letra_transporte_valida (char letra_transporte){
     return (letra_transporte == TRINEO || letra_transporte == NAVE_ESPACIAL ||
       letra_transporte == CAMION || letra_transporte == ALFOMBRA);
}

//Pre: --
//Pos: pide al usuario el método que va a utilizar de transporte, hasta que sea valido.
void pedir_usuario_transporte (char* letra_transporte){
    printf("Estas saliendo de tu casa, y te enteras que hay paro de trenes, ¿Qué otro transporte elegis?\n");
    printf("Opciones: Trineo (T), Nave Espacial (N), Camión (C) o Alfombra (A)\n");

    scanf(" %c", letra_transporte);
    
    while (!es_letra_transporte_valida(*letra_transporte)){
    printf("La letra ingresada no es correcta, por favor vuelva a intentarlo\n");
    scanf(" %c", letra_transporte);
    }    
}

//Pre: la letra debe ser B, K, G o P; no puede ser otra letra.
//Pos: se devuelve la letra valida si es correcta.
bool es_letra_manifestacion_valida (char letra_manifestacion){
    return (letra_manifestacion == BOLAS_DE_NIEVE|| letra_manifestacion == PIUM_PIUM ||
       letra_manifestacion == KUCHAU || letra_manifestacion == GENIO);
}

//Pre: -- 
//Pos: pide al usuario el método que va a utilizar para deshacerse de la manifestación, hasta que sea valido .
void pedir_usuario_manifestacion (char* letra_manifestacion){
    printf("En medio del camino te encontras con una manifestación, ¿Que medio utilizas para deshacerte de la manifestación?\n");
    printf("Opciones: Bolas de Nieve (B), Pium Pium (P), Kuchau (K) o Genio (G)\n");
    
    scanf(" %c", letra_manifestacion);

    while (!es_letra_manifestacion_valida(*letra_manifestacion)){
        printf("La letra ingresada no es correcta, por favor vuelva a intentarlo\n");
        scanf(" %c", letra_manifestacion);
    }
}

//Pre: se controla que las horas sean validas, entre 00 y 23 y que los minutos sean entre 00 y 59.
//Pos: si es una hora y un minuto valido, devuelve un true, si no son validos, devuelve un false y se repregunta.
//  
bool es_hora_valida (int parte_entera, float decimales){
   if ((parte_entera >= VALOR_MIN_HORA && parte_entera <= VALOR_MAX_HORA) && 
   (decimales >= VALOR_MIN_MINUTOS && decimales <= VALOR_MAX_MINUTOS)){
        return true;
    } else {
        return false;
}
}

//Pre: --
//Pos: se le pide al usuario la hora hasta que sea valida.
void pedir_usuario_hora (float* horario, int* parte_entera, float* decimales){
    printf("Lograste superar la manifestación, ¿A que hora conseguiste llegar a la universidad? Ejemplo: 12.33 o 18.55\n");
    scanf(" %f", horario); 

    (*parte_entera) = (int) (*horario);
    (*decimales) = (*horario) - (float) (*parte_entera);
    
    while (!es_hora_valida(*parte_entera, *decimales)){
        printf("La hora ingresada no es valida, por favor vuelva a intentarlo\n");
        scanf(" %f", horario);
        (*parte_entera) = (int) (*horario);
        (*decimales) = (*horario) - (float) (*parte_entera);
    }
}  

//Pre: se controla que la nota obtenida sea entre el 1 y el 10.
//Pos: si la nota ingresada es correcta, se toma como valido.

bool es_calificacion_obtenida_valida (int nota){
    return (nota >= 1 && nota <= 10);
}

//Pre: --
//Pos: se le pide al usuario la nota obtenida en el examén hasta que sea valida. 
void pedir_usuario_nota(int* nota){
    printf("¡Por fin llegó la hora del parcial!¿Qué nota lograste sacarte? Ejemplo: 2 o 7\n");

    scanf(" %i", nota);

    while (!es_calificacion_obtenida_valida(*nota)){
        printf("El número ingresado no es valido, por favor vuelva a intentarlo\n");
        scanf(" %i", nota);
    }
}

//Pre: se envían todas las respuestas de metodo de manifestación, transporte y nota. 
//Pos: se devuelven nuevos int con los puntajes para cada respuesta que ingreso el usuario.
void suma_puntaje(char letra_transporte, char letra_manifestacion, int* letrat_int, 
                int* letram_int, int nota, int* multiplicador){

    if ((letra_transporte == CAMION) || (letra_transporte == ALFOMBRA)){
        (*letrat_int) = PUNTAJE_MANIFESTACION2;
    } else if ((letra_transporte == NAVE_ESPACIAL) || (letra_transporte == TRINEO)){
        (*letrat_int) = PUNTAJE_MANIFESTACION1;
    } 

     if(letra_manifestacion == BOLAS_DE_NIEVE){
        (*letram_int) = PUNTAJE_BOLAS_DE_NIEVE;
    } else if(letra_manifestacion == PIUM_PIUM){
        (*letram_int) = PUNTAJE_PIUM_PIUM;
    } else if(letra_manifestacion == KUCHAU){
       (*letram_int) = PUNTAJE_KUCHAU;
    } else if(letra_manifestacion == GENIO){
       (*letram_int) = PUNTAJE_GENIO;
    }

    if ((nota >= 1) && (nota <= 3)){
        (*multiplicador) = 1 ;
    } else if ((nota >= 4) && (nota <= 6)){
        (*multiplicador)= 2;
    } else if ((nota == 7) || (nota == 8)){
        (*multiplicador) = 3;
    } else if ((nota == 9) ||(nota == 10)){
        (*multiplicador) = 4;
    }
}

//Pre: las variables int que se utilizan para poder concretar el personaje son enviados.
//Pos: se devuelve el calculo del puntaje completo a partir de la hora que llego y el puntaje obtenido en las preguntas. 
//      Además, se crean printf para imprimir el resultado del personaje por la pantalla 
void calculo_personaje(int puntaje, char* personaje, float decimales, int parte_entera){
    if (((puntaje >= VALOR1_MIN_PUNTAJE) && (puntaje <= VALOR1_MAX_PUNTAJE)) && 
        ((parte_entera > VALOR_LIM_HORAS)|| ((parte_entera == VALOR_LIM_HORAS) && (decimales > VALOR_LIM_MINUTOS)))){
        (*personaje) = OLAF;
        printf("El personaje elegido para vencer todas las dificultades es -Olaf-\n");
    } else if (((puntaje >= VALOR1_MIN_PUNTAJE) && (puntaje <= VALOR1_MAX_PUNTAJE)) && 
        ((parte_entera < VALOR_LIM_HORAS)|| ((parte_entera == VALOR_LIM_HORAS) && (decimales <= VALOR_LIM_MINUTOS)))){
        (*personaje) = STITCH;
        printf("El personaje elegido para vencer todas las dificultades es -Stitch-\n");
    } else if (((puntaje > VALOR1_MAX_PUNTAJE) && (puntaje <= VALOR2_MAX_PUNTAJE)) && 
        ((parte_entera > VALOR_LIM_HORAS)|| ((parte_entera == VALOR_LIM_HORAS) && (decimales > VALOR_LIM_MINUTOS)))){
        (*personaje) = RAYO_MCQUEEN;
        printf("El personaje elegido para vencer todas las dificultades es -Rayo McQueen-\n");
    } else if (((puntaje > VALOR1_MAX_PUNTAJE) && (puntaje <= VALOR2_MAX_PUNTAJE)) && 
        ((parte_entera < VALOR_LIM_HORAS)|| ((parte_entera == VALOR_LIM_HORAS) && (decimales <= VALOR_LIM_MINUTOS)))){
        (*personaje) = JASMIN;
        printf("El personaje elegido para vencer todas las dificultades es -Jasmín-\n");
    }
   
}


int main () {
    printf("Tenes que rendir uno de los examenes más difíciles que la FIUBA haya hecho. Estuviste estudiando por semanas, pero cuando llega el día de rendir, observas en los noticieros ves que el noticiero dice: PARO DE MEDIOS DE TRANSPORTE EN TODO BUENOS AIRES POR 48 HORAS. Todo el exfuerzo quedaría en vano a menos que haya forma de cambiar esa posibilidad...\n");
    printf("Gracias a nuestros amigos Olaf, Stitch, Jasmín y Rayo Mcqueen, podremos llegar a destino y cumplir con nuestro objetivo. Cada uno tiene diferentes personalidades que nos podran ayudar!\n");

    char letra_transporte = ' ';
    pedir_usuario_transporte(&letra_transporte);

    printf("El transporte elegido es %c.\n", letra_transporte);

    char letra_manifestacion = ' ';
    pedir_usuario_manifestacion(&letra_manifestacion);

    printf("El metodo para deshacerte de la manifestación elegido es %c.\n", letra_manifestacion);

    float horario = 0;
    int parte_entera = 0;
    float decimales = 0;
    pedir_usuario_hora( &horario, &parte_entera, &decimales);
    printf ("La hora seleccionada es %.2f\n",horario);

    int nota = 0;
    pedir_usuario_nota( &nota);
    printf("La nota obtenida es %i.\n", nota);

    int multiplicador = 0;
    int letrat_int = 0;
    int letram_int = 0;
    int puntaje = 0;
    suma_puntaje (letra_transporte, letra_manifestacion, &letram_int, &letrat_int, nota, &multiplicador);
    printf("Multiplicador: %i", multiplicador);
    puntaje = letram_int + (letrat_int * multiplicador);  

    printf("El puntaje es: %i\n", puntaje);  

    char personaje = ' ';
    calculo_personaje( puntaje, &personaje, decimales, parte_entera);

   return 0;
}j