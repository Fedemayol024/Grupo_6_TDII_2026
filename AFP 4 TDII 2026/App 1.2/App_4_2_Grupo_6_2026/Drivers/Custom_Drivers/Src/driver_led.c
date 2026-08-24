/**
 * @file driver_led.c
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Implementación del driver genérico de manipulación de LEDs.
 * @details Contiene la lógica de control del componente, delegando la ejecución
 * física del hardware a la capa PAL a través de punteros opacos.
 * @version 2.0
 * @date 2026
 */

#include "driver_led.h"
#include "driver_led_pal.h"
#include <stddef.h>

/**
 * @brief Variable privada para el control genérico de la cantidad de instancias.
 * @details Se declara como 'static' para limitar su alcance exclusivamente a este archivo,
 * garantizando el principio de encapsulamiento.
 */
static uint8_t leds_registrados = 0;

/**
 * @brief Inicializa el driver de LEDs asociándolo a una plataforma y cantidad específica.
 * @param tabla_leds Puntero opaco (void*) a la tabla de configuración física de la PAL.
 * @param cantidad_leds Cantidad total de LEDs que se van a administrar.
 */
void LED_Init(const void* tabla_leds, uint8_t cantidad_leds) {
    /* Barrera de robustez inicial: evitar tablas inexistentes o conteos nulos */
    if (tabla_leds != NULL && cantidad_leds > 0) {
        leds_registrados = cantidad_leds;

        /** * @note Desacoplamiento por Puntero Opaco:
         * Se realiza un "cast" seguro del puntero genérico 'void*' al tipo estructural
         * concreto requerido por la PAL de la plataforma actual ('LED_Hardware_t*').
         */
        LED_PAL_Init((const LED_Hardware_t*)tabla_leds, cantidad_leds);
    }
}

/**
 * @brief Modifica el estado de un LED por su índice.
 * @param indice_led Índice del LED dentro del arreglo registrado (0 hasta cantidad - 1).
 * @param estado true para encender (SET), false para apagar (RESET).
 */
void LED_Write(uint8_t indice_led, bool estado) {
    /* Primera barrera de robustez perimetral en la capa genérica */
    if (indice_led < leds_registrados) {
        /* Delega la conmutación eléctrica a la capa de abstracción de plataforma */
        LED_PAL_Write(indice_led, estado);
    }
}

/**
 * @brief Alterna el estado de un LED por su índice.
 * @param indice_led Índice del LED dentro del arreglo registrado (0 hasta cantidad - 1).
 */
void LED_Toggle(uint8_t indice_led) {
    /* Validamos rigurosamente el índice antes de pasar la orden a la capa física */
    if (indice_led < leds_registrados) {
        /* Invoca la función de toggle nativa del silicio mediante la PAL */
        LED_PAL_Toggle(indice_led);
    }
}

/**
 * @brief Obtiene la cantidad de LEDs registrados en el sistema.
 * @return uint8_t Cantidad actual de LEDs bajo el control del driver.
 */
uint8_t LED_GetCount(void) {
    return leds_registrados;
}
