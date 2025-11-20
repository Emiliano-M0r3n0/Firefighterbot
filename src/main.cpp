#include <Arduino.h>
#include <pines.h>
#include "Extincion.h"
#include "Motores.h"
#include "Ultrasonico.h"

#define DEBUG_SERVOS false
#define DEBUG_MECANUM false
#define DEBUG_WATER_PUMP true
#define DEBUG_ECHO false


void setup() {
  Serial.begin(9600);       // Inicia comunicación serial a 9600 baudios
  iniciarExtincion();
  iniciarmotores();
  initultrasonic();
}

void loop() {
    leerSensoresUS();

    seguirFlama(); 

    // C. Lógica de Navegación (Solo si no estamos apagando Y no hay obstáculo)
    if (estadoActual == BARRIDO) { 
        
        // Nueva condición de seguridad:
        if (distanciaIzquierda > DISTANCIA_SEGURIDAD && distanciaDerecha > DISTANCIA_SEGURIDAD) {
            square(1500, 500, 2500); // Continúa la rutina si es seguro
        } else {
            // ¡Peligro de choque! Detener el robot.
            stop(); 
            
        }

    } else {
        stop(); // Detiene los motores si está en modo APAGANDO
    }
}
