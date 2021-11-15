
#include <unistd.h>
#include <stdio.h>
#include "function.h"
#include <stdbool.h> 

bool principal_menu(int server_socket){
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
        client_send_message(server_socket, 10, "mostar info");
        //mostrar info
    } else if (c == '1'){
        char id = menu_crear_aldeano();
        if (id == '0'){
            client_send_message(server_socket, 11, "minero");
        } else if (id == '1'){
            client_send_message(server_socket, 11, "agricultor");
        } else if (id == '2'){
            client_send_message(server_socket, 11, "ingeniero");
        } else if (id == '3'){
            client_send_message(server_socket, 11, "ataque");
        } else if (id == '4'){
            client_send_message(server_socket, 11, "defensa");
        }
        

    } else if (c == '2'){
        char id = menu_subir_nivel();
        printf("id %c\n", id);
        if (id == '0'){
            client_send_message(server_socket, 13, "minero");
        } else if (id == '1'){
            client_send_message(server_socket, 13, "agricultor");
        } else if (id == '2'){
            client_send_message(server_socket, 13, "ingeniero");
        } else if (id == '3'){
            client_send_message(server_socket, 13, "ataque");
        } else if (id == '4'){
            client_send_message(server_socket, 13, "defensa");
        }
    } else if (c == '3'){
        char id = menu_atacar();
        client_send_message(server_socket, 14, "Atacar");
        //printf("id %c\n", id);
    } else if (c == '4'){
        char id = menu_espiar();
        client_send_message(server_socket, 15, "espiar");
    } else if (c == '5'){
        char* id = menu_robar();
        client_send_message(server_socket, 16, "robar");
    }
    else if (c == '6'){
        printf("Fin del turno\n");
        client_send_message(server_socket, 17, "pasar");
        return false;
    }
    else if (c == '7'){
        printf("rendirse\n");
        client_send_message(server_socket, 18, "rendirse");
        return false;
    }
    return true;
    
}

char menu_crear_aldeano(){
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

char menu_subir_nivel(){
    printf("Menu Subir Nivel\n");
    printf("Escoger rol a subir de nivel...\n");
    printf("[0] Minero\n");
    printf("[1] Agricultor\n");
    printf("[2] Ingeniero\n");
    printf("[3] Ataque\n");
    printf("[4] Defensa\n");
    char x = getchar();
    getchar();
    return x;
}

char menu_atacar(){
    printf("Menu atacar\n");
    printf("Escoger jugador a atacar...\n");
    printf("[0] \n");
    //VARIABLE SEGUN NUMERO DE JUGADORES
    char x = getchar();
    getchar();
    return x;
}

char menu_espiar(){
    printf("Menu Espiar\n");
    printf("Escoger jugador a espiar...\n");
    printf("[0] \n");
    //VARIABLE SEGUN NUMERO DE JUGADORES
    char x = getchar();
    getchar();
    return x;
}

char * menu_robar(){
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
    char * array[2];
    printf("[0] Oro \n");
    array[0] = c1;
    printf("[1] Oro \n");
    array[1] = c2;
    printf("[2] Oro \n");
    return array;
}



//int main (int argc, char *argv[]){
    //principal_menu();
    //crear_aldeano();
    //return 0;
//}