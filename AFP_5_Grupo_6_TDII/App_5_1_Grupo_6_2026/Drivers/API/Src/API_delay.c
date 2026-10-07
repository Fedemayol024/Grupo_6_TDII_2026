/*
 * API_delay.c
 *
 *  Created on: Oct 6, 2026
 *      Author: santi
 */


#include "main.h"
#include "API_delay.h"
void delayInit(delay_t * delay, tick_t duration)
{
	delay->duration = duration; //← cargar la duracion
	  delay->running = false; // ← poner running en false

}
bool_t delayRead(delay_t * delay)
{
    bool_t cumplido = false;                     // por defecto, no se cumplio

    if (delay->running == false)                 // no estaba contando
    {
        delay->startTime = HAL_GetTick();        // anoto la hora de inicio
        delay->running = true;                   // arranco a contar
    }
    else                                         // ya estaba contando
    {
        if ((HAL_GetTick() - delay->startTime) >= delay->duration)   // ya paso el tiempo?
        {
            delay->running = false;              // termino, la proxima vez arranca de nuevo
            cumplido = true;
        }
    }

    return cumplido;
}

void delayWrite(delay_t * delay, tick_t duration)
{
	delay->duration = duration;
}
