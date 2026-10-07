/**
 * @file    API_debounce.c
 * @author  Mayol Federico (UTN FRT) - Grupo 6
 * @brief   Driver antirrebote para el pulsador, con MEF de 4 estados.
 * @details Basado en el API_debounce.c de la catedra. Cada cambio del
 *          pulsador se confirma con una segunda lectura DEBOUNCE_DELAY ms
 *          despues, usando un retardo no bloqueante.
 * @version 1.0
 * @date    2026
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_debounce.h"
#include "API_delay.h"

/* Defines -------------------------------------------------------------------*/
#define DEBOUNCE_DELAY 40   /* Tiempo de verificacion, en ms */

/* Declaration of variables --------------------------------------------------*/
static debounceState_t actualState;   /* Estado actual de la MEF */
static bool_t keyPressed = false;     /* true mientras el pulsador esta presionado */
static bool_t fallingEdge = false;    /* true si hubo una pulsacion nueva sin leer */
static delay_t debounceDelay;         /* Retardo de DEBOUNCE_DELAY ms */

/* Function definition -------------------------------------------------------*/

/**
 * @brief  Carga el estado inicial de la MEF.
 * @param  None
 * @retval None
 */
void debounceFSM_init(void)
{
	actualState = BUTTON_UP;
	keyPressed = false;
	fallingEdge = false;
	delayInit(&debounceDelay, DEBOUNCE_DELAY);
}

/**
 * @brief  Actualiza la MEF. Debe llamarse en cada vuelta del lazo principal.
 * @param  buttonRead: lectura actual del pulsador (true = presionado).
 * @retval None
 */
void debounceFSM_update(bool_t buttonRead)
{
	switch (actualState)
	{
	case BUTTON_UP:
		if (buttonRead)
		{
			actualState = BUTTON_FALLING;
			delayRead(&debounceDelay);   /* Arranca la cuenta de DEBOUNCE_DELAY */
		}
		break;

	case BUTTON_FALLING:
		if (delayRead(&debounceDelay))
		{
			if (buttonRead)
			{
				keyPressed = true;
				fallingEdge = true;
				actualState = BUTTON_DOWN;
				buttonPressed();
			}
			else
			{
				actualState = BUTTON_UP;   /* Era un rebote */
			}
		}
		break;

	case BUTTON_DOWN:
		if (!buttonRead)
		{
			actualState = BUTTON_RISING;
			delayRead(&debounceDelay);   /* Arranca la cuenta de DEBOUNCE_DELAY */
		}
		break;

	case BUTTON_RISING:
		if (delayRead(&debounceDelay))
		{
			if (!buttonRead)
			{
				keyPressed = false;
				actualState = BUTTON_UP;
				buttonReleased();
			}
			else
			{
				actualState = BUTTON_DOWN;   /* Era un rebote */
			}
		}
		break;

	default:
		debounceFSM_init();   /* Estado invalido: se reinicia la MEF */
		break;
	}
}

/**
 * @brief  Evento que se dispara al confirmarse una pulsacion.
 * @note   En la prueba del driver (punto a de la consigna) invierte el LED1.
 *         En la App 5.3 queda vacia porque los LEDs los maneja la secuencia.
 * @param  None
 * @retval None
 */
void buttonPressed(void)
{
	/* toggleLed_GPIO(LD1_Pin); */
}

/**
 * @brief  Evento que se dispara al confirmarse una liberacion.
 * @note   En la prueba del driver (punto a de la consigna) invierte el LED3.
 *         En la App 5.3 queda vacia porque los LEDs los maneja la secuencia.
 * @param  None
 * @retval None
 */
void buttonReleased(void)
{
	/* toggleLed_GPIO(LD3_Pin); */
}

/**
 * @brief  Informa si hubo una pulsacion nueva y reinicia el aviso al leerlo.
 * @param  None
 * @retval true una sola vez por cada pulsacion confirmada.
 */
bool_t readKey(void)
{
	bool_t keyPress = false;

	if (fallingEdge)
	{
		keyPress = true;
		fallingEdge = false;
	}

	return keyPress;
}
