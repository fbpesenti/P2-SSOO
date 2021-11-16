# P2-SSOO

## Integrantes 
- Francisco Balmaceda - 18623948
- Josefa Parra - 19643098
- Florencia Pesenti - 16640268
- Victoria Sanchez - 18623913
- Maria Paz Subiabre - 16640535 

## Instrucciones de Ejecución
Para ejecutar el proyecto se debe inicializar en la carpeta server un make para compilar el código y luego en consola para abrir el servidor la siguiente línea:
./server -i <ip_address> -p <tcp_port>

luego en otra consola para inicializar un cliente se ejecuta make y la siguiente línea:
./client -i <ip_address> -p <tcp_port>

Utilizando en el código actual como address: 0.0.0.0 y port: 8080

Luego de tener inicializados a los clientes, en consola se debe ingresar los nombres y se asignan los distintos aldeanos a su correspondiente rol. 
Cuando se encuentra todo listo el líder puede iniciar el juego presionando enter.

Cada jugador en su respectivo turno tendrá acceso a un menú en el cual se encontraran las opciones de Mostrar información, Crear Aldeano, Subir de Nivel, Atacar, Espiar, Robar, Pasar y Rendirse. Cada opción se despegara en la consola acompañada de un numero el cual el jugador deberá apretar según la opción deseada.

## Paquetes
Los paquetes utilizados 

## Decisiones de diseño
En primer lugar, el servidor es quien realiza toda la lógica del juego, mientras que el cliente es quien escoge que decisiones tomar. Se dispone de dos carpetas independientes, client y server. A continuación, se explicara cada una de ellas

### Server
Como se mencionó anteriormente, el servidor es quien realiza la lógica del juego, por lo que se incluye el archivo jugador.c en donde se construye la lógica de cada una de las opciones las cuales podría escoger el cliente, junto con los archivos comunication.c y conection.c en donde se maneja las conexiones y comunicaciones con el cliente.
Por último, se encuentra el archivo main.c en donde se reciben las opciones escogidas por el cliente, se realiza la lógica según sea el msg code recibido, y se envía la respuesta al cliente.

Los msg code con su respectiva explicación son los siguientes:
- msg_code: 10 -> Mostrar información 
- msg_code: 11 -> Crear Aldeano
- msg_code: 13 -> Subir Nivel 
- msg_code: 14 -> Atacar
- msg_code: 15 -> Espiar
- msg_code: 16 -> Robar
- msg_code: 17 -> Pasar
- msg_code: 18 -> Rendirse

### Cliente
El cliente tiene la única labor de escoger la opción que desea que se ejecute. Los archivos que contiene son: function.c en donde se realiza el menú de opciones, es aqui en donde se envía un msg code, según la opción escogida, al servidor. También se encuentran los archivos comunication.c y conection.c en donde se maneja las conexiones y comunicaciones con el servidor. Finalmente se encuentra el archivo main.c en donde se recibe los msg code del servidor y, según el msg code recibido, se despliega en consola al cliente la respuesta correspondiente.
Los msg code con su respectiva explicación son los siguientes:

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

## Principales Funciones del programa
- se conectan los clientes e inicializan los jugadores correctamente
- funciona correctamente cada una de las opciones del menú
-
## Supuestos
- El recolectar recursos se muestra en todos los turnos menos en el primero que se parte con 100 de cada recurso
- Cuando el jugador necesita el id de otro jugador en atacar/espiar/robar el jugador sabe que va de 0 a n-1, siendo n la cantidad de jugadores.
-
## FUNCIONAMIENTO (Para facilitar corrección)
- Rendirse solo funciona con dos clientes
- Cunado un jugador gana no se acaba el flujo del juego, solo avisa al ganador que ganó


