#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h> 
#include "conection.h"
#include "comunication.h"
#include "function.h"

char * get_input(){
  char * response = malloc(20);
  int pos=0;
  while (1){
    char c = getchar();
    if (c == '\n') break;
    response[pos] = c;
    pos++;
  }
  response[pos] = '\0';
  return response;
}

void* escuchador(void *atr){
  int server_socket = (int) atr;
  printf("Presione enter para empezar\n");
  char * opcion = get_input();
  client_send_message(server_socket, 0, opcion);
  pthread_exit(NULL);
}


int main (int argc, char *argv[]){
  //Se obtiene la ip y el puerto donde está escuchando el servidor (la ip y puerto de este cliente da igual)
  char * IP = "0.0.0.0";
  int PORT = 8080;

  // Se prepara el socket
  int server_socket = prepare_socket(IP, PORT);

  int intro = 1;

  while(intro){
    int msg_code = client_receive_id(server_socket);

    //aviso a lider de nueva conexion
    if (msg_code == 0)
    {
      char * message = client_receive_payload(server_socket);
      printf("ingresó jugador: %s\n", message);
    }
    
    // solicitud de nombre
    if (msg_code == 1) { //Recibimos un mensaje del servidor
      char * message = client_receive_payload(server_socket);
      printf("%s\n", message);
      free(message);

      printf("ingrese su nombre a continuacion: ");
      char * name = get_input();
      client_send_message(server_socket, 0, name);
    }
    if (msg_code == 2) { //Recibimos soliitud de ingresar aldeano
      char * message = client_receive_payload(server_socket);
      printf("%s\n", message);
      free(message);

      printf("ingrese opción: ");
      char * opcion = get_input();
      client_send_message(server_socket, 0, opcion);
    }
    if (msg_code == 3) { // Atento a empezar juego
      pthread_t point;
      char * message = client_receive_payload(server_socket);
      free(message);
      pthread_create(&point, NULL, escuchador, (void*)server_socket);
    }
    if (msg_code == 4) { // Imprime mensaje de servidor
      char * message = client_receive_payload(server_socket);
      printf("%s\n", message);
      free(message);
    }
    if (msg_code == 5) { // comienzo de juego
      char * message = client_receive_payload(server_socket);
      printf("%s\n", message);
      free(message);
      intro = 0;
    }
  }

  // Se inicializa un loop para recibir todo tipo de paquetes y tomar una acción al respecto
  while (1){
    int msg_code = client_receive_id(server_socket);
    
    
    if (msg_code == 1) { //Recibimos un mensaje del servidor
      printf("entre a code 1\n");
      char * message = client_receive_payload(server_socket);
      printf("El servidor dice: %s\n", message);
      free(message);
      // client_send_message(server_socket, 19, "1");
      bool turno = true;
      turno = principal_menu(server_socket);
      

      //printf("¿Qué desea hacer?\n   1)Enviar mensaje al servidor\n   2)Enviar mensaje al otro cliente\n");
      //int option = getchar() - '0';
      //getchar(); //Para capturar el "enter" que queda en el buffer de entrada stdin
      //printf("Ingrese su mensaje: ");
      //char * response = get_input();
      //client_send_message(server_socket, option, response);
    }
    if (msg_code == 17) {
      printf("entre a code 17\n");
      char * message = client_receive_payload(server_socket);
      printf("El servidor dice: %s\n", message);
      free(message);
      // bool turno = true;
      // turno = principal_menu(server_socket);
    }
    if (msg_code == 2){ //Recibimos un mensaje que proviene del otro cliente
    printf("entre a code 2\n");
      char * message = client_receive_payload(server_socket);
      printf("El otro cliente dice: %s\n", message);
      free(message);

      printf("¿Qué desea hacer?\n   1)Enviar mensaje al servidor\n   2)Enviar mensaje al otro cliente\n");
      int option = getchar() - '0';
      getchar(); //Para capturar el "enter" que queda en el buffer de entrada stdin
      
      printf("Ingrese su mensaje: ");
      char * response = get_input();

      client_send_message(server_socket, option, response);
    }
    
    if (msg_code == 11) { //Recibimos un mensaje del servidor
      printf("entre a code 11\n");
      char * message = client_receive_payload(server_socket);
      printf("%s\n", message);
      free(message);
    }
    if (msg_code == 10){
      //printf("entre a code 10\n");
      char * message = client_receive_payload(server_socket);
      printf("\n%s\n", message);
      free(message);

    }
    if (msg_code == 15){
      //printf("entre a code 15\n");
      char * message = client_receive_payload(server_socket);
      printf("\n%s\n", message);
      free(message);

    }
    if (msg_code == 16){
      //printf("entre a code 15\n");
      char * message = client_receive_payload(server_socket);
      printf("\n%s\n", message);
      free(message);
    }
    if (msg_code == 19){
      //printf("entre a code 15\n");
      char * message = client_receive_payload(server_socket);
      printf("\n%s\n", message);
      free(message);
    }
    //printf("------------------\n");
    
  }

  // Se cierra el socket
  close(server_socket);
  free(IP);

  return 0;
}
