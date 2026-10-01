/***********************************
 * API_GPIO.h
 *
 *  Created on: Aug 20, 2026
 *      Author: emalu
 *      Function Driver: Retardo No Bloqueante
 *
 **********************************/

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/*Includes*************/
#include <stdint.h>
#include <stdbool.h>

/*Exproted types********************/
typedef uint32_t tick_t;
typedef bool bool_t;
typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
}delay_t;
/*Exported function prototypes********/
void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);
#endif /* API_INC_API_GPIO_H_ */
