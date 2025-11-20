#include "Ultrasonico.h"
#include <pines.h>
#include <Arduino.h>
// Variables para el control de tiempo y datos
unsigned long tUltimaLecturaUS = 0;
float distanciaIzquierda = 400.0; // Inicializar a un valor seguro
float distanciaDerecha = 400.0;

void initultrasonic()
{
    pinMode(TRIG_ONE, OUTPUT);
    pinMode(ECHO_ONE, INPUT);
    pinMode(TRIG_TWO, OUTPUT);
    pinMode(ECHO_TWO, INPUT);
}

float medirDistancia(int trigPin, int echoPin) {
    // 1. Limpiar el pin TRIG
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // 2. Generar el pulso TRIG de 10us
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // 3. Leer el tiempo del pulso ECHO
    long duracion = pulseIn(echoPin, HIGH);

    // 4. Calcular la distancia: cm = (duracion del pulso / 2) / 29.1 
    // (La velocidad del sonido es aprox. 343 m/s o 29.1 us/cm)
    float distancia = duracion * 0.0343 / 2; // O duracion / 58.2;
    
    // Si la distancia es muy grande (fuera de rango) o 0, limitarla
    if (distancia == 0 || distancia > 400) return 400; 

    return distancia;
}

// Función principal de lectura NO BLOQUEANTE
void leerSensoresUS() {
    unsigned long ahora = millis();

    if (ahora - tUltimaLecturaUS >= INTERVALO_LECTURA_US) {
        tUltimaLecturaUS = ahora;
        
        // Asumiendo que has hecho los pinMode(TRIG/ECHO, OUTPUT/INPUT) en setup
        distanciaIzquierda = medirDistancia(TRIG_ONE, ECHO_ONE);
        distanciaDerecha = medirDistancia(TRIG_TWO, ECHO_TWO);
    }
}