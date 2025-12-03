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
    seguirFlama(); // Esto actualiza el estadoActual y direccionFlama

    // A. Lógica para CENTRAR EL FUEGO
    if (estadoActual == CENTRAR) {
        stop(); // Detenemos la búsqueda/movimiento

        if (direccionFlama == FLAMA_IZQUIERDA) {
            movgiroizq(); // Giro en el eje hacia la izquierda
        } else if (direccionFlama == FLAMA_DERECHA) {
            movgiroder(); // Giro en el eje hacia la derecha
        } else { // FLAMA_CENTRO
            // Flama Centrada: Pasamos al estado de APAGADO
            stop(); 
            digitalWrite(WATER_PUMP, HIGH); // Encender bomba
            digitalWrite(BUZZER, HIGH);
            
            tInicioApagado = millis(); // <-- ¡ESTA LÍNEA AHORA FUNCIONARÁ!
            
            estadoActual = APAGANDO;
        }
    }

    // B. Lógica de BÚSQUEDA (El robot se mueve solo si está en BARRIDO)
    else if (estadoActual == BARRIDO) { 
        
        // Condición de seguridad (Obstáculos)
        if (distanciaIzquierda > DISTANCIA_SEGURIDAD && distanciaDerecha > DISTANCIA_SEGURIDAD) {
            square(1500, 500, 2500); // Rutina de búsqueda
        } else {
            // ¡Peligro de choque! Detener el robot.
            stop(); 
        }

    } 
    
    // C. Lógica de APAGADO (Solo espera a que pase el tiempo)
    else if (estadoActual == APAGANDO) {
        stop(); // Asegúrate de que el robot esté completamente quieto mientras dispara
        // La lógica del temporizador para apagar la bomba está dentro de seguirFlama()
    }
}