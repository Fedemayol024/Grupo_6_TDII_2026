/**
 * @file    API_delay.h
 * @author  Mayol Federico (UTN FRT) - Grupo 6
 * @brief   Driver de retardos no bloqueantes basado en el SysTick.
 * @version 1.0
 * @date    2026
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
typedef uint32_t tick_t;   /* Marca de tiempo o duracion, en ms */
typedef bool bool_t;       /* Booleano del grupo */

typedef struct {
	tick_t startTime;      /* Marca de tiempo en la que empezo a contar */
	tick_t duration;       /* Duracion del retardo, en ms */
	bool_t running;        /* true mientras el retardo esta contando */
} delay_t;

/* Exported functions prototypes ---------------------------------------------*/
void delayInit(delay_t * delay, tick_t duration);
bool_t delayRead(delay_t * delay);
void delayWrite(delay_t * delay, tick_t duration);

#endif /* API_INC_API_DELAY_H_ */
