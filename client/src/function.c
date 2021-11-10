
#include <unistd.h>
#include <stdio.h>
#include "function.h"

void principal_menu(){
    printf("Menu Principal\n");
    printf("Escoger una accion:\n");
    printf("[0] Mostrar Informacion \n");
    printf("[1] Crear Aldeano\n");
    printf("[2] Subir de Nivel\n");
    printf("[3] Atacar\n");
    printf("[4] Espiar\n");
    printf("[5] Robar\n");
    printf("[6] Pasar\n");
    printf("[7] Rendirse\n");
    char c = getchar();
    getchar();
    //printf("char: %c\n", c);
    if (c == '0'){
        //mostrar info
    } else if (c == '1'){
        char id = crear_aldeano();
        printf("id %c\n", id);
    } else if (c == '2'){
        char id = subir_nivel();
        printf("id %c\n", id);
    } else if (c == '3'){
        char id = atacar();
        printf("id %c\n", id);
    } else if (c == '4'){
        char id = espiar();
        printf("id %c\n", id);
    } else if (c == '5'){
        char* id = robar();
        printf("[9] Oro \n");
        printf("id %d\n", id[0]);
        printf("id %d\n", id[1]);
        printf("[10] Oro \n");
    }
    
}

char crear_aldeano(){
    printf("Menu Crear Aldeano\n");
    printf("Escoger rol a asignar...\n");
    printf("[0] Minero\n");
    printf("[1] Agricultor\n");
    printf("[2] Ingeniero\n");
    printf("[3] Guerrero\n");
    char x = getchar();
    getchar();
    return x;
}

char subir_nivel(){
    printf("Menu Subir Nivel\n");
    printf("Escoger rol a subir de nivel...\n");
    printf("[0] Minero\n");
    printf("[1] Agricultor\n");
    printf("[2] Ingeniero\n");
    printf("[3] Guerrero\n");
    char x = getchar();
    getchar();
    return x;
}

char atacar(){
    printf("Menu atacar\n");
    printf("Escoger jugador a atacar...\n");
    printf("[0] \n");
    //VARIABLE SEGUN NUMERO DE JUGADORES
    char x = getchar();
    getchar();
    return x;
}

char espiar(){
    printf("Menu Espiar\n");
    printf("Escoger jugador a espiar...\n");
    printf("[0] \n");
    //VARIABLE SEGUN NUMERO DE JUGADORES
    char x = getchar();
    getchar();
    return x;
}

char * robar(){
    printf("Menu Robar\n");
    printf("Escoger jugador a robar...\n");
    printf("[0] \n");
    //VARIABLE SEGUN NUMERO DE JUGADORES
    char * c1 = getchar();
    getchar();
    printf("Robar comida o oro?\n");
    printf("[0] Comida \n");
    printf("[1] Oro \n");
    //VARIABLE SEGUN NUMERO DE JUGADORES
    char c2 = getchar();
    getchar();
    char array[2];
    printf("[0] Oro \n");
    array[0] = c1;
    printf("[1] Oro \n");
    array[1] = c2;
    printf("[2] Oro \n");
    return array;
}

int main (int argc, char *argv[]){
    principal_menu();
    //crear_aldeano();
    return 0;
}