#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "comunication.h"
#include "conection.h"
#include "../structs/jugador.h"

char * revert(char * message){
  //Se invierte el mensaje
  
  int len = strlen(message) + 1;
  char * response = malloc(len);

  for (int i = 0; i < len-1; i++)
  {
    response[i] = message[len-2-i];
  }
  response[len-1] = '\0';
  return response;
}

int main(int argc, char *argv[]){
  printf("se inicializa el servidor\n");
  // Se define una IP y un puerto
  char * IP = "0.0.0.0";
  int PORT = 8080;

  // Se crea el servidor y se obtienen los sockets de ambos clientes.
  PlayersInfo * players_info = prepare_sockets_and_get_clients(IP, PORT);

  


  

  // Guardaremos los sockets en un arreglo e iremos alternando a quién escuchar.
  int sockets_array[4] = {players_info->socket_c1,
                          players_info->socket_c2,
                          players_info->socket_c3,
                          players_info->socket_c4};

  Jugador** jugadores_array = calloc(4, sizeof(Jugador*)); // Array de jugadores

  for (int i = 0; i < 4; i++)
  {

    char *welcome = (char*)malloc(23 * sizeof(char));
    sprintf(welcome, "Bienvenido Cliente %d!!", i);
    server_send_message(sockets_array[i], 0, welcome);
    free(welcome);
    int msg_code = server_receive_id(sockets_array[i]);
    char * client_name = server_receive_payload(sockets_array[i]);
    jugadores_array[i] = jugador_init(client_name, i);
    // printf("%s\n", client_name);
    printf("nombre jugador %d: %s\n", jugadores_array[i]->id, jugadores_array[i]->nombre);
  }

  char* game_begin = "inicio el juego";
  server_send_message(sockets_array[0], 1, game_begin);
  
  int my_attention = 0;
  while (1)
  {
    // Se obtiene el paquete del cliente 1
    int msg_code = server_receive_id(sockets_array[my_attention]);

    if (msg_code == 1) //El cliente me envió un mensaje a mi (servidor)
    {
      printf("entre a code 1\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);

      // Le enviaremos el mismo mensaje invertido jeje
      char * response = revert(client_message);

      // Le enviamos la respuesta
      server_send_message(sockets_array[my_attention], 1, response);
    }
    else if (msg_code == 2){ //El cliente le envía un mensaje al otro cliente
      printf("entre a code 2\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("Servidor traspasando desde %d a %d el mensaje: %s\n", my_attention+1, ((my_attention+1)%4)+1, client_message);

      // Mi atención cambia al otro socket
      my_attention = (my_attention + 1) % 4;
      server_send_message(sockets_array[my_attention], 2, client_message);
    }else if (msg_code == 10) //El cliente me envió un mensaje a mi (servidor) para MOSTRAR INFO
    {
      printf("entre a code 10 \n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      // Le enviamos la respuesta
      server_send_message(sockets_array[my_attention], 1, "vuelve a escoger una opcion");
    }

    else if (msg_code == 11) //El cliente me envió un mensaje a mi (servidor) para CREAR ALDEANO
    {
      printf("entre a code 11\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      if (strcmp(client_message,"minero") == 0){
        printf("jugador %i\n", jugadores_array[my_attention+1]->id);
        bool answer = crear_aldeano(jugadores_array[my_attention], 1);
        if (answer){
          char * client_message = "Minero creado\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
        else{
          char * client_message = "recursos insuficientes\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
      } else if (strcmp(client_message,"agricultor") == 0){
        printf("jugador %i\n", jugadores_array[my_attention+1]->id);
        bool answer = crear_aldeano(jugadores_array[my_attention], 1);
        if (answer){
          char * client_message = "Agricultor creado\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
        else{
          char * client_message = "recursos insuficientes\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
      } else if (strcmp(client_message,"ingeniero") == 0){
        printf("jugador %i\n", jugadores_array[my_attention+1]->id);
        bool answer = crear_aldeano(jugadores_array[my_attention], 1);
        if (answer){
          char * client_message = "Ingeniero creado\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
        else{
          char * client_message = "recursos insuficientes\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
      } else if (strcmp(client_message,"guerrero") == 0){
        printf("jugador %i\n", jugadores_array[my_attention+1]->id);
        bool answer = crear_aldeano(jugadores_array[my_attention], 1);
        if (answer){
          char * client_message = "Guerrero creado\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
        else{
          char * client_message = "recursos insuficientes\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
      }
      server_send_message(sockets_array[my_attention], 1, "vuelve a escoger una opcion");

      // Le enviaremos el mismo mensaje invertido jeje
      char * response = revert(client_message);

      // Le enviamos la respuesta
      server_send_message(sockets_array[my_attention], 1, response);
    }else if (msg_code == 13) //El cliente me envió un mensaje a mi (servidor) para SUBIR NIVEL
    {
      printf("entre a code 13 \n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      if (strcmp(client_message,"minero") == 0){
        char * client_message = "funcion por hacer\n";
        server_send_message(sockets_array[my_attention], 11, client_message);
      }
      else if (strcmp(client_message,"agricultor") == 0){
        char * client_message = "funcion por hacer\n";
        server_send_message(sockets_array[my_attention], 11, client_message);
      }
      else if (strcmp(client_message,"ingeniero") == 0){
        char * client_message = "funcion por hacer\n";
        server_send_message(sockets_array[my_attention], 11, client_message);
      }
      else if (strcmp(client_message,"guerrero") == 0){
        char * client_message = "funcion por hacer\n";
        server_send_message(sockets_array[my_attention], 11, client_message);
      }
      // Le enviamos la respuesta
      server_send_message(sockets_array[my_attention], 1, "vuelve a escoger una opcion");
    }
    if (msg_code == 14) //El cliente me envió un mensaje a mi (servidor) ATACAR
    {
      printf("entre a code 14\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      // Le enviamos la respuesta
      char * response = "funcion por hacer";
      server_send_message(sockets_array[my_attention], 11, response);
      server_send_message(sockets_array[my_attention], 1, "vuelve a escoger una opcion");
    }
    if (msg_code == 15) //El cliente me envió un mensaje a mi (servidor) ESPIAR
    {
      printf("entre a code 15\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      // Le enviamos la respuesta
      char * response = "funcion por hacer";
      server_send_message(sockets_array[my_attention], 11, response);
      server_send_message(sockets_array[my_attention], 1, "vuelve a escoger una opcion");
    } if (msg_code == 16) //El cliente me envió un mensaje a mi (servidor) robar
    {
      printf("entre a code 16\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      // Le enviamos la respuesta
      char * response = "funcion por hacer";
      server_send_message(sockets_array[my_attention], 11, response);
      server_send_message(sockets_array[my_attention], 1, "vuelve a escoger una opcion");
    } if (msg_code == 17) //El cliente me envió un mensaje a mi (servidor) pasar
    {
      printf("entre a code 17\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      // Le enviamos la respuesta
      char * response = "funcion por hacer";
      server_send_message(sockets_array[my_attention], 11, response);
      server_send_message(sockets_array[my_attention], 1, "vuelve a escoger una opcion");
    } if (msg_code == 18) //El cliente me envió un mensaje a mi (servidor) rendirse
    {
      printf("entre a code 18\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      // Le enviamos la respuesta
      char * response = "funcion por hacer";
      server_send_message(sockets_array[my_attention], 11, response);
      server_send_message(sockets_array[my_attention], 1, "vuelve a escoger una opcion");
    }
    printf("------------------\n");
  }
  return 0;
}
