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
  char *welcome = (char*)malloc(24 * sizeof(char));
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
  printf("se inicializa el servidor\n");
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
  server_send_message(sockets_array[0], 4, "Elija las profecsiones de sus 9 primeros aldeanos\n");
  for (int i = 0; i < 9; i++)
  {
    char* message = (char*)malloc(62 * sizeof(char));
    sprintf(message, "Aldeano %d:\n1.-Agricultor 2.-Minero 3.-Ingeniero 4.-Guerrero\n", i);
    server_send_message(sockets_array[0], 2, message);
    free(message);
    int msg_code = server_receive_id(sockets_array[0]);
    char * type_char = server_receive_payload(sockets_array[0]);
    int type = atoi(type_char);
    asignar_aldeano(jugadores_array[0], type);
  }
  pthread_mutex_lock(&lock2);
  n_jugadores++;
  pthread_mutex_unlock(&lock2);
  server_send_message(sockets_array[0], 3, "");
  
  while (1)
  {
    int msg_code = server_receive_id(sockets_array[0]);
    if (msg_code == 0)
    {
      for (int i = 0; i < n_jugadores; i++)
      {
        server_send_message(sockets_array[i], 5, "Comienza el juego");
      }
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
      my_attention = (my_attention + 1) % n_jugadores;
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
      my_attention = (my_attention + 1) % n_jugadores;
      
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
      n_jugadores=n_jugadores-1;
      if(n_jugadores==1){
        printf("Se termina el juego");
      }
      my_attention = (my_attention + 1) % n_jugadores;
    }
    printf("------------------\n");
    server_send_message(sockets_array[my_attention], 1, "vuelve a escoger una opcion");
  }
  return 0;
}
