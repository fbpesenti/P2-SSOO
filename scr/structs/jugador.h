#pragma once

struct jugador;
typedef struct jugador Jugador;

struct jugador
{
  // Nombre
  char* nombre;
  // id
  int id;
  // 0 si no es lider 1 si lo es
  int es_lider;
  // Recursos del jugador
  int oro;
  int comida;
  int ciencia;
  // Cantidad de aldeanos por tipo
  int n_mineros;
  int n_agricultores;
  int n_ingenieros;
  int n_guerreros;
  // Estos son los aldeanos no asignados
  int aldeanos;
  /*Lo que se podria hacer es tener la cantidad de cada tipo de aldeano y un identificador en que nivel van 
  ej: mineros =9 ;nivel=1
      ingernieros =2 ; nivel 3;
      etc.
  */ 
  int nivel_minero;
  int nivel_agricultores;
  int nivel_ingenieros;
  int nivel_guerreros;
};

// Inicializar el jugador con los stats iniciales
Jugador* jugador_init(char* nombre, int id);
// Se recolectan recursos al inicio del turno
void recolectar_recursos(Jugador* jug);
// Asignar aldeano inicialmente
/*
No se si hacer la asignacion separada de crear aldeanos 
Se diferencian que la asignacionse hace al inicio y se van descontando de los 9 aldeanos iniciales
y la segunda es dentro del juego mismo ya inciado
*/ 
void asignar_aldeano(Jugador* jug, int tipo);
// Crear el aldeano segun el tipo requerido (minero, agricultor, ingeniero, guerrero)
void crear_aldeano(Jugador* jug, int tipo);
// Mostrar información en menu (recursos, aldeano, niveles de aldeanos)
void mostrar_menu(Jugador* jug);
// Subir de nivel a x cosa (agri, mineros, ingenieros, ataque, defensa)
void subir_nive(Jugador* jug, int tipo);
// Atacar contrincante
void atacar(Jugador* curr, Jugador* other);
// Espiar
void espiar(Jugador* curr, Jugador* other);
// Robar
void robar(Jugador* curr, Jugador* other);
// Pasar
void pasar(Jugador* jug);
// Rendirse
void rendirse(Jugador* jug);

