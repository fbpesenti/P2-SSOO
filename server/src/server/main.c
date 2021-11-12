#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
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

int n_jugadores = 0;
Jugador* jugadores_array[4];
int sockets_array[4];
int server_socket;
pthread_mutex_t lock;
pthread_mutex_t lock2;

void* common_thread (void *atr){
  printf("id recibido: %d\n", (int)atr);
  int id = (int) atr;
  char *welcome = (char*)malloc(23 * sizeof(char));
  sprintf(welcome, "Bienvenido Cliente %d!!", id);
  server_send_message(sockets_array[id], 1, welcome);
  free(welcome);
  pthread_mutex_unlock(&lock);
  int msg_code = server_receive_id(sockets_array[id]);
  char * client_name = server_receive_payload(sockets_array[id]);
  jugadores_array[id] = jugador_init(client_name, id);
  // printf("%s\n", client_name);
  printf("nombre jugador %d: %s\n", jugadores_array[id]->id, jugadores_array[id]->nombre);
  server_send_message(sockets_array[0], 0, client_name);

  for (int i = 0; i < 9; i++)
  {
    char* message = "Elija:\n1.-Agricultor 2.-Minero 3.-Ingeniero 4.-Guerrero\n";
    server_send_message(sockets_array[id], 2, message);
    int msg_code = server_receive_id(sockets_array[id]);
    char * type_char = server_receive_payload(sockets_array[id]);
    int type = atoi(type_char);
    asignar_aldeano(jugadores_array[id], type);
  }

  pthread_mutex_lock(&lock2);
  n_jugadores++;
  pthread_mutex_unlock(&lock2);

  pthread_exit(NULL);
  return NULL;
}

void* creador_threads(void *atr){
  pthread_t threads[3];
  for (int i = 0; i < 3; i++)
  {
    pthread_mutex_lock(&lock);
    int id = i+1;
    sockets_array[i+1]= get_client(server_socket);
    printf("id es: %d \n", id);
    pthread_create(&threads[i], NULL, common_thread, (void*)id);
  }
}

int main(int argc, char *argv[]){
  // Se define una IP y un puerto
  char * IP = "0.0.0.0";
  int PORT = 8080;
  // Se prepara socket de servidor
  server_socket = prepare_socket(IP, PORT);
  sockets_array[0] = get_client(server_socket);

  pthread_t creador;
  pthread_create(&creador, NULL, creador_threads, (void*)NULL);

  char *welcome = (char*)malloc(30 * sizeof(char));
  sprintf(welcome, "Bienvenido Cliente lider %d!!", 0);
  server_send_message(sockets_array[0], 1, welcome);
  free(welcome);
  int msg_code = server_receive_id(sockets_array[0]);
  char * client_name = server_receive_payload(sockets_array[0]);
  jugadores_array[0] = jugador_init(client_name, 0);
  // printf("%s\n", client_name);
  printf("nombre jugador %d: %s\n", jugadores_array[0]->id, jugadores_array[0]->nombre);
  sockets_array[0] = sockets_array[0];
  pthread_mutex_lock(&lock2);
  n_jugadores++;
  pthread_mutex_unlock(&lock2);
  
  while (1)
  {
    int msg_code = server_receive_id(sockets_array[0]);
    if (msg_code == 0)
    {
      break;
    }
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
