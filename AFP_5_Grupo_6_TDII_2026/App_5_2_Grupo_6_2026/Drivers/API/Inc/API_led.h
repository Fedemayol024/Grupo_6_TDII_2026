/**
 * @file API_led.h
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Driver de abstracción para el manejo genérico de LEDs.
 * @details Este driver permite controlar LEDs de forma independiente de la placa,
 *          facilitando la portabilidad del código al pasar la configuración por referencia.
 * @version 1.0
 * @date 2026
 */

#ifndef API_INC_API_LED_H_
#define API_INC_API_LED_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdbool.h>
#include <stddef.h>

/* Exported types ------------------------------------------------------------*/

/**
 * @brief Enumeración para definir la lógica de polaridad del LED.
 */
typedef enum {
    LED_LOGIC_ACTIVE_HIGH = 0, /**< El LED enciende con nivel alto (SET). */
    LED_LOGIC_ACTIVE_LOW       /**< El LED enciende con nivel bajo (RESET) - Lógica invertida. */
} led_logic_t;

/**
 * @brief Estructura que define un objeto LED mediante sus parámetros de hardware.
 */
typedef struct {
    GPIO_TypeDef* port;     /**< Puntero al puerto GPIO (Ej: GPIOF). */
    uint16_t pin;           /**< Número del pin GPIO (Ej: GPIO_PIN_13). */
    led_logic_t logic;      /**< Define si el LED es de lógica activa alta o baja. */
} led_t;

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief Enciende el LED referenciado.
 * @param led Puntero a la estructura led_t.
 * @return void
 */
void LED_On(led_t * led);

/**
 * @brief Apaga el LED referenciado.
 * @param led Puntero a la estructura led_t.
 * @return void
 */
void LED_Off(led_t * led);

/**
 * @brief Conmuta el estado físico del LED.
 * @param led Puntero a la estructura led_t.
 * @return void
 */
void LED_Toggle(led_t * led);

/**
 * @brief Enciende todos los LEDs del grupo.
 * @param ledGroup Arreglo de estructuras led_t.
 * @param size Cantidad de LEDs en el arreglo.
 */
void LED_All_On(led_t ledGroup[], uint8_t size);

/**
 * @brief Apaga todos los LEDs del grupo.
 * @param ledGroup Arreglo de estructuras led_t.
 * @param size Cantidad de LEDs en el arreglo.
 */
void LED_All_Off(led_t ledGroup[], uint8_t size);

/**
 * @brief Conmuta el estado de todos los LEDs del grupo.
 * @param ledGroup Arreglo de estructuras led_t.
 * @param size Cantidad de LEDs en el arreglo.
 */
void LED_ToggleAll(led_t ledGroup[], uint8_t size);

#endif /* API_INC_API_LED_H_ */
