#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "jugador.h"

Jugador* jugador_init(char* nombre, int id){
  Jugador* jug = malloc(sizeof(Jugador));
  jug->id = id;
  jug->nombre = nombre;
  jug->aldeanos=9; 
  if(id==1){
    jug->es_lider=1;
  }
  else{
    jug->es_lider=0;
  }
  // Inicializan en cero y cuando son asignados los aldeanos 
  // los niveles deben en empezar en 1 y se asignan los nueve
  // aldeanos al cada tipo
  jug->oro=0;
  jug->comida=0;
  jug->ciencia=0;
  jug->n_mineros=0;
  jug->n_agricultores=0;
  jug->n_ingenieros=0;
  jug->n_guerreros=0;
  jug->nivel_minero=1;
  jug->nivel_agricultores=1;
  jug->nivel_ingenieros=1;
  jug->nivel_guerreros=1;

}

void recolectar_recursos(Jugador* jug){
  
  int new_oro = jug->n_mineros*jug->nivel_minero*2;
  int new_comida = jug->n_agricultores*jug->nivel_agricultores*2;
  int new_ciencia = jug->n_ingenieros*jug->nivel_ingenieros;
  // Se recolectan los recursos y se agregan a los atributos
  jug->oro = jug->oro+new_oro;
  jug->comida = jug->comida+new_comida;
  jug->ciencia = jug->ciencia+new_ciencia;

  /*No se si imprimir aqui o hacemos una funcion que imprime despues*/ 
}

void asignar_aldeano(Jugador* jug, int tipo){
  /* El tipo se designa por el numero
    1 = minero
    2 = agricultor
    3 = ingeniero
    4 = guerrero
  */ 
  if (tipo = 1)
  {
   jug->n_mineros++; 
  }
  else if (tipo=2)
  {
    jug->n_agricultores++;
  }
  else if (tipo=3)
  {
    jug->n_ingenieros++;
  }
  else if (tipo=4)
  {
    jug->n_guerreros ++;
  }
  // restar un aldeano de los 9 iniciales
  jug->aldeanos=jug->aldeanos-1;
  
}

void crear_aldeano(Jugador* jug, int tipo){
  if (tipo = 1)
  {
   jug->n_mineros++; 
   jug->comida=jug->comida-10;
   jug->oro=jug->oro-5;
  }
  else if (tipo=2)
  {
    jug->n_agricultores++;
    jug->comida=jug->comida-10;
    jug->oro=jug->oro-5;
  }
  else if (tipo=3)
  {
    jug->n_ingenieros++;
    jug->comida=jug->comida-20;
    jug->oro=jug->oro-10;
  }
  else if (tipo=4)
  {
    jug->n_guerreros ++;
    jug->comida=jug->comida-10;
    jug->oro=jug->oro-10;
  }
}

void mostrar_menu(Jugador* jug){
  /* 
    -Debe mostrar la cantidad de recursos
    -la cantidad de aldeanos en cada rol
    -nivel de cada rol
    No lo implemente porque no se si se deben imprimir o pasarlos 
    como un mensaje del socket?
  */ 
}

