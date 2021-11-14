# P2-SSOO

## Integrantes 
- Francisco Balmaceda - 18623948
- Josefa Parra - 19643098
- Florencia Pesenti - 16640268
- Victoria Sanchez - 18623913
- Maria Paz Subiabre - 16640535 

## Instrucciones de Ejecución

## Paquetes
### Descripción

## Decisiones de Diseños

## Principales Funciones del programa

## Supuestos


## FUNCIONAMIENTO

En client:
- msg code: 10 -> mostrar info
- msg code: 11 -> crear Aldeano
- msg code: 13 -> subir nivel
    - retorna 0 si se sube el nivel
    - retorna 1 si se esta en el maximo
    - retirna 2 si no hay recursos suficientes
- msg code: 14 -> atacar
- msg code: 15 -> ESPIAR
- msg code: 16 -> robar
- msg code: 17 -> pasar
- msg code: 18 -> rendirse

en server: la mayoria llega al msg code 11

Las funciones.c de client se mandan slo mensajes al servidor
