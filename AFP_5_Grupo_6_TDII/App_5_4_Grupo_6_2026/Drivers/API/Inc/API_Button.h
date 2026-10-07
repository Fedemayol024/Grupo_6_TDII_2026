/*
 * Driver_Button.h
 *
 *  Created on: Sep 29, 2026
 *      Author: emalu
 */

#ifndef API_INC_API_BUTTON_H_
#define API_INC_API_BUTTON_H_


/*Includes*************/
#include <stdint.h>
#include <stdbool.h>
#include "API_GPIO.h"
#include "API_Delay.h"

/*Exproted types********************/
typedef uint32_t state_t, tick_t;
typedef bool bool_t;
typedef struct {
	tick_t startTime;
	tick_t duration;
	state_t state;
	bool_t press;
}button_t;
/*Exported function prototypes********/
void PressButton(button_t *states_t);
void init_Time_Button_t(button_t *states_t);
void caseInactivo(button_t *states_t);
void caseActivo_Espera(button_t *states_t);
void caseActivo(button_t *states_t);
void caseInactivo_Espera(button_t *states_t);


#endif /* API_INC_API_BUTTON_H_ */
