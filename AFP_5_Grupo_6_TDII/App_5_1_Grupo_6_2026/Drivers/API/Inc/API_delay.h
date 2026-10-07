/*
 * API_delay.h
 *
 *  Created on: Oct 6, 2026
 *      Author: santi
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_
#include "stm32f4xx_hal.h"


#include <stdint.h>    // para uint32_t
#include <stdbool.h>   // para bool

typedef uint32_t tick_t;   // tiempo en milisegundos
typedef bool bool_t;       // verdadero o falso

typedef struct {
    tick_t startTime;      // cuando arranco a contar
    tick_t duration;       // cuanto tiene que durar
    bool_t running;        // si esta contando o no
} delay_t;
void delayInit(delay_t * delay, tick_t duration);    // carga la duracion, no arranca
bool_t delayRead(delay_t * delay);                   // true cuando se cumplio el tiempo
void delayWrite(delay_t * delay, tick_t duration);   // cambia la duracion

#endif /* API_INC_API_DELAY_H_ */
