/**
 * @file API_delay.c
 * @brief Implementación de la lógica de retardos no bloqueantes.
 */

#include "API_delay.h"
#include <stddef.h>

void delayInit(delay_t * delay, tick_t duration) {
    if (delay != NULL) {
        delay->duration = duration;
        delay->status = DELAY_IDLE;
    }
}

bool delayRead(delay_t * delay) {
    bool expired = false;

    if (delay == NULL) return false;

    switch (delay->status) {
        case DELAY_IDLE:
            // Captura el tick actual e inicia el conteo
            delay->startTime = HAL_GetTick();
            delay->status = DELAY_RUNNING;
            break;

        case DELAY_RUNNING:
            // Verifica si ha pasado el tiempo comparando ticks
            if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
                delay->status = DELAY_EXPIRED;
                expired = true;
            }
            break;

        case DELAY_EXPIRED:
            // Reinicio automático para facilitar tareas periódicas
            delay->startTime = HAL_GetTick();
            delay->status = DELAY_RUNNING;
            break;

        default:
            delay->status = DELAY_IDLE;
            break;
    }
    return expired;
}

void delayWrite(delay_t * delay, tick_t duration) {
    if (delay != NULL) {
        delay->duration = duration;
    }
}

void delayReset(delay_t * delay) {
    if (delay != NULL) {
        delay->status = DELAY_IDLE;
    }
}
