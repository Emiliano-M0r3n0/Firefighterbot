#ifndef EXTINCION_H
#define EXTINCION_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include <pines.h>

/// @brief Ajusta los sensores como entradas y pone en apagado la bomba
void iniciarExtincion(); 
/**
 * @brief Guarda la lectura de los sensores, hace una diferencia entre ellos y en base a esto mueve el servo hacia la posicion con el fuego
 * 
 * @return * void 
 */
void seguirFlama();
/**
 * @brief Lee los sensores, en caso de detectar fuego regresa un 1 de otro caso regresa un 0
 * 
 * @return *int
 */
int leerSensores();                   


#endif
