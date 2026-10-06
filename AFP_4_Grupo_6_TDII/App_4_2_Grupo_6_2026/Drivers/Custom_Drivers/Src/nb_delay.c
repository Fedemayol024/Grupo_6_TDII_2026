/**
 * @file nb_delay.c
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Implementación del driver genérico de retardos no bloqueantes.
 * @details Contiene la lógica de control de temporizaciones no bloqueantes
 *          utilizando la capa de abstracción pal_tick para la base de tiempo.
 *          Implementa verificaciones defensivas contra punteros nulos, duraciones
 *          inválidas y manejo aritmético seguro frente al desbordamiento del contador.
 * @version 1.0
 * @date 2026
 */

/*==================[Inclusiones]============================================*/
#include "nb_delay.h"

/*==================[Implementación de funciones públicas]====================*/

/**
 * @brief Inicializa la estructura del delay no bloqueante.
 * @details Carga la duración deseada, apaga la bandera de ejecución y resetea
 *          la marca de tiempo inicial. No inicia el conteo.
 * @param[out] delay Puntero a la estructura nb_delay_t a inicializar.
 * @param[in]  duration Duración del retardo en milisegundos (> 0).
 */
void nb_delay_init(nb_delay_t * delay, tick_t duration)
{
    /* Verificación de parámetros de entrada: puntero válido y duración mayor a cero */
    if ((delay == NULL) || (duration == 0U))
    {
        return;
    }

    /* Asignación de parámetros iniciales */
    delay->duration = duration;
    delay->running = false;
    delay->startTime = 0U;
}

/**
 * @brief Lee el estado del retardo y gestiona el conteo de tiempo.
 * @details Si el retardo no estaba activo, toma la marca de tiempo actual del
 *          sistema mediante la PAL y pasa al estado activo. Si ya estaba activo,
 *          evalúa si transcurrió el tiempo configurado mediante aritmética modular.
 * @param[in,out] delay Puntero a la estructura nb_delay_t.
 * @return true si el tiempo configurado expiró, false si aún está en conteo o ante error.
 */
bool_t nb_delay_read(nb_delay_t * delay)
{
    bool_t timeReached = false;

    /* Validación defensiva: instancia nula o no configurada */
    if ((delay == NULL) || (delay->duration == 0U))
    {
        return false;
    }

    /* Evaluación del estado del retardo */
    if (!delay->running)
    {
        /* Primera ejecución: captura la marca de tiempo inicial e inicia el conteo */
        delay->startTime = pal_tick_get();
        delay->running = true;
    }
    else
    {
        /*
         * Comprobación de expiración:
         * La resta (tiempo_actual - startTime) en enteros sin signo (uint32_t)
         * resuelve automáticamente el desbordamiento (overflow) del contador de ticks.
         */
        if ((pal_tick_get() - delay->startTime) >= delay->duration)
        {
            timeReached = true;
            delay->running = false; /* Reinicia el flag para el siguiente ciclo */
        }
    }

    return timeReached;
}

/**
 * @brief Actualiza la duración de un retardo existente.
 * @details Modifica el campo duration sin alterar el estado actual de conteo
 *          ni la marca de tiempo inicial.
 * @param[in,out] delay Puntero a la estructura nb_delay_t.
 * @param[in]     duration Nueva duración en milisegundos (> 0).
 */
void nb_delay_write(nb_delay_t * delay, tick_t duration)
{
    /* Verificación de seguridad ante puntero nulo o duración nula */
    if ((delay == NULL) || (duration == 0U))
    {
        return;
    }

    delay->duration = duration;
}
