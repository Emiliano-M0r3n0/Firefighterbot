//Pines.h
/**
 * @brief Define los pines del esp32 que se utilizan en el proyecto y la funcion de cada uno
 * 
 */

#ifndef PINES_H
#define PINES_H

//---------------MOTOR 1------------------------

#define MOTOR1_HORARIO 26
#define MOTOR1_ANTIHORARIO 14 
#define SPEED_MOTOR1 13

//-------------MOTOR 2--------------------------

#define MOTOR2_HORARIO 15
#define MOTOR2_ANTIHORARIO 16 
#define SPEED_MOTOR2 4

//-------------MOTOR 3------------------------

#define MOTOR3_HORARIO 32 
#define MOTOR3_ANTIHORARIO 33 
#define SPEED_MOTOR3 25

//-------------------MOTOR 4--------------------

#define MOTOR4_HORARIO 23
#define MOTOR4_ANTIHORARIO 22 
#define SPEED_MOTOR4 21 

//--------------------SERVOMOTORES------------

#define SERVO_BOMBA 5
#define SERVO_SENSOR 19

//-------------------ACTUADORES------------------

#define WATER_PUMP 17
#define BUZZER 12

//------------------SENSORES------------------------

#define SENSOR_FLAMA 39 //PIN VN
#define ECHO_ONE 34
#define TRIG_ONE 18
#define ECHO_TWO 36 //PIN VP
#define TRIG_TWO 27

#endif