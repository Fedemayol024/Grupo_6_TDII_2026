/*
 * header.h
 *
 * Driver de retardos no bloqueantes (basado en SysTick / HAL_GetTick)
 * AFP 4 - Tecnicas Digitales II - Grupo 6 - 2025
 */

#ifndef API_INC_HEADER_H_
#define API_INC_HEADER_H_

#include <stdint.h>   // para tener uint32_t
#include <stdbool.h>  // para tener bool

// tipos de datos propios del driver (los pide la consigna)
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct {
	tick_t startTime;   // marca de tiempo en la que arranco a contar
	tick_t duration;     // cuanto tiene que durar el retardo (en ms)
	bool_t running;      // si esta contando o no
} delay_t;

// funciones publicas del driver
void delayInit(delay_t * delay, tick_t duration);
bool_t delayRead(delay_t * delay);
void delayWrite(delay_t * delay, tick_t duration);

#endif /* API_INC_HEADER_H_ */
