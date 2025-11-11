#include <Arduino.h>
#include "Extincion.h"
#include "Motores.h"

#define DEBUG_SERVOS false

void setup() {
  Serial.begin(9600);       // Inicia comunicación serial a 9600 baudios
  iniciarExtincion();
  iniciarmotores();
}

void loop() {
  if(DEBUG_SERVOS){
    zero_servo();
    delay(500);
  }
  else
  {
    seguirFlama();
    movadelante();
    delay(750);
    movderecha();
    delay(750);
    movatras();
    delay(750);
    movizquierda();
    //movgiroaxeder();
  }
}