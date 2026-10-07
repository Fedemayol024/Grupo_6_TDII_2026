/**
 * @file API_delay.c
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Implementación de la lógica de retardos no bloqueantes.
 * @details Contiene la máquina de estados orientada a la gestión de tiempos basada en HAL_GetTick(),
 *          garantizando protección frente al desborde de contadores y soporte para tareas periódicas.
 * @version 1.0
 * @date 2026
 */

#include "API_delay.h"

/**
 * @brief Inicializa la estructura del retardo estableciendo su duración y estado en IDLE.
 * @details Valida que el puntero no sea NULL antes de asignar los valores.
 * @param delay Puntero a la estructura delay_t.
 * @param duration Duración del retardo en milisegundos.
 * @return void
 */
void delayInit(delay_t * delay, tick_t duration) {
    if (delay == NULL) return;

    delay->duration = duration;
    delay->status = DELAY_IDLE;
}

/**
 * @brief Evalúa y actualiza la máquina de estados del retardo.
 * @details Si está en IDLE, captura el tiempo actual y arranca. Si está RUNNING, comprueba
 *          el tiempo transcurrido de forma segura ante desbordes. Si está EXPIRED, notifica la expiración
 *          y reinicia el ciclo de forma automática.
 * @param delay Puntero a la estructura delay_t.
 * @return true si el tiempo se cumplió, false en caso contrario.
 */
bool delayRead(delay_t * delay) {
    bool expired = false;

    // Validación de robustez: previene fallos por puntero nulo
    if (delay == NULL) return false;

    switch (delay->status) {
        case DELAY_IDLE:
            // Captura el tick actual e inicia el conteo asíncrono
            delay->startTime = HAL_GetTick();
            delay->status = DELAY_RUNNING;
            break;

        case DELAY_RUNNING:
            // Comprobación segura contra desborde (roll-over) de 32 bits de HAL_GetTick()
            if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
                delay->status = DELAY_EXPIRED;
                expired = true;
            }
            break;

        case DELAY_EXPIRED:
            // Reinicio automático para facilitar tareas periódicas sin re-inicializar
            delay->startTime = HAL_GetTick();
            delay->status = DELAY_RUNNING;
            break;

        default:
            // Estado por defecto de seguridad ante corrupciones de memoria
            delay->status = DELAY_IDLE;
            break;
    }

    return expired;
}

/**
 * @brief Actualiza dinámicamente la duración de un retardo.
 * @details Valida el puntero y modifica el campo duration sin alterar el estado actual de conteo.
 * @param delay Puntero a la estructura delay_t.
 * @param duration Nueva duración en milisegundos.
 * @return void
 */
void delayWrite(delay_t * delay, tick_t duration) {
    if (delay == NULL) return;

    delay->duration = duration;
}

/**
 * @brief Fuerza el reseteo del retardo llevándolo al estado IDLE.
 * @param delay Puntero a la estructura delay_t.
 * @return void
 */
void delayReset(delay_t * delay) {
    if (delay == NULL) return;

    delay->status = DELAY_IDLE;
}
