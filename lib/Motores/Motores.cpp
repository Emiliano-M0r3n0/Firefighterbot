//Motores.cpp
#include"Motores.h"
#include<pines.h>
#include<Arduino.h>

// Definimos canales PWM para el ESP32
#define PWM_FREQ 5000      // Frecuencia PWM (Hz)
#define PWM_RESOLUTION 8   // Resolución de 8 bits (0–255)

// Canales (0 a 15 disponibles)
#define CH_M1 4
#define CH_M2 5
#define CH_M3 6
#define CH_M4 7

/**
 * @brief Declara los pines de control de los motores y los configura como salidas pwm asignandoles sus respectivos canales, *Uso recomendado dentro del void setup* 
 */
void iniciarmotores(){
    //Pines de Direccion
    //MOTOR1
    pinMode(MOTOR1_HORARIO,OUTPUT);
    pinMode(MOTOR1_ANTIHORARIO,OUTPUT);
    //MOTOR2
    pinMode(MOTOR2_HORARIO,OUTPUT);
    pinMode(MOTOR2_ANTIHORARIO,OUTPUT);
    //MOTOR3
    pinMode(MOTOR3_HORARIO,OUTPUT);
    pinMode(MOTOR3_ANTIHORARIO,OUTPUT);
    //MOTOR4
    pinMode(MOTOR4_HORARIO,OUTPUT);
    pinMode(MOTOR4_ANTIHORARIO,OUTPUT);

    // Configuración PWM
    ledcSetup(CH_M1, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(CH_M2, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(CH_M3, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(CH_M4, PWM_FREQ, PWM_RESOLUTION);

    // Adjuntar pines PWM a canales
    ledcAttachPin(SPEED_MOTOR1, CH_M1);
    ledcAttachPin(SPEED_MOTOR2, CH_M2);
    ledcAttachPin(SPEED_MOTOR3, CH_M3);
    ledcAttachPin(SPEED_MOTOR4, CH_M4);

}

/**
 * @brief Controla la dirección y velocidad de los 4 motores, usar un valor positivo hace que gire en sentido horario y un valor negativo lo hace girar en sentido antihorario, de ser un valor nulo, el motor se mantiene apagado *Uso recomendado: Para configurar cada funcion de movimiento individual*
 * @param v1 Velocidad Motor 1 (-255 a 255)
 * @param v2 Velocidad Motor 2 (-255 a 255)
 * @param v3 Velocidad Motor 3 (-255 a 255)
 * @param v4 Velocidad Motor 4 (-255 a 255)
 */
void moverMotores(float v1, float v2, float v3, float v4) {
  struct MotorConfig {
    int horario;
    int antihorario;
    int canal;
    int velocidad;
  } motores[4] = {
    {MOTOR1_HORARIO, MOTOR1_ANTIHORARIO, CH_M1, v1},
    {MOTOR2_HORARIO, MOTOR2_ANTIHORARIO, CH_M2, v2},
    {MOTOR3_HORARIO, MOTOR3_ANTIHORARIO, CH_M3, v3},
    {MOTOR4_HORARIO, MOTOR4_ANTIHORARIO, CH_M4, v4}
  };

  for (auto &m : motores) {
    if (m.velocidad > 0) {
      digitalWrite(m.horario, HIGH);
      digitalWrite(m.antihorario, LOW);
    } else if (m.velocidad < 0) {
      digitalWrite(m.horario, LOW);
      digitalWrite(m.antihorario, HIGH);
    } else {
      digitalWrite(m.horario, LOW);
      digitalWrite(m.antihorario, LOW);
    }

    ledcWrite(m.canal, abs(m.velocidad)); // PWM de 0–255
  }
}

//Funciones de movimiento

void movadelante()   { moverMotores(255, 255, 255, 255); }
void movatras()      { moverMotores(-255, -255, -255, -255); }
void movderecha()    { moverMotores(255, -255, -255, 255); }
void movizquierda()  { moverMotores(-255, 255, 255, -255); }
void movnoreste()    { moverMotores(255, 0, 0, 255); }
void movsureste()    { moverMotores(0, -255, -255, 0); }
void movsuroeste()   { moverMotores(-255, 0, 0, -255); }
void movnoroeste()   { moverMotores(0, 255, 255, 0); }
void movgiroizq()    { moverMotores(-255, 255, -255, 255); }
void movgiroder()    { moverMotores(255, -255, 255, -255); }
void movgiroaxeizq() { moverMotores(-255, -255, 255, 255); }
void movgiroaxeder() { moverMotores(255, 255, -255, -255); }

