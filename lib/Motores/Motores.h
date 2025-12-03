//Motores.h
/**
 * Declara todas las funciones relacionadas con las ruedas mecanum, esto es un include guard
 * de tal forma que evita que se declaren mas de una vez las funciones, generando problemas
 * 
 */
#ifndef MOTORES_H

#define MOTORES_H
typedef void (*MovimientoFunc)();

// Variables de estado para la rutina de búsqueda
extern int secuencia_general_square;
extern int estado_square;
extern unsigned long tInicio_square;
/// @brief Hace una declaración de todos los pines adjuntados a los motores como salidas, asi como los canales PWM
void iniciarmotores();
/// @brief Enciende los motores en orden para avanzar hacia adelante
void movadelante(); 
/// @brief Enciende los motores en orden para avanzar hacia atras
void movatras();
/// @brief Enciende los motores en orden para moverse lateralmente a la derecha
void movderecha();
/// @brief Enciende los motores en orden para moverse lateralmente a la izquierda
void movizquierda();
/// @brief Enciende los motores en orden para moverse al noreste
void movnoreste();
/// @brief Enciende los motores en orden para moverse al sureste
void movsureste();
/// @brief Enciende los motores en orden para moverse al suroeste
void movsuroeste();
/// @brief Enciende los motores en orden para moverse al noreste
void movnoroeste();
/// @brief Enciende los motores para girar a la izquierda
void movgiroizq();
/// @brief Enciende los motores para girar a la derecha 
void movgiroder();
/// @brief Enciende los motores para girar sobre su eje a la izquierda 
void movgiroaxeizq();
/// @brief Enciende los motores para girar sobre su eje a la drecha
void movgiroaxeder();
/// @brief Detiene todos los motores
void stop();

void moverMotores(float v1, float v2, float v3, float v4);

void reiniciarRutinas();

bool ejecutarSecuencia(MovimientoFunc mover,
                       unsigned long timeMov,
                       unsigned long timePause,
                       unsigned long timeBarrido,
                       int &estado,
                       unsigned long &tInicio);

//Rutinas
/// @brief Realiza una rutina en forma de cuadrado
/// @param timemov Tiempo que dura el movimiento 
/// @param timepause Pausa entre movimientos
/// @param timelens Tiempo que hace la lectura de la flama
void square(int timemov,int timepause,int timelens);

//Rutinas
/// @brief Realiza una rutina en forma de hexagono
/// @param timemov Tiempo que dura el movimiento 
/// @param timepause Pausa entre movimientos
/// @param timelens Tiempo que hace la lectura de la flama
void hexagonedge(int timemov,int timepause,int timelens);

// Variables de estado para la rutina de búsqueda (DECLARACIÓN CORRECTA)
extern int secuencia_general_square;
extern int estado_square;
extern unsigned long tInicio_square;
void reiniciarRutinas();
#endif