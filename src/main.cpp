#include <stdio.h>
#include <Arduino.h>
#include "Extincion.h"

void setup() {
  Serial.begin(9600);       // Inicia comunicación serial a 9600 baudios
  iniciarExtincion();
}

void loop() {
  digitalWrite(WATER_PUMP,LOW);
  leerSensores();
  if(leerSensores() == 1)
  {
    digitalWrite(WATER_PUMP,HIGH);
    seguirFlama();
  }
  else
  {
    digitalWrite(WATER_PUMP,LOW);
  }
  delay(5); 
}
