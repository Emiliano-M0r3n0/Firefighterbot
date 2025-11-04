#include <Arduino.h>
#include "Extincion.h"
#include "Motores.h"

#define DEBUG_SERVOS false //Para salir del modo DEBUG_SERVOS solo cambiar a false

void setup() {
  Serial.begin(9600);       // Inicia comunicación serial a 9600 baudios
  iniciarExtincion();
  //iniciarmotores();
}

void loop() {
  if(DEBUG_SERVOS){
    zero_servo();
  }
  else
  {
    seguirFlama();
    //movgiroaxeder();
  }
}