#include "Extincion.h"
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
    static int lastPos = -1;
    if(indicador == true)
    {
        servopump.write(posSensor);
        digitalWrite(WATER_PUMP,HIGH);
        delay(750);
    }
    else
    {   
        digitalWrite(WATER_PUMP,LOW);

        if (posSensor != lastPos) {   // Solo mover si cambió
            servosensor.write(posSensor);
            lastPos = posSensor;
        }
        delay(10);
        posSensor += Dirsensor *2;

        if(posSensor >= POS_MAX || posSensor <= POS_MIN)
        {
            Dirsensor = -Dirsensor;
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