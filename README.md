# P2-SSOO

## Integrantes 
- Francisco Balmaceda - 18623948
- Josefa Parra - 19643098
- Florencia Pesenti - 16640268
- Victoria Sanchez - 18623913
- Maria Paz Subiabre - 16640535 

## Instrucciones de Ejecución
Para ejecutar el proyecto se debe inicializar en la carpeta server un make para compilar el codigo y luego en consola para abrir el servidor la siguiente linea:
`.\server -i -p`

luego en otra consola para iniciarlizar un cliente se ejecuta make y la siguiente linea:
`.\client -i -p`

Luego de tener inicializados a los clientes, en consola se ingresan los nombres y se asignan los distintos aldeanos a su correspondiente rol. 
Cuando se encuentra todo listo el lider puede iniciar el juego haciendo enter.

## Paquetes
### Server
- msg_code: 10 -> Mostrar información 
- msg_code: 11 -> Crear Aldeano
- msg_code: 13 -> Subir Nivel 
    - Mensaje: minero; ingeniero; agricultor; ataque; defensa
- msg_code: 14 -> Atacar
- msg_code: 15 -> Espiar
- msg_code: 16 -> Robar
- msg_code: 17 -> Pasar
- msg_code: 18 -> Rendirse

### Cliente
- msg_code: 1 -> Solicitar nombre
- msg_code: 2 -> Asignar Aldeano
- msg_code: 3 -> Empezar el juego
- msg_code: 4 -> imprimir mensaje servidor
- msg_code: 5 -> comenzar el juego

- msg_code: 11 -> llegan
    - Crear aldeano
    - Subir nivel
    - Atacar
- msg_code: 15 -> Espiar
- msg_code: 16 -> Robar
- msg_code: 19 -> Recoger recursos
- msg_code: 10 -> mostrar informacion

## Decisiones de Diseños

## Principales Funciones del programa

## Supuestos
- El recolectar recursos se muestra en todos los turnos menos en el primero que se parte con 100 de cada recurso
- Cuando el jugador necesita el id de otro jugador en atacar/espiar/robar el jugador sabe que va de 0 a n-1, siendo n la cantidad de jugadores.
## FUNCIONAMIENTO


en server: la mayoria llega al msg code 11

Las funciones.c de client se mandan slo mensajes al servidor
