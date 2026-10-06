/**
 * @file    API_delay.c
 * @author  Mayol Federico (UTN FRT) - Grupo 6
 * @brief   Driver de retardos no bloqueantes basado en el SysTick.
 * @version 1.0
 * @date    2026
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_delay.h"

/* Function definition -------------------------------------------------------*/

/**
 * @brief  Carga la duracion del retardo. No inicia el conteo.
 * @param  delay: retardo a inicializar.
 * @param  duration: duracion en ms.
 * @retval None
 */
void delayInit(delay_t * delay, tick_t duration)
{
	delay->duration = duration;
	delay->running = false;
}

/**
 * @brief  Consulta el retardo. La primera llamada toma la marca de tiempo;
 *         las siguientes verifican si ya transcurrio la duracion.
 * @param  delay: retardo a consultar.
 * @retval true si el tiempo se cumplio, false en caso contrario.
 */
bool_t delayRead(delay_t * delay)
{
	bool_t timeReached = false;

	if (!delay->running)
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else if ((HAL_GetTick() - delay->startTime) >= delay->duration)
	{
		delay->running = false;
		timeReached = true;
	}

	return timeReached;
}

/**
 * @brief  Cambia la duracion de un retardo existente.
 * @param  delay: retardo a modificar.
 * @param  duration: nueva duracion en ms.
 * @retval None
 */
void delayWrite(delay_t * delay, tick_t duration)
{
	delay->duration = duration;
}
