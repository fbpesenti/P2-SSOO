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
  jug->oro = 0;
  jug->comida = 0;
  jug->ciencia = 0;
  jug->n_mineros = 0;
  jug->n_agricultores = 0;
  jug->n_ingenieros = 0;
  jug->n_guerreros = 0;
  jug->nivel_minero = 1;
  jug->nivel_agricultores = 1;
  jug->nivel_ingenieros = 1;
  jug->nivel_ataque = 1;
  jug->nivel_defensa = 1;

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
    if (jug->comida >10 & jug->oro >5)
    {
      jug->n_mineros++; 
      jug->comida=jug->comida-10;
      jug->oro=jug->oro-5;
    }
  }
  else if (tipo=2)
  {
    if (jug->comida >10)
    {
      jug->n_agricultores++;
      jug->comida=jug->comida-10;
    }
  }
  else if (tipo=3)
  {
    if (jug->comida >20 & jug->oro >10)
    {
      jug->n_ingenieros++;
      jug->comida=jug->comida-20;
      jug->oro=jug->oro-10;
    }
  }
  else if (tipo=4)
  {
    if (jug->comida >10 & jug->oro >10)
    {
      jug->n_guerreros ++;
      jug->comida=jug->comida-10;
      jug->oro=jug->oro-10;
    }
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




//CUALQUIER DUDA DE ESTAS ME PREGUNTAN (Pachi)

// -----mostrar info -------------------------

void mostrar_informacion(Jugador* jug){
  printf("Informacion...:\n");
  printf("Recursos\n");
  printf("Comida: %i\n", jug->comida);
  printf("Oro: %i\n", jug->oro);

  printf("Aldeanos\n");
  printf("Agricultores: %i - Nivel: %i\n", jug->n_agricultores, jug->nivel_agricultores);
  printf("Mineros: %i- Nivel: %i\n", jug->n_mineros, jug->nivel_minero);
  printf("Guerrers: %i- Nivel: %i\n", jug->n_guerreros, jug->nivel_guerreros);
  printf("Ingenieros: %i- Nivel: %i\n", jug->n_ingenieros, jug->nivel_ingenieros);
  
}
//--subir nivel--------------------------

void subir_nivel_minero(Jugador* jug){
  if (jug->nivel_minero == 1){
      if (jug->comida>10 & jug->oro>10 & jug->ciencia>10){
        jug->comida -= 10;
        jug->oro -= 10;
        jug->ciencia -= 10;
        jug->nivel_minero += 1;
        printf("AUMENTO DE NIVEL: 1-> 2\n");
        return;
      }
    }
    else if (jug->nivel_minero == 2){
      if (jug->comida>20 & jug->oro>20 & jug->ciencia>20){
        jug->comida -= 20;
        jug->oro -= 20;
        jug->ciencia -= 20;
        jug->nivel_minero += 1;
        printf("AUMENTO DE NIVEL: 2-> 3\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_minero == 3){
      if (jug->comida>30 & jug->oro>30 & jug->ciencia>30){
        jug->comida -= 30;
        jug->oro -= 30;
        jug->ciencia -= 30;
        jug->nivel_minero += 1;
        printf("AUMENTO DE NIVEL: 3-> 4\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_minero == 4){
      if (jug->comida>40 & jug->oro>40 & jug->ciencia>40){
        jug->comida -= 40;
        jug->oro -= 40;
        jug->ciencia -= 40;
        jug->nivel_minero += 1;
        printf("AUMENTO DE NIVEL: 4-> 5\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_minero == 5){
      printf("Estas en el nivel maximo\n");
      return;
    }
}
void subir_nivel_agricultor(Jugador* jug){
  if (jug->nivel_agricultores == 1){
      if (jug->comida>10 & jug->oro>10 & jug->ciencia>10){
        jug->comida -= 10;
        jug->oro -= 10;
        jug->ciencia -= 10;
        jug->nivel_agricultores += 1;
        printf("AUMENTO DE NIVEL: 1-> 2\n");
        return;
      }
    }
    else if (jug->nivel_agricultores == 2){
      if (jug->comida>20 & jug->oro>20 & jug->ciencia>20){
        jug->comida -= 20;
        jug->oro -= 20;
        jug->ciencia -= 20;
        jug->nivel_agricultores += 1;
        printf("AUMENTO DE NIVEL: 2-> 3\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_agricultores == 3){
      if (jug->comida>30 & jug->oro>30 & jug->ciencia>30){
        jug->comida -= 30;
        jug->oro -= 30;
        jug->ciencia -= 30;
        jug->nivel_agricultores += 1;
        printf("AUMENTO DE NIVEL: 3-> 4\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_agricultores == 4){
      if (jug->comida>40 & jug->oro>40 & jug->ciencia>40){
        jug->comida -= 40;
        jug->oro -= 40;
        jug->ciencia -= 40;
        jug->nivel_agricultores += 1;
        printf("AUMENTO DE NIVEL: 4-> 5\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_agricultores == 5){
      printf("Estas en el nivel maximo\n");
      return;
    }
}
void subir_nivel_ingeniero(Jugador* jug){
  if (jug->nivel_ingenieros == 1){
      if (jug->comida>10 & jug->oro>10 & jug->ciencia>10){
        jug->comida -= 10;
        jug->oro -= 10;
        jug->ciencia -= 10;
        jug->nivel_ingenieros += 1;
        printf("AUMENTO DE NIVEL: 1-> 2\n");
        return;
      }
    }
    else if (jug->nivel_ingenieros == 2){
      if (jug->comida>20 & jug->oro>20 & jug->ciencia>20){
        jug->comida -= 20;
        jug->oro -= 20;
        jug->ciencia -= 20;
        jug->nivel_ingenieros += 1;
        printf("AUMENTO DE NIVEL: 2-> 3\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_ingenieros == 3){
      if (jug->comida>30 & jug->oro>30 & jug->ciencia>30){
        jug->comida -= 30;
        jug->oro -= 30;
        jug->ciencia -= 30;
        jug->nivel_ingenieros += 1;
        printf("AUMENTO DE NIVEL: 3-> 4\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_ingenieros == 4){
      if (jug->comida>40 & jug->oro>40 & jug->ciencia>40){
        jug->comida -= 40;
        jug->oro -= 40;
        jug->ciencia -= 40;
        jug->nivel_ingenieros += 1;
        printf("AUMENTO DE NIVEL: 4-> 5\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_ingenieros == 5){
      printf("Estas en el nivel maximo\n");
      return;
    }
}
void subir_nivel_guerrero(Jugador* jug){
  if (jug->nivel_guerreros == 1){
      if (jug->comida>10 & jug->oro>10 & jug->ciencia>10){
        jug->comida -= 10;
        jug->oro -= 10;
        jug->ciencia -= 10;
        jug->nivel_defensa += 1;
        jug->nivel_ataque += 1;
        printf("AUMENTO DE NIVEL: 1-> 2\n");
        return;
      }
    }
    else if (jug->nivel_guerreros == 2){
      if (jug->comida>20 & jug->oro>20 & jug->ciencia>20){
        jug->comida -= 20;
        jug->oro -= 20;
        jug->ciencia -= 20;
        jug->nivel_defensa += 1;
        jug->nivel_ataque += 1;
        printf("AUMENTO DE NIVEL: 2-> 3\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_guerreros == 3){
      if (jug->comida>30 & jug->oro>30 & jug->ciencia>30){
        jug->comida -= 30;
        jug->oro -= 30;
        jug->ciencia -= 30;
        jug->nivel_defensa += 1;
        jug->nivel_ataque += 1;
        printf("AUMENTO DE NIVEL: 3-> 4\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_guerreros == 4){
      if (jug->comida>40 & jug->oro>40 & jug->ciencia>40){
        jug->comida -= 40;
        jug->oro -= 40;
        jug->ciencia -= 40;
        jug->nivel_defensa += 1;
        jug->nivel_ataque += 1;
        printf("AUMENTO DE NIVEL: 4-> 5\n");
        return;
      }
      printf("faltan recursos :(\n");
    }
    else if (jug->nivel_guerreros == 5){
      printf("Estas en el nivel maximo\n");
      return;
    }
}
void subir_nivel(Jugador* jug, int tipo){
  if (tipo == 1){ //nivel minero
    subir_nivel_minero(jug);
  } else if (tipo == 2){
    subir_nivel_agricultor(jug);
  } else if (tipo == 3){
    subir_nivel_ingeniero(jug);
  } else if (tipo == 4){
    subir_nivel_guerrero(jug);
  }
}
//---------curr ataca a other ---------
void atacar(Jugador* curr, Jugador* other){
  curr->fuerza = curr->nivel_guerreros * curr->nivel_ataque;
  other->nivel_defensa = (other->nivel_guerreros * other->nivel_ataque) * 2;
  if (curr > other){
    curr->comida += other->comida;
    other->comida = 0;
    curr->oro += other->oro;
    other->oro = 0;
    curr->ciencia += other->ciencia;
    other->ciencia = 0;
    //ACA SE DEBERIA ELIMINAR EL JUGADOR

  } else{
    curr->nivel_guerreros = curr->n_guerreros/2;

  }


}
//-----------curr espia a other---------------
void espiar(Jugador* curr, Jugador* other){
  if (curr->oro>30){
    curr->oro -= 30;
    printf("Espiando....\n");
    printf("cantidad guerreros: %i", other->n_guerreros);
    printf("nivel defenza: %i", other->nivel_defensa);
    printf("nivel ataque: %i", other->nivel_ataque);

  } else{
    printf("no hay suficientes recursos\n");
  }

}
//--------------------------



int main(int argc, char const *argv[])
{
  printf("\n:)\n");
  return 0;
}