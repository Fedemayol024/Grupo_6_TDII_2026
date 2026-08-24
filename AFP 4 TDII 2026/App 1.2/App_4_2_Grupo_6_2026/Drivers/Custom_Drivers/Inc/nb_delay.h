/**
 * @file nb_delay.h
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Interfaz del driver de retardos no bloqueantes (Non-Blocking Delay).
 * @details Provee tipos de datos y prototipos de funciones para crear temporizaciones
 *          sin bloquear la CPU, independientes de la plataforma mediante una capa PAL.
 * @version 1.0
 * @date 2026
 */

#ifndef INC_NB_DELAY_H_
#define INC_NB_DELAY_H_

#include <pal_tick_stm32.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/** @brief Tipo de dato para valores booleanos */
typedef bool bool_t;

/**
 * @brief Estructura de control para retardos no bloqueantes.
 */
typedef struct {
    tick_t startTime; /**< Marca de tiempo inicial del retardo */
    tick_t duration;  /**< Duración configurada en milisegundos */
    bool_t running;   /**< Flag indicador de conteo en progreso */
} nb_delay_t;

/**
 * @brief Inicializa una estructura de retardo no bloqueante.
 * @param[out] delay Puntero a la estructura nb_delay_t a inicializar.
 * @param[in]  duration Duración del retardo en milisegundos (> 0).
 */
void nb_delay_init(nb_delay_t * delay, tick_t duration);

/**
 * @brief Lee y actualiza el estado del retardo no bloqueante.
 * @details Si no estaba en marcha, toma la marca de tiempo actual y arranca.
 *          Si ya estaba en marcha, verifica si transcurrió la duración requerida.
 * @param[in,out] delay Puntero a la estructura nb_delay_t.
 * @return true si el retardo expiró correctamente, false si está en proceso o ante error de parámetros.
 */
bool_t nb_delay_read(nb_delay_t * delay);

/**
 * @brief Modifica la duración de un retardo previamente creado.
 * @param[in,out] delay Puntero a la estructura nb_delay_t a modificar.
 * @param[in]     duration Nueva duración en milisegundos (> 0).
 */
void nb_delay_write(nb_delay_t * delay, tick_t duration);

#endif /* INC_NB_DELAY_H_ */
