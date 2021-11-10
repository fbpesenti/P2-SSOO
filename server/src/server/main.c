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
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);

      // Le enviaremos el mismo mensaje invertido jeje
      char * response = revert(client_message);

      // Le enviamos la respuesta
      server_send_message(sockets_array[my_attention], 1, response);
    }
    else if (msg_code == 2){ //El cliente le envía un mensaje al otro cliente
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("Servidor traspasando desde %d a %d el mensaje: %s\n", my_attention+1, ((my_attention+1)%4)+1, client_message);

      // Mi atención cambia al otro socket
      my_attention = (my_attention + 1) % 4;

      server_send_message(sockets_array[my_attention], 2, client_message);
    }
    printf("------------------\n");
  }

  return 0;
}
