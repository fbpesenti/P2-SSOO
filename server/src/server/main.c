#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "comunication.h"
#include "conection.h"
#include "../structs/jugador.h"

int numero_jug = 0;
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
    numero_jug++;
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
      my_attention = (my_attention + 1) % numero_jug;
      server_send_message(sockets_array[my_attention], 2, client_message);
    }else if (msg_code == 10) //El cliente me envió un mensaje a mi (servidor) para MOSTRAR INFO
    {
      printf("entre a code 10 \n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
    }
    else if (msg_code == 11) //El cliente me envió un mensaje a mi (servidor) para CREAR ALDEANO
    {
      printf("entre a code 11\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d creara un %s\n", my_attention+1, client_message);
      if (strcmp(client_message,"minero") == 0){
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
        bool answer = crear_aldeano(jugadores_array[my_attention], 2);
        if (answer){
          char * client_message = "Agricultor creado\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
        else{
          char * client_message = "recursos insuficientes\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
      } else if (strcmp(client_message,"ingeniero") == 0){
        bool answer = crear_aldeano(jugadores_array[my_attention], 3);
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
        bool answer = crear_aldeano(jugadores_array[my_attention], 4);
        if (answer){
          char * client_message = "Guerrero creado\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
        else{
          char * client_message = "recursos insuficientes\n";
          server_send_message(sockets_array[my_attention], 11, client_message);
        }
      }      

    }else if (msg_code == 13) //El cliente me envió un mensaje a mi (servidor) para SUBIR NIVEL
    {
      printf("entre a code 13 \n");
      printf("recursos comida %i, ciencia%i, oro %i\n", jugadores_array[my_attention]->comida, jugadores_array[my_attention]->ciencia, jugadores_array[my_attention]->oro);
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d quiere subir niver a %s\n", my_attention+1, client_message);
      if (strcmp(client_message,"minero") == 0){
        int n = subir_nivel(jugadores_array[my_attention],1);
        if (n == 0){
          server_send_message(sockets_array[my_attention], 11, "se aumento el nivel minero");
        }
        else if (n == 1){
          server_send_message(sockets_array[my_attention], 11, "nivel maximo, no se puede aumentar mas nivel minero");
        }
        else if (n== 2){
          server_send_message(sockets_array[my_attention], 11, "recursos insuficientes para aumentar nivel minero");
        }        
      }
      else if (strcmp(client_message,"agricultor") == 0){
        int n = subir_nivel(jugadores_array[my_attention],2);
        if (n == 0){
          server_send_message(sockets_array[my_attention], 11, "se aumento el nivel agricultores");
        }
        else if (n == 1){
          server_send_message(sockets_array[my_attention], 11, "nivel maximo, no se puede aumentar mas nivel agricultores");
        }
        else if (n== 2){
          server_send_message(sockets_array[my_attention], 11, "recursos insuficientes para aumentar nivel agricultores");
        }
      }
      else if (strcmp(client_message,"ingeniero") == 0){
        int n = subir_nivel(jugadores_array[my_attention],3);
        if (n == 0){
          server_send_message(sockets_array[my_attention], 11, "se aumento el nivel ingeniero");
        }
        else if (n == 1){
          server_send_message(sockets_array[my_attention], 11, "nivel maximo, no se puede aumentar mas nivel ingenieros");
        }
        else if (n== 2){
          server_send_message(sockets_array[my_attention], 11, "recursos insuficientes para aumentar nivel ingenieros");
        }
      }
      else if (strcmp(client_message,"ataque") == 0){
        int n = subir_nivel(jugadores_array[my_attention],4);
        if (n == 0){
          server_send_message(sockets_array[my_attention], 11, "se aumento el nivel ataque");
        }
        else if (n == 1){
          server_send_message(sockets_array[my_attention], 11, "nivel maximo, no se puede aumentar mas nivel ataque");
        }
        else if (n== 2){
          server_send_message(sockets_array[my_attention], 11, "recursos insuficientes para aumentar nivel ataque");
        }
      }
      else if (strcmp(client_message,"defensa") == 0){
        int n = subir_nivel(jugadores_array[my_attention],5);
        if (n == 0){
          server_send_message(sockets_array[my_attention], 11, "se aumento el nivel defensa");
        }
        else if (n == 1){
          server_send_message(sockets_array[my_attention], 11, "nivel maximo, no se puede aumentar mas nivel defensa");
        }
        else if (n== 2){
          server_send_message(sockets_array[my_attention], 11, "recursos insuficientes para aumentar nivel defensa");
        }
      }
      // Le enviamos la respuesta
    }
    if (msg_code == 14) //El cliente me envió un mensaje a mi (servidor) ATACAR
    {
      printf("entre a code 14\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      // Le enviamos la respuesta
      char * response = "funcion por hacer";
      server_send_message(sockets_array[my_attention], 11, response);
    }
    if (msg_code == 15) //El cliente me envió un mensaje a mi (servidor) ESPIAR
    {
      printf("entre a code 15\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      // Le enviamos la respuesta
      char * response = "funcion por hacer";
      server_send_message(sockets_array[my_attention], 11, response);
    } 
    if (msg_code == 16) //El cliente me envió un mensaje a mi (servidor) robar
    {
      printf("entre a code 16\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      // Le enviamos la respuesta
      char * response = "funcion por hacer";
      server_send_message(sockets_array[my_attention], 11, response);
    } 
    if (msg_code == 17) //El cliente me envió un mensaje a mi (servidor) pasar
    {
      printf("entre a code 17\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      // Le enviamos la respuesta
      char * response = "Jugador paso turno";
      server_send_message(sockets_array[my_attention], 11, response);
      // Mi atención cambia al otro socket
      my_attention = (my_attention + 1) % numero_jug;
    } 
    if (msg_code == 18) //El cliente me envió un mensaje a mi (servidor) rendirse
    {
      printf("entre a code 18\n");
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention, client_message);
      // Le enviamos la respuesta
      int temp = rendirse(jugadores_array[my_attention]);
      char * response = "Jugador se rindio";
      server_send_message(sockets_array[my_attention], 11, response);
      if(my_attention==4){
        sockets_array[my_attention]=NULL;
        jugadores_array[my_attention]=NULL;
      }
      else if(my_attention==3)
      {
        sockets_array[my_attention]=sockets_array[4];
        jugadores_array[my_attention]=jugadores_array[4];
        sockets_array[4]=NULL;
        jugadores_array[4]=NULL;
      }
      else if(my_attention==2)
      {
        sockets_array[my_attention]=sockets_array[3];
        jugadores_array[my_attention]=jugadores_array[3];
        sockets_array[3]=sockets_array[4];
        jugadores_array[3]=jugadores_array[4];
        sockets_array[4]=NULL;
        jugadores_array[4]=NULL;
      }
      else if(my_attention==1){
        sockets_array[my_attention]=sockets_array[2];
        jugadores_array[my_attention]=jugadores_array[2];
        sockets_array[2]=sockets_array[3];
        jugadores_array[2]=jugadores_array[3];
        sockets_array[3]=sockets_array[4];
        jugadores_array[3]=jugadores_array[4];
        sockets_array[4]=NULL;
        jugadores_array[4]=NULL;
      }
      // Mi atención cambia al otro socket
      numero_jug=numero_jug-1;
      if(numero_jug==1){
      // Proceder a terminar el juego
      }
      my_attention = (my_attention + 1) % numero_jug;
    }
    printf("------------------\n");
    server_send_message(sockets_array[my_attention], 1, "vuelve a escoger una opcion");
  }
  return 0;
}
