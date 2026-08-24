/**
 * @file driver_led_pal.h
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Capa PAL para STM32 con soporte de asignación dinámica de periféricos.
 * @details Mapea los llamados lógicos del driver con los registros HAL de ST.
 * @version 1.0
 * @date 2026
 */

#ifndef DRIVER_LED_PAL_H_
#define DRIVER_LED_PAL_H_

#include "main.h"
#include "stdbool.h"
/**
 * @brief Estructura de hardware física para STM32.
 */
typedef struct {
    GPIO_TypeDef* port;   ///< Puerto GPIO de la MCU (GPIOA, GPIOB, etc.)
    uint16_t pin;         ///< Pin de la MCU (GPIO_PIN_X)
} LED_Hardware_t;

/**
 * @brief Vincula la PAL con la tabla de hardware activa.
 */
void LED_PAL_Init(const LED_Hardware_t* tabla, uint8_t cantidad);

/**
 * @brief Ejecuta la escritura física sobre el silicio de ST.
 */
void LED_PAL_Write(uint8_t indice, bool estado);

/**
 * @brief Ejecuta el toggle físico sobre el silicio de ST.
 */
void LED_PAL_Toggle(uint8_t indice);

#endif /* DRIVER_LED_PAL_H_ */
