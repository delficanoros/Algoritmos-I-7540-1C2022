// compilo con: gcc ej0.c -Wall -Werror -Wconversion -std=c99 -o ej0
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



bool letra_transporte_valida(char letra_transporte){
    if(letra_transporte == TRINEO){
           return true;
    } else if(letra_transporte == NAVE_ESPACIAL){
        return true;
    } else if(letra_transporte == CAMION){
        return true;
    } else if(letra_transporte == ALFOMBRA){
        return true;
    } else{
        return false;
       printf("La letra ingresada no es correcta, por favor vuelva a intentarlo\n");
}
    return (letra_transporte == TRINEO || letra_transporte == NAVE_ESPACIAL ||
       letra_transporte == CAMION || letra_transporte == ALFOMBRA);
}

void pedir_usuario_transporte(char* letra_transporte, bool* letra){
    printf("Estas saliendo de tu casa, y te enteras que hay paro de trenes, ¿Qué otro transporte elegis?\n");

    scanf(" %c", letra_transporte);



    while(!letra_transporte_valida(*letra_transporte)){
    printf("La letra ingresada no es correcta, por favor vuelva a intentarlo\n");
    scanf(" %c", letra_transporte);




    }    
}



    /*
     (letra_transporte == OLAF || letra_transporte == STITCH ||
       letra_transporte == JASMIN || letra_transporte == RAYO_MCQUEEN){
        return true;
       }else{
           return false;
       }
    return (letra_transporte == OLAF || letra_transporte == STITCH ||
       letra_transporte == JASMIN || letra_transporte == RAYO_MCQUEEN);
       
}
*/
// Sirve pero no con los codigos que se exigen
/*
char medio_transporte (char id_transporte){
	if(id_transporte == TRINEO){
		return printf("El metodo de transporte elegido es el TRINEO\n");
	} else if(id_transporte == NAVE_ESPACIAL){
		return printf("El metodo de transporte elegido es la NAVE ESPACIAL\n");
	} else if(id_transporte == CAMION){
		return printf("El metodo de transporte elegido es el CAMION\n");
    } else if(id_transporte == ALFOMBRA){
        return printf("El metodo de transporte elegido es la ALFOMBRA\n");
    } else{
		return printf("El metodo utilizado no es valido, intentelo de nuevo\n");;
	}
}*/
//funciona con los comandos pero no funciona correctamente
/*char medio_transporte (char id_transporte){
	if(id_transporte == TRINEO){
		return TRINEO;
	} else if(id_transporte == NAVE_ESPACIAL){
		return NAVE_ESPACIAL;
	} else if(id_transporte == CAMION){
		return CAMION;
    } else if(id_transporte == ALFOMBRA){
        return ALFOMBRA;
    } else{
		return ERROR;
    }
}*/

bool letra_manifestacion_valida(char letra_manifestacion){
    if (letra_manifestacion == BOLAS_DE_NIEVE){
        return true;
    } else if (letra_manifestacion == PIUM_PIUM){
        return true;
    } else if (letra_manifestacion == KUCHAU){
        return true;
    } else if (letra_manifestacion == GENIO){
        return true;
    } else {
        return false;
        printf("La letra ingresada no es correcta, por favor vuelva a intentarlo\n");
    }
    return (letra_manifestacion == BOLAS_DE_NIEVE|| letra_manifestacion == PIUM_PIUM ||
       letra_manifestacion == KUCHAU || letra_manifestacion == GENIO);
}



void pedir_usuario_manifestacion(char* letra_manifestacion, bool* letra_manifestacion_valida){
    printf("En medio del camino te encontras con una manifestación, ¿Que medio utilizas para deshacerte de la manifestación\n");
    
    scanf(" %c", letra_manifestacion);

    while(!letra_manifestacion_valida(*letra_manifestacion)){
        printf("La letra ingresada no es correcta, por favor vuelva a intentarlo\n");
        scanf(" %c", letra_manifestacion);
    }
}

int main () {

    printf("Introducción\n");

    char letra_transporte;
    bool letra_transporte_valida;
    pedir_usuario_transporte(&letra_transporte, &letra_transporte_valida);

    printf("El transporte elegido es %c\n", letra_transporte);

    char letra_manifestacion;
    bool letra_manifestacion_valida;
    pedir_usuario_manifestacion(&letra_manifestacion, &letra_manifestacion_valida);

    printf("El metodo para deshacerte de la manifestación elegido es %c\n", letra_transporte);

    return 0;
}