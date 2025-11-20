#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_
// Definiciones de Sensores Ultrasónicos
// Variables Globales para Lectura Ultrasónica
extern float distanciaIzquierda;
extern float distanciaDerecha;
// Constantes
const int DISTANCIA_SEGURIDAD = 3;
const long INTERVALO_LECTURA_US = 50; // Intervalo para leer US en ms (ej. 50 ms)


float medirDistancia(int trigPin, int echoPin);

void initultrasonic();

void leerSensoresUS();

#endif