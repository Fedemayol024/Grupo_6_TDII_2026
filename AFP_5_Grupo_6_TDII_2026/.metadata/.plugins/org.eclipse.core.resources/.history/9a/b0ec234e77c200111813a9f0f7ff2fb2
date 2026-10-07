/**
 * @file API_led.c
 * @brief Implementación de las funciones de abstracción de LEDs.
 */

#include "API_led.h"
#include <stddef.h>

void LED_On(led_t * led) {
    if (led == NULL) return;

    // Si es invertido, enciende con RESET, de lo contrario con SET
    GPIO_PinState state = (led->inverted) ? GPIO_PIN_RESET : GPIO_PIN_SET;
    HAL_GPIO_WritePin(led->port, led->pin, state);
}

void LED_Off(led_t * led) {
    if (led == NULL) return;

    // Si es invertido, apaga con SET, de lo contrario con RESET
    GPIO_PinState state = (led->inverted) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(led->port, led->pin, state);
}

void LED_Toggle(led_t * led) {
    if (led == NULL) return;
    HAL_GPIO_TogglePin(led->port, led->pin);
}

void LED_All_Off(led_t ledGroup[], uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        // Llamamos a tu función individual para cada elemento
        LED_Off(&ledGroup[i]);
    }
}

void LED_ToggleAll(led_t ledGroup[], uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        LED_Toggle(&ledGroup[i]);
    }
}
