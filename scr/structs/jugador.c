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

// void recolectar_recursos(Jugador* jug){

// }