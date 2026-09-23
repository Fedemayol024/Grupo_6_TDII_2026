/**
 * @file driver_time.h
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Interfaz abstracta para temporización bloqueante y no bloqueante.
 * @details Provee funciones de retardo clásico y estructuras de control de
 * tiempo basadas en software para implementar polling no bloqueante.
 * @version 2.0
 * @date 2026
 */

#ifndef DRIVER_TIME_H_
#define DRIVER_TIME_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Estructura de control para temporizadores no bloqueantes.
 */
typedef struct {
    uint32_t tiempo_inicio; ///< Registro del tick de inicio
    uint32_t duracion;      ///< Duración del intervalo en milisegundos
    bool en_marcha;         ///< Flag de estado del temporizador
} Timer_t;

/**
 * @brief Genera un retardo bloqueante en milisegundos.
 * @param ms Tiempo de espera en milisegundos.
 */
void TIME_DelayMS(uint32_t ms);

/**
 * @brief Obtiene el valor actual del contador de milisegundos del sistema.
 * @return uint32_t Ticks actuales transcurridos.
 */
uint32_t TIME_GetTicks(void);

/**
 * @brief Inicializa y arranca un temporizador no bloqueante.
 * @param timer Puntero a la estructura del temporizador.
 * @param duracion_ms Duración del intervalo en milisegundos.
 */
void TIME_TimerIniciar(Timer_t* timer, uint32_t duracion_ms);

/**
 * @brief Verifica si el tiempo del temporizador ha expirado.
 * @details Si expira y el temporizador está activo, retorna true.
 * Maneja correctamente el desbordamiento (overflow) del contador de ticks.
 * @param timer Puntero a la estructura del temporizador.
 * @return true si el tiempo se cumplió, false en caso contrario.
 */
bool TIME_TimerExpirado(Timer_t* timer);

/**
 * @brief Detiene un temporizador activo.
 * @param timer Puntero a la estructura del temporizador.
 */
void TIME_TimerDetener(Timer_t* timer);

#endif /* DRIVER_TIME_H_ */
