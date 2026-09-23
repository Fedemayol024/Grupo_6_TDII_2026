/**
 * @file driver_led.h
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Interfaz genérica y dinámica para el control de N-LEDs.
 * @details Permite registrar un arreglo de LEDs en tiempo de ejecución,
 * independizando al driver de la cantidad y ubicación física de los actuadores.
 * @version 1.0
 * @date 2026
 */

#ifndef DRIVER_LED_H_
#define DRIVER_LED_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Inicializa el driver de LEDs asociándolo a una plataforma y cantidad específica.
 * @param led_table Puntero opaco a la tabla de configuración de la PAL.
 * @param led_count Cantidad total de LEDs a administrar.
 */
void LED_Init(const void* tabla_leds, uint8_t cantidad_leds);

/**
 * @brief Modifica el estado de un LED por su índice.
 * @param led_index Índice del LED (0 hasta led_count - 1).
 * @param state true para encender, false para apagar.
 */
void LED_Write(uint8_t indice_led, bool estado);

/**
 * @brief Alterna el estado de un LED por su índice.
 * @param led_index Índice del LED (0 hasta led_count - 1).
 */
void LED_Toggle(uint8_t indice_led);

/**
 * @brief Obtiene la cantidad de LEDs registrados en el sistema.
 * @return uint8_t Cantidad de LEDs.
 */
uint8_t LED_GetCount(void);

#endif /* DRIVER_LED_H_ */
