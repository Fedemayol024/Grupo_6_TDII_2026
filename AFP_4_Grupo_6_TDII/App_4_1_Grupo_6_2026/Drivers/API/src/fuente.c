/*
 * fuente.c
 *
 * Implementacion del driver de retardos no bloqueantes.
 * Usa HAL_GetTick() como base de tiempo (el SysTick incrementa esta
 * cuenta 1 vez por milisegundo).
 *
 * AFP 4 - Tecnicas Digitales II - Grupo 6 - 2025
 */

#include "header.h"
#include "stm32f4xx_hal.h"   // para poder usar HAL_GetTick()

/*
 * delayInit: carga la duracion pedida y deja el delay "apagado".
 * OJO que esto NO arranca a contar todavia, eso lo hace delayRead.
 */
void delayInit(delay_t * delay, tick_t duration)
{
	delay->duration = duration;
	delay->running = false;
}

/*
 * delayRead: hay que llamarla todo el tiempo desde el while(1).
 * - si el delay no estaba corriendo, lo arranca (toma tiempo actual) y
 *   devuelve false (todavia no paso nada).
 * - si ya estaba corriendo, se fija si ya paso el tiempo pedido. Si paso,
 *   apaga el running y devuelve true. Si no paso, devuelve false.
 */
bool_t delayRead(delay_t * delay)
{
	if (delay->running == false)
	{
		delay->running = true;
		delay->startTime = HAL_GetTick();
		return false;
	}

	if ((HAL_GetTick() - delay->startTime) >= delay->duration)
	{
		delay->running = false;
		return true;
	}

	return false;
}

/*
 * delayWrite: sirve para cambiar el tiempo de un delay ya creado
 * (por ej para pasar de 200ms de ON a 200ms de OFF en la misma variable)
 */
void delayWrite(delay_t * delay, tick_t duration)
{
	delay->duration = duration;
}
