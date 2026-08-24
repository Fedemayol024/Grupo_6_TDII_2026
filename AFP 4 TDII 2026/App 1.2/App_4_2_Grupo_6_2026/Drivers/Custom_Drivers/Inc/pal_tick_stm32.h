/**
 * @file pal_tick_stm32.h
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Interfaz de la capa PAL de base de tiempo para STM32F439ZI.
 * @details Provee la definición del tipo de dato tick_t y el prototipo de función
 *          para la obtención de marcas de tiempo en milisegundos en plataformas STM32.
 * @version 1.0
 * @date 2026
 */

#ifndef INC_PAL_TICK_STM32_H_
#define INC_PAL_TICK_STM32_H_

/*==================[Inclusiones]============================================*/
#include <stdint.h>

/*==================[Tipos de datos definidos por el usuario]================*/

/**
 * @brief Tipo de dato estándar para el conteo de tiempo del sistema.
 * @details Entero sin signo de 32 bits que representa milisegundos transcurridos.
 */
typedef uint32_t tick_t;

/*==================[Declaración de funciones públicas]======================*/

/**
 * @brief Obtiene el valor actual del contador de tiempo del sistema en milisegundos.
 * @return tick_t Conteo de tiempo transcurrido en milisegundos desde el inicio del micro.
 */
tick_t pal_tick_get(void);

#endif /* INC_PAL_TICK_STM32_H_ */
