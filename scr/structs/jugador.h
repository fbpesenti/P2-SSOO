#pragma once

struct jugador;
typedef struct jugador Jugador;

struct jugador
{
  char* nombre;
  int id;
  int es_lider; // 0 si no es lider 1 si lo es
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
  int nivel_ataque;
  int nivel_defensa;
  int defensa;
  int fuerza;
};

// Inicializar el jugador con los stats iniciales
Jugador* jugador_init(char* nombre, int id);
// Se recolectan recursos al inicio del turno
void recolectar_recursos(Jugador* jug);
// Asignar aldeano inicialmente
void asignar_aldeano(Jugador* jug, int tipo);
// Crear el aldeano segun el tipo requerido (minero, agricultor, ingeniero, guerrero)
void crear_aldeano(Jugador* jug, int tipo);


// Subir de nivel a x cosa (agri, mineros, ingenieros, ataque, defensa)
void subir_nivel(Jugador* jug, int tipo);
//la funcion de arriba utiliza estas sub funciones
void subir_nivel_minero(Jugador* jug);
void subir_nivel_agricultor(Jugador* jug);
void subir_nivel_ingeniero(Jugador* jug);
void subir_nivel_guerreros(Jugador* jug);
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

void mostrar_informacion(Jugador* jug);
