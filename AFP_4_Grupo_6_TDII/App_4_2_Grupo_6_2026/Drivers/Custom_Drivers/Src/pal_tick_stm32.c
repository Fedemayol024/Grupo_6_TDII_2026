/**
 * @file pal_tick_stm32.c
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Implementación de la PAL de base de tiempo para STM32F439ZI.
 * @details Conecta la interfaz pal_tick_get() con la función HAL_GetTick()
 *          provista por la biblioteca HAL de ST para microcontroladores STM32F4.
 * @version 1.0
 * @date 2026
 */

/*==================[Inclusiones]============================================*/
#include "pal_tick_stm32.h"
#include "stm32f4xx_hal.h"

/*==================[Implementación de funciones públicas]====================*/

/**
 * @brief Lee el contador de ticks del SysTick en microcontroladores STM32F4.
 * @details Retorna el valor de la variable uwTick provista por la HAL de ST,
 *          la cual se incrementa periódicamente a través de la interrupción del SysTick.
 * @return tick_t Marca de tiempo actual en milisegundos.
 */
tick_t pal_tick_get(void)
{
    /* Retorna el tick de la HAL casteado explícitamente al tipo tick_t */
    return (tick_t)HAL_GetTick();
}
