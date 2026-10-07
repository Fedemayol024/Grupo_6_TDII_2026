/**
 * @file    API_debounce.h
 * @author  Grupo 6 (UTN FRT)
 * @brief   Driver antirrebote para el pulsador, con MEF de 4 estados.
 * @version 1.0
 * @date    2026
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

/* Includes ------------------------------------------------------------------*/
#include "API_delay.h"   /* bool_t, delay_t */

/* Exported types ------------------------------------------------------------*/
typedef enum {
	BUTTON_UP,        /* Pulsador liberado */
	BUTTON_FALLING,   /* Se detecto una pulsacion, falta confirmarla */
	BUTTON_DOWN,      /* Pulsador presionado */
	BUTTON_RISING     /* Se detecto una liberacion, falta confirmarla */
} debounceState_t;

/* Exported functions prototypes ---------------------------------------------*/
void debounceFSM_init(void);
void debounceFSM_update(bool_t buttonRead);
void buttonPressed(void);
void buttonReleased(void);
bool_t readKey(void);

#endif /* API_INC_API_DEBOUNCE_H_ */
