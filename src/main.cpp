#include <Arduino.h>
#include <pines.h>
#include "Extincion.h"
#include "Motores.h"

#define DEBUG_SERVOS false
#define DEBUG_MECANUM false
#define DEBUG_WATER_PUMP true

unsigned long tInicio = 0;
bool haciendoBarrido = false;
const unsigned long tiempoMovimiento = 2200;
const unsigned long tiempoPausa = 500;
const unsigned long tiempoBarrido = 4000;

int estado = 0;
unsigned long ahora;

void setup() {
  Serial.begin(9600);       // Inicia comunicación serial a 9600 baudios
  iniciarExtincion();
  iniciarmotores();
}

void loop() {
  if(DEBUG_SERVOS){
    //En caso de querer usar alguna funcion para calibracion o arreglo de errores, comentar o descomentar la funcion segun sea tus necesidades
    zero_servo();
    barrido();
  }
  else if(DEBUG_MECANUM)
  {
    movadelante();
  }
  else if(DEBUG_WATER_PUMP)
  {
    int time = 4000;
    digitalWrite(WATER_PUMP,HIGH);
    delay(time);
    digitalWrite(WATER_PUMP,LOW);
    delay(time/4);
  }
  else
  {
      ahora = millis();

  switch (estado) {

    // ===Mover hacia adelante ===
    case 0:
      movnoroeste();
      tInicio = ahora;
      estado = 1;
      break;

    case 1:
      if (ahora - tInicio >= tiempoMovimiento) {
        stop();
        tInicio = ahora;
        estado = 2;
      }
      break;

    case 2:
      if (ahora - tInicio >= tiempoPausa) {
        haciendoBarrido = true;
        tInicio = ahora;
        estado = 3;
      }
      break;

    case 3:
      if (haciendoBarrido) seguirFlama();
      if (ahora - tInicio >= tiempoBarrido) {
        haciendoBarrido = false;
        estado = 4;
      }
      break;

    // === Mover a la derecha ===
    case 4:
      movderecha();
      tInicio = ahora;
      estado = 5;
      break;

    case 5:
      if (ahora - tInicio >= tiempoMovimiento) {
        stop();
        tInicio = ahora;
        estado = 6;
      }
      break;

    case 6:
      if (ahora - tInicio >= tiempoPausa) {
        haciendoBarrido = true;
        tInicio = ahora;
        estado = 7;
      }
      break;

    case 7:
      if (haciendoBarrido) seguirFlama();
      if (ahora - tInicio >= tiempoBarrido) {
        haciendoBarrido = false;
        estado = 8;
      }
      break;

    // ===  Mover hacia atrás ===
    case 8:
      movatras();
      tInicio = ahora;
      estado = 9;
      break;

    case 9:
      if (ahora - tInicio >= tiempoMovimiento) {
        stop();
        tInicio = ahora;
        estado = 10;
      }
      break;

    case 10:
      if (ahora - tInicio >= tiempoPausa) {
        haciendoBarrido = true;
        tInicio = ahora;
        estado = 11;
      }
      break;

    case 11:
      if (haciendoBarrido) seguirFlama();
      if (ahora - tInicio >= tiempoBarrido) {
        haciendoBarrido = false;
        estado = 12;
      }
      break;

    // ===  Mover a la izquierda ===
    case 12:
      movizquierda();
      tInicio = ahora;
      estado = 13;
      break;

    case 13:
      if (ahora - tInicio >= tiempoMovimiento) {
        stop();
        tInicio = ahora;
        estado = 14;
      }
      break;

    case 14:
      if (ahora - tInicio >= tiempoPausa) {
        haciendoBarrido = true;
        tInicio = ahora;
        estado = 15;
      }
      break;

    case 15:
      if (haciendoBarrido) seguirFlama();
      if (ahora - tInicio >= tiempoBarrido) {
        haciendoBarrido = false;
        estado = 16;
      }
      break;

    // === Reinicio del ciclo ===
    case 16:
      stop();
      estado = 0; // vuelve al inicio del ciclo
      break;
  }
  }
}
