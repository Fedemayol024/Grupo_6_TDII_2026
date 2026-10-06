/**
 * @file driver_led_pal.c
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Implementación de la Capa de Abstracción de Plataforma (PAL) para STM32.
 * @details Administra el acceso directo a las funciones de la HAL de ST utilizando
 * la tabla de configuración física provista por la aplicación.
 * @version 2.0
 * @date 2026
 */

#include "driver_led_pal.h"
#include <stddef.h>

/**
 * @brief Variables privadas de la PAL encapsuladas con alcance de archivo.
 * @details Al definirse como 'static', quedan completamente ocultas para el driver genérico
 * y la aplicación, cumpliendo con el ocultamiento de información (Information Hiding).
 */
static const LED_Hardware_t* tabla_leds_plataforma = NULL;
static uint8_t cantidad_leds_plataforma = 0;

/**
 * @brief Vincula la PAL con la tabla de hardware activa de STM32.
 * @param tabla Puntero a la matriz de estructuras físicas LED_Hardware_t.
 * @param cantidad Número total de elementos dentro de la matriz física.
 */
void LED_PAL_Init(const LED_Hardware_t* tabla, uint8_t cantidad) {
    /* Barrera de seguridad para evitar punteros huérfanos o inicializaciones nulas */
    if (tabla != NULL && cantidad > 0) {
        tabla_leds_plataforma = tabla;
        cantidad_leds_plataforma = cantidad;
    }
}

/**
 * @brief Ejecuta la escritura física sobre el silicio utilizando la HAL de ST.
 * @param indice Posición del LED dentro del arreglo físico de hardware.
 * @param estado Nivel lógico deseado (true para activar el pin, false para desactivar).
 */
void LED_PAL_Write(uint8_t indice, bool estado) {
    /* Protección contra desbordamiento de índice o tabla física no inicializada */
    if (indice >= cantidad_leds_plataforma || tabla_leds_plataforma == NULL) {
        return;
    }

    /* Mapeo del tipo booleano genérico al enum específico de la HAL de ST */
    GPIO_PinState estado_pin = (estado) ? GPIO_PIN_SET : GPIO_PIN_RESET;

    /* Acceso directo al hardware mediante las estructuras indexadas */
    HAL_GPIO_WritePin(tabla_leds_plataforma[indice].port, tabla_leds_plataforma[indice].pin, estado_pin);
}

/**
 * @brief Ejecuta el toggle físico sobre el pin del microcontrolador STM32.
 * @param indice Posición del LED dentro del arreglo físico de hardware.
 */
void LED_PAL_Toggle(uint8_t indice) {
    /* Protección perimetral de robustez para evitar accesos a memoria inválida */
    if (indice >= cantidad_leds_plataforma || tabla_leds_plataforma == NULL) {
        return;
    }

    /* Conmutación directa operando los registros del periférico mediante HAL */
    HAL_GPIO_TogglePin(tabla_leds_plataforma[indice].port, tabla_leds_plataforma[indice].pin);
}
