#include <Arduino.h>
#include "Extincion.h"
#include "Motores.h"

#define DEBUG_SERVOS false
#define DEBUG_MOTORES true

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
  else if(DEBUG_MOTORES)
  {
    //Primer movimiento
    movadelante();
    delay(2200);
    stop();
    delay(500);
    seguirFlama();
    delay(4000);
    //Segundo movimiento
    movderecha();
    delay(2200);
    stop();
    delay(500);
    seguirFlama();
    delay(4000);
    //Tercer movimiento
    movatras();
    delay(2200);
    stop();
    delay(500);
    seguirFlama();
    delay(4000);
    //Cuarto movimiento
    movizquierda();
    delay(2200);
    stop();
    delay(500);
    seguirFlama();
    delay(4000);
    //movgiroaxeizq();
    //movgiroaxeder();
    //cuadrado();
  }
  else
  {
    int time;
    movadelante();
    delay(1000);
    stop();
    delay(250);
    movgiroaxeizq();
    delay(time); 
    seguirFlama();
    delay(time);
    movgiroaxeizq();
    delay(time);
    movderecha();

    delay(time);
    movatras();
    delay(time);

  }
}
