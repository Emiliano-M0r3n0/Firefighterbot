#include "Extincion.h"
#include <Arduino.h>
#include <pines.h>

Servo servopump; //Servo que controla la direccion del agua
Servo servosensor; //Servo que controla la direccion del sensor (Esta en cte movimiento)
int posSensor = 0; //Iniciamos en cero para que no guarde basura (Por si acaso)
const int POS_MIN = 20; //MIN y MAX son los topes que encuentra
const int POS_MAX = 160;
int umbral = 2300; //Apartir de que valor esta detectando flama
int Dirsensor = 1;

void iniciarExtincion() {
    posSensor = 90;
    pinMode(SENSOR_FLAMA,INPUT); //Pin del sensor como entrada
    pinMode(WATER_PUMP,OUTPUT); //Pin de la bomba de agua como salida
    digitalWrite(WATER_PUMP,LOW); //Colocamos la bomba de agua como 
    servopump.attach(SERVO_BOMBA);
    servosensor.attach(SERVO_SENSOR);
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
    if(indicador == true)
    {
        servopump.write(posSensor);
        digitalWrite(WATER_PUMP,HIGH);
        delay(1500);
    }
    else if(indicador == false)
    {   
        digitalWrite(WATER_PUMP,LOW);

        servosensor.write(posSensor);
        delay(10); //Cambia la velocidad del servo

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