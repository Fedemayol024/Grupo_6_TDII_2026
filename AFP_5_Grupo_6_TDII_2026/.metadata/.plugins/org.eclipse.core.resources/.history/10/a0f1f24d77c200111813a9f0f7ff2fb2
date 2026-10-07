/**
 * @file API_debounce.c
 * @author CarlitozMF
 * @brief Implementación de la lógica reentrante de antirrebote para múltiples botones.
 * @version 2.0
 */

#include "API_debounce.h"
#include <stddef.h>

/* Definiciones privadas -----------------------------------------------------*/

/** * @brief Tiempo de guarda en milisegundos para filtrar los rebotes mecánicos.
 * @note 40ms es un estándar robusto para la mayoría de pulsadores táctiles.
 */
#define DEBOUNCE_TIME_MS 40

/* Funciones privadas --------------------------------------------------------*/

/**
 * @brief Lee el nivel físico del pin y adapta el resultado a la lógica configurada.
 * @param btn Puntero al objeto botón que contiene la config de puerto/pin e inversión.
 * @return true si el botón está activo según su configuración (Active High/Low).
 * @return false si el botón está en reposo.
 */
static bool readButton_Physical(button_t* btn) {
    bool pin_state = (HAL_GPIO_ReadPin(btn->port, btn->pin) == GPIO_PIN_SET);

    /* Si inverted es true, el botón está activo cuando el pin está en RESET (Lógica Negativa) */
    return btn->inverted ? !pin_state : pin_state;
}

/* Funciones públicas --------------------------------------------------------*/

/**
 * @brief Inicializa la estructura del botón.
 * @details Setea el tiempo del timer interno y coloca la MEF en el estado inicial BUTTON_UP.
 * @param btn Puntero a la estructura button_t.
 */
void debounceFSM_Init(button_t* btn) {
    if (btn != NULL) {
        delayInit(&(btn->timer), DEBOUNCE_TIME_MS);
        btn->state = BUTTON_UP;
        btn->keyPressed = false;
    }
}

/**
 * @brief Motor de la Máquina de Estados Finitos para el antirrebote.
 * @details Esta función implementa el filtrado temporal en ambos flancos (subida y bajada).
 * Las transiciones solo se confirman si la señal permanece estable durante DEBOUNCE_TIME_MS.
 * @param btn Puntero a la instancia del botón a actualizar.
 */
void debounceFSM_Update(button_t* btn) {
    if (btn == NULL) return;

    switch (btn->state) {

        /* Estado: Reposo. Esperando detección de presión. */
        case BUTTON_UP:
            if (readButton_Physical(btn)) {
                delayReset(&(btn->timer)); // Iniciamos conteo de validación
                btn->state = BUTTON_FALLING;
            }
            break;

        /* Estado: Transitorio de presión. Verificando estabilidad del flanco. */
        case BUTTON_FALLING:
            if (delayRead(&(btn->timer))) {
                if (readButton_Physical(btn)) {
                    /* Flanco de bajada confirmado */
                    btn->keyPressed = true;
                    btn->state = BUTTON_DOWN;
                } else {
                    /* Fue ruido: volver a reposo */
                    btn->state = BUTTON_UP;
                }
            }
            break;

        /* Estado: Presión estable. Esperando detección de liberación. */
        case BUTTON_DOWN:
            if (!readButton_Physical(btn)) {
                delayReset(&(btn->timer)); // Iniciamos conteo de validación de subida
                btn->state = BUTTON_RISING;
            }
            break;

        /* Estado: Transitorio de liberación. Verificando estabilidad. */
        case BUTTON_RISING:
            if (delayRead(&(btn->timer))) {
                if (!readButton_Physical(btn)) {
                    /* Flanco de subida confirmado: vuelta al reposo */
                    btn->state = BUTTON_UP;
                } else {
                    /* Fue ruido: el botón sigue presionado */
                    btn->state = BUTTON_DOWN;
                }
            }
            break;

        /* Protección ante estados no definidos */
        default:
            btn->state = BUTTON_UP;
            break;
    }
}

/**
 * @brief Interfaz de lectura de eventos para la aplicación.
 * @details Permite conocer si hubo una pulsación confirmada.
 * @param btn Puntero a la instancia del botón.
 * @return true si hubo un evento, false en caso contrario.
 * @note Limpia el flag keyPressed automáticamente (Clear on Read).
 */
bool readKey(button_t* btn) {
    bool event = false;
    if (btn != NULL) {
        event = btn->keyPressed;
        btn->keyPressed = false;
    }
    return event;
}
