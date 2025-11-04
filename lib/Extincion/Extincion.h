#ifndef EXTINCION_H
#define EXTINCION_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include <pines.h>

/// @brief Ajusta sensores como salidas, adjuta los servos a sus pines, coloca la bomba en apagado y como salida
void iniciarExtincion(); 

/// @brief El servo_sensor hace un barrido cte al encontrar fuego se detiene y el servo_pum se dirige automaticamente a esa posicion
void seguirFlama();

/// @brief Lee los sensores y regresa un valor en funcion del umbral
/// @return true or false
bool leerSensores();                   

//-------------------------Funciones para Debugear-------------------//

/// @brief Manda los servos a su posicion 0
void zero_servo();

#endif
