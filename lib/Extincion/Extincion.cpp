#include "Extincion.h"
#include <Arduino.h>
#include <pines.h>

double contador = 0;
double sumatoria = 0;
double promedio = 0;
Servo servoExtincion;
int posicionServo = 90;

void iniciarExtincion() {
    servoExtincion.attach(SERVO_PIN);
    servoExtincion.write(posicionServo); // Posición de reposo

    pinMode(WATER_PUMP, OUTPUT);
    pinMode(SENSOR_FLAMAIZQ, INPUT);
    pinMode(SENSOR_FLAMADER, INPUT);
}

int leerSensores() {
    int activacion;
    int flamaIzq = analogRead(SENSOR_FLAMAIZQ);
    int flamaDer = analogRead(SENSOR_FLAMADER);
    Serial.print("Sensor izquierdo:");
    Serial.println(flamaIzq);
    Serial.print("Sensor derecho:");
    Serial.println(flamaDer);
    if (flamaIzq <= 1300 || flamaDer <= 2300) { 
        Serial.println("¡Flama detectada! Iniciando extinción...");
        activacion = 1;
    }
    else
    {
        activacion = 0;
    }
    return (activacion);
    delay(50); // para no saturar el monitor
}

void seguirFlama() {
    int flamaIzq = analogRead(SENSOR_FLAMAIZQ);
    int flamaDer = analogRead(SENSOR_FLAMADER);

    // Mientras más pequeño el valor, más fuerte la flama
    float diferencia = (float)flamaIzq - (float)flamaDer;

    Serial.print("\tDiferencia: ");
    Serial.println(diferencia);

    // Umbral de sensibilidad
    int umbral = 200;

    /*sumatoria += diferencia;
    contador += 1;
    promedio += (sumatoria/contador);

    Serial.print("\tFactor");
    Serial.println(promedio);*/
    // Limitar el movimiento entre 0° y 180°
    //posicionServo = constrain(posicionServo, 0, 180);



    // Flama más intensa a la derecha
    if (flamaDer > flamaIzq) {
        //Se mueve inicialmente hacia 45 grados para hacer una barrido de 45 a 0, luego regresa a 45 y hace otro barrido de 45 a 90
        servoExtincion.write(45);
        for (int i = 45; i > 0; i--)
        {
            servoExtincion.write(i);
            delay(5);
        }
        servoExtincion.write(45);
        for (int i = 45; i < 91; i++)
        {
            servoExtincion.write(i);
            delay(5);
        }
    }
    //Flama mas intensa a la izquierda
    else {
        //Se mueve inicialmente hacia 135 grados para hacer un barrido de 135 a 180, luego regresa a 135 y hace otro barrido de 135 a 90
        servoExtincion.write(135);
        for(int i = 135; i < 181; i++)
        {
            servoExtincion.write(i);
            delay(5);
        }
        servoExtincion.write(135);
        for (int i = 135; i > 89; i--)
        {
            servoExtincion.write(i);
            delay(5);
        }
    } 



    delay(5);
}
