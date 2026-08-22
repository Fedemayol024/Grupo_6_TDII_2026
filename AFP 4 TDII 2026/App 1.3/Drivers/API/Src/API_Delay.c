/*
 * API_Delay.c
 *
 *  Created on: 22.08.2026
 *      Author: fedem
 */
#include "API_delay.h"
#include "stm32f7xx_hal.h" // Cambia "f4" por la familia de tu micro si es distinta (ej. f1, f7, g0)

void delayInit(delay_t * delay, tick_t duration) {
    delay->duration = duration;
    delay->running = false;
}

bool delayRead(delay_t * delay) {
    if (!delay->running) {
        delay->startTime = HAL_GetTick(); // Toma la marca de tiempo actual
        delay->running = true;
        return false; // Aún no terminó
    } else {
        // Verifica si la diferencia de tiempo es mayor a la duración
        if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
            delay->running = false; // Reinicia para el próximo ciclo
            return true; // ¡El tiempo se cumplió!
        }
        return false;
    }
}

void delayWrite(delay_t * delay, tick_t duration) {
    delay->duration = duration;
}
