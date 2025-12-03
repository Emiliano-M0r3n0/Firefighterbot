//Motores.cpp
#include"Motores.h"
#include"Extincion.h"
#include<pines.h>
#include<Arduino.h>

// Variables de estado_square de la rutina square (DEFINICIÓN CORREGIDA)
int secuencia_general_square = 0; // ¡Corregido!
int estado_square = 0;            // ¡Corregido!
unsigned long tInicio_square = 0; // ¡Corregido!

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

//--------------------Funciones de movimiento----------------------------
void movadelante()   { moverMotores(255, 255, 255, 255); }
void movatras()      { moverMotores(-255, -255, -255, -255); }

// Movimientos laterales
void movderecha()    { moverMotores(-255, 255, 255, -255); }
void movizquierda()  { moverMotores(255, -255, -255, 255); }

// Diagonales
void movnoreste()    { moverMotores(0, 255, 255, 0); }
void movsureste()    { moverMotores(-255, 0, 0, -255); }
void movsuroeste()   { moverMotores(0, -255, -255, 0); }
void movnoroeste()   { moverMotores(255, 0, 0, 255); }

// Rotaciones sobre eje
void movgiroder()    { moverMotores(255, -255, 255, -255); }
void movgiroizq()    { moverMotores(-255, 255, -255, 255); }

// Giros diagonales opcionales (no estándar)
void movgiroaxeizq() { moverMotores(-255, -255, 255, 255); }
void movgiroaxeder() { moverMotores(255, 255, -255, -255); }

// Parada total
void stop()          { moverMotores(0,0,0,0); }

//Movimiento conjunto
bool ejecutarSecuencia(MovimientoFunc mover,
                       unsigned long timeMov,
                       unsigned long timePause,
                       unsigned long timelens,
                       int &estado_square,
                       unsigned long &tInicio_square)
{
    unsigned long ahora = millis();

    switch (estado_square) {

        case 0:
            mover();
            tInicio_square = ahora;
            estado_square = 1;
            break;

        case 1:
            if (ahora - tInicio_square >= timeMov) {
                stop();
                tInicio_square = ahora;
                estado_square = 2;
            }
            break;

        case 2:
            if (ahora - tInicio_square >= timePause) {
                tInicio_square = ahora;
                estado_square = 3;
            }
            break;

        case 3:

            if (ahora - tInicio_square >= timelens) {
                estado_square = 4;
            }
            break;

        case 4:
            estado_square = 0;
            return true;
    }

    return false;
}

//-----------------------Rutinas-------------------------------

void square(int timemov,int timepause,int timelens)
{

    switch (secuencia_general_square)
    {
        case 0:
            if (ejecutarSecuencia(movadelante, timemov, timepause, timelens, 
                                  estado_square,tInicio_square))
                secuencia_general_square++;
            break;

        case 1:
            if (ejecutarSecuencia(movgiroder, timemov, timepause, timelens,
                                  estado_square,tInicio_square))
                secuencia_general_square++;
            break;

        case 2:
            if (ejecutarSecuencia(movderecha, timemov, timepause, timelens,
                                  estado_square,tInicio_square))
                secuencia_general_square++;
            break;

        case 3:
            if (ejecutarSecuencia(movgiroder, timemov, timepause, timelens,
                                  estado_square,tInicio_square))
                secuencia_general_square++; // repetir indefinido
            break;
        case 4:
            if (ejecutarSecuencia(movatras, timemov, timepause, timelens, 
                                  estado_square,tInicio_square))
                secuencia_general_square++;
            break;

        case 5:
            if (ejecutarSecuencia(movgiroder, timemov, timepause, timelens,
                                  estado_square,tInicio_square))
                secuencia_general_square++;
            break;

        case 6:
            if (ejecutarSecuencia(movizquierda, timemov, timepause, timelens,
                                  estado_square,tInicio_square))
                secuencia_general_square++;
            break;

        case 7:
            if (ejecutarSecuencia(movgiroder, timemov, timepause, timelens,
                                  estado_square,tInicio_square))
                secuencia_general_square = 0; // repetir indefinido
            break;
    }
}

void hexagonedge(int timemov,int timepause,int timelens)
{
    switch(secuencia_general_square)
    {
    case 0:  // Noroeste
        if (ejecutarSecuencia(movnoroeste, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;

    case 1:  // Giro
        if (ejecutarSecuencia(movgiroder, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;



    case 2:  // Adelante
        if (ejecutarSecuencia(movadelante, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;

    case 3:  // Giro
        if (ejecutarSecuencia(movgiroder, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;



    case 4:  // Noreste
        if (ejecutarSecuencia(movnoreste, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;

    case 5:  // Giro
        if (ejecutarSecuencia(movgiroder, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;



    case 6:  // Derecha
        if (ejecutarSecuencia(movderecha, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;

    case 7:  // Giro
        if (ejecutarSecuencia(movgiroder, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;



    case 8:  // Sureste
        if (ejecutarSecuencia(movsureste, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;

    case 9:  // Giro
        if (ejecutarSecuencia(movgiroder, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;



    case 10: // Atrás
        if (ejecutarSecuencia(movatras, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;

    case 11: // Giro
        if (ejecutarSecuencia(movgiroder, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;



    case 12: // Suroeste
        if (ejecutarSecuencia(movsuroeste, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square++;
        break;

    case 13: // Giro final
        if (ejecutarSecuencia(movgiroder, timemov, timepause, timelens,
                              estado_square, tInicio_square))
            secuencia_general_square = 0; // Reiniciar hexágono
        break;
    }
}

void reiniciarRutinas() {
    secuencia_general_square = 0;
    estado_square = 0;
    tInicio_square = 0;
}
