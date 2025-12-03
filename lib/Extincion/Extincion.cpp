#include "Extincion.h"
#include "Motores.h"
#include <Arduino.h>
#include <pines.h>
#include <ESP32Servo.h>

Servo servopump; //Servo que controla la direccion del agua
Servo servosensor; //Servo que controla la direccion del sensor (Esta en cte movimiento)
int posSensor = 0; //Iniciamos en cero para que no guarde basura (Por si acaso)
const int POS_MIN = 20; //MIN y MAX son los topes que encuentra
const int POS_MAX = 160;
int umbral = 2300; //Apartir de que valor esta detectando flama
int Dirsensor = 1;
unsigned long tInicioApagado = 0;
EstadoExtincion estadoActual = BARRIDO;
DireccionFlama direccionFlama = FLAMA_CENTRO;

// Nuevas variables para control NO BLOQUEANTE
bool flamaEncontrada = false; // Estado para saber si se encontró flama
const long tiempoApagado = 750;  // Duración del chorro de agua
unsigned long tUltimoBarrido = 0; // Tiempo para el retardo de barrido (10ms)
const long intervaloBarrido = 10; // Intervalo para mover el servo sensor

// Variable estática original (la definiremos como global si es necesario que persista fuera de la función)
int lastPos = -1; // Mantenemos la lógica de la posición anterior

void iniciarExtincion() {
    posSensor = 90;
    ESP32PWM::allocateTimer(0); //Configuramos el par de relojes que usaremos para evitar interferencias con el pwm de los motores
    ESP32PWM::allocateTimer(1);
    pinMode(SENSOR_FLAMA,INPUT); //Pin del sensor como entrada
    pinMode(WATER_PUMP,OUTPUT); //Pin de la bomba de agua como salida
    digitalWrite(WATER_PUMP,LOW); //Colocamos la bomba de agua como apagado
    servopump.setPeriodHertz(50);     // Frecuencia estándar de servo
    servopump.attach(SERVO_BOMBA, 500, 2400); //500 y 2400 son la frecuencia a la que trabajan los servos estandar
    servosensor.setPeriodHertz(50);
    servosensor.attach(SERVO_SENSOR, 500, 2400);
    servopump.write(90); //Inicia alineada
    servosensor.write(posSensor);
}

bool leerSensores() {
    int lectura_flama = analogRead(SENSOR_FLAMA); //Lectura del sensor de 0 a 4095
    if(lectura_flama <= umbral) return true; //Es menor que porque los sensores de flama entre mas flama tenga regresan una señal mas baja
    else
    return false;
}

void seguirFlama() {
    bool indicador = leerSensores();
    unsigned long ahora = millis();
    
    // ----------- LÓGICA DE DETECCIÓN Y TRANSICIÓN -----------
    
    // Si la flama se detecta y el sistema NO está disparando
    if (indicador == true && estadoActual != APAGANDO) {
        
        // Determinar dónde está la flama para decirle al robot cómo girar
        if (posSensor < 70) { // Si el sensor está en el lado izquierdo (ej. 20 a 70 grados)
            direccionFlama = FLAMA_IZQUIERDA;
        } else if (posSensor > 110) { // Si el sensor está en el lado derecho (ej. 110 a 160 grados)
            direccionFlama = FLAMA_DERECHA;
        } else { // Si está más o menos centrado (70 a 110 grados)
            direccionFlama = FLAMA_CENTRO;
        }
        
        // Transicionar al nuevo estado CENTRAR si no está ya apagando
        if(estadoActual != APAGANDO) {
            estadoActual = CENTRAR;
        }
        
    }
    
    // ----------- LÓGICA DEL ESTADO APAGANDO (Tiempo de chorro) -----------
    if (estadoActual == APAGANDO) {
        if (ahora - tInicioApagado >= tiempoApagado) {
            
            // 2. **FIN DE APAGADO**
            digitalWrite(WATER_PUMP, LOW);
            estadoActual = BARRIDO; // Regresa al modo barrido
            reiniciarRutinas();
            // NOTA: El servo de la bomba (servopump) ya no se mueve, se queda en 90
            
        } else {
            // Mientras no se cumpla el tiempo, sigue en modo APAGANDO (sin bloqueo)
            return; 
        }
    }
    
    // ----------- LÓGICA DEL ESTADO BARRIDO (Movimiento del Servo) -----------
    // El barrido del servo debe continuar a menos que estemos en APAGANDO
    if (estadoActual == BARRIDO || estadoActual == CENTRAR) {
        
        // El servo se mueve solo si ha pasado el intervalo de 10ms
        if (ahora - tUltimoBarrido >= intervaloBarrido) {
            
            tUltimoBarrido = ahora;
            
            posSensor += Dirsensor * 2;
            
            if (posSensor >= POS_MAX || posSensor <= POS_MIN) {
                Dirsensor = -Dirsensor;
            }

            // Solo mover el servo si la posición cambió
            if (posSensor != lastPos) {
                servosensor.write(posSensor);
                lastPos = posSensor;
            }
        }
    }
}
//-----------------Funciones para Debuggear-----------------//

void zero_servo()
{
    servopump.write(90);
    servosensor.write(90);
}

void barrido()
{
    for (int i = 0; i < 180; i++)
    {
        servosensor.write(i);
        servopump.write(i);
        delay(5);
    }
    
    for (int i = 180; i > 0; i--)
    {
        servosensor.write(i);
        servopump.write(i);
        delay(5);
    }
}