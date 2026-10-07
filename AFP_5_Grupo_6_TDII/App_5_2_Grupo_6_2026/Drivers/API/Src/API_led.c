/**
 * @file API_led.c
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Implementación de las funciones de abstracción de LEDs.
 * @details Contiene la lógica para el manejo independiente de hardware de LEDs genéricos mediante descriptores por referencia,
 *          sopportando polaridades de lógica directa e invertida (active-high y active-low) y operaciones grupales.
 * @version 1.0
 * @date 2026
 */

#include "API_led.h"

/**
 * @brief Enciende el LED referenciado según su lógica configurada.
 * @details Valida que el puntero no sea NULL. Si el LED es de lógica activa baja (LED_LOGIC_ACTIVE_LOW),
 *          escribe un estado GPIO_PIN_RESET; de lo contrario, escribe GPIO_PIN_SET.
 * @param led Puntero a la estructura led_t que define el hardware del LED.
 * @return void
 */
void LED_On(led_t * led) {
    // Validación de robustez: evita fallos por punteros nulos
    if (led == NULL) return;

    // Determina el estado físico del pin evaluando si la lógica es invertida
    GPIO_PinState state = (led->logic == LED_LOGIC_ACTIVE_LOW) ? GPIO_PIN_RESET : GPIO_PIN_SET;
    HAL_GPIO_WritePin(led->port, led->pin, state);
}

/**
 * @brief Apaga el LED referenciado según su lógica configurada.
 * @details Valida que el puntero no sea NULL. Si el LED es de lógica activa baja (LED_LOGIC_ACTIVE_LOW),
 *          escribe un estado GPIO_PIN_SET para apagarlo; de lo contrario, escribe GPIO_PIN_RESET.
 * @param led Puntero a la estructura led_t que define el hardware del LED.
 * @return void
 */
void LED_Off(led_t * led) {
    // Validación de robustez: evita fallos por punteros nulos
    if (led == NULL) return;

    // Determina el estado de apagado según la polaridad
    GPIO_PinState state = (led->logic == LED_LOGIC_ACTIVE_LOW) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(led->port, led->pin, state);
}

/**
 * @brief Conmuta el estado físico actual del LED.
 * @details Valida que el puntero no sea NULL e invierte el estado lógico actual del pin GPIO mediante HAL.
 * @param led Puntero a la estructura led_t que define el hardware del LED.
 * @return void
 */
void LED_Toggle(led_t * led) {
    // Validación de robustez: evita fallos por punteros nulos
    if (led == NULL) return;

    // Invierte el estado actual del pin físico
    HAL_GPIO_TogglePin(led->port, led->pin);
}

/**
 * @brief Enciende todos los LEDs contenidos en un arreglo.
 * @details Recorre de forma iterativa el arreglo aplicando la función LED_On a cada elemento.
 * @param ledGroup Arreglo de estructuras led_t que conforman el grupo.
 * @param size Cantidad de elementos (LEDs) presentes en el arreglo.
 * @return void
 */
void LED_All_On(led_t ledGroup[], uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        LED_On(&ledGroup[i]);
    }
}

/**
 * @brief Apaga todos los LEDs contenidos en un arreglo.
 * @details Recorre de forma iterativa el arreglo aplicando la función LED_Off a cada elemento.
 * @param ledGroup Arreglo de estructuras led_t que conforman el grupo.
 * @param size Cantidad de elementos (LEDs) presentes en el arreglo.
 * @return void
 */
void LED_All_Off(led_t ledGroup[], uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        LED_Off(&ledGroup[i]);
    }
}

/**
 * @brief Conmuta el estado de todos los LEDs contenidos en un arreglo.
 * @details Recorre de forma iterativa el arreglo aplicando la función LED_Toggle a cada elemento.
 * @param ledGroup Arreglo de estructuras led_t que conforman el grupo.
 * @param size Cantidad de elementos (LEDs) presentes en el arreglo.
 * @return void
 */
void LED_ToggleAll(led_t ledGroup[], uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        LED_Toggle(&ledGroup[i]);
    }
}
