/**
 * @file driver_time.c
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Implementación del driver de tiempo con soporte no bloqueante.
 * @details Vincula las lecturas al SysTick de la plataforma y resuelve la
 * matemática de desbordamiento de variables de 32 bits.
 * @version 2.0
 * @date 2026
 */

#include "driver_time.h"
#include "main.h" // Vinculación temporal a la HAL de ST
#include <stddef.h>

/**
 * @brief Genera un retardo bloqueante en milisegundos.
 * @param ms Tiempo de espera en milisegundos.
 */
void TIME_DelayMS(uint32_t ms) {
    /* Abstracción del retardo de la plataforma actual (STM32 HAL) */
    HAL_Delay(ms);
}

/**
 * @brief Obtiene el valor actual del contador de milisegundos del sistema.
 * @return uint32_t Ticks actuales transcurridos.
 */
uint32_t TIME_GetTicks(void) {
    /* Retorna la base de tiempos del SysTick mapeada por ST */
    return HAL_GetTick();
}

/**
 * @brief Inicializa y arranca un temporizador no bloqueante.
 * @param timer Puntero a la estructura del temporizador.
 * @param duracion_ms Duración del intervalo en milisegundos.
 */
void TIME_TimerIniciar(Timer_t* timer, uint32_t duracion_ms) {
    /* Barrera de robustez: protección contra punteros nulos */
    if (timer != NULL) {
        timer->tiempo_inicio = TIME_GetTicks(); // Captura la marca de tiempo actual
        timer->duracion = duracion_ms;          // Asigna el intervalo de muestreo
        timer->en_marcha = true;               // Activa el contador por software
    }
}

/**
 * @brief Verifica si el tiempo del temporizador ha expirado.
 * @param timer Puntero a la estructura del temporizador.
 * @return true si el tiempo se cumplió, false en caso contrario o si no está activo.
 */
bool TIME_TimerExpirado(Timer_t* timer) {
    /* Validación perimetral: si el temporizador es nulo o está apagado, no procesa */
    if (timer == NULL || !timer->en_marcha) {
        return false;
    }

    uint32_t tiempo_actual = TIME_GetTicks();

    /** * @note Análisis de Robustez de Desbordamiento (Overflow):
     * Debido al uso de variables de 32 bits sin signo (uint32_t), la resta algebraica
     * (tiempo_actual - tiempo_inicio) aprovecha las propiedades de la aritmética modular complementaria.
     * Si 'tiempo_actual' se desborda y vuelve a 0, el resultado de la resta sigue siendo
     * exactamente igual a la distancia temporal real transcurrida. Esto previene fallas críticas
     * por desbordamiento del SysTick (aproximadamente cada 49.7 días).
     */
    if ((tiempo_actual - timer->tiempo_inicio) >= timer->duracion) {
        return true;
    }

    return false;
}

/**
 * @brief Detiene un temporizador activo.
 * @param timer Puntero a la estructura del temporizador.
 */
void TIME_TimerDetener(Timer_t* timer) {
    /* Barrera de robustez básica antes de modificar el estado */
    if (timer != NULL) {
        timer->en_marcha = false; // Desactiva la bandera para ignorar chequeos en el ciclo principal
    }
}
