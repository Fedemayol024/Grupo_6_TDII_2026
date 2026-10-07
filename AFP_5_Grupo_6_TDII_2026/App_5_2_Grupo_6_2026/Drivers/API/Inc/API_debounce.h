/**
 * @file API_debounce.h
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief API para la gestión de múltiples pulsadores con antirrebote (Debounce) no bloqueante.
 * @details Este driver implementa una Máquina de Estados Finitos (MEF) para cada instancia
 *          de botón. Utiliza la API_delay para el filtrado temporal, permitiendo gestionar N botones
 *          de forma independiente y reentrante sin bloquear la ejecución del CPU.
 * @version 2.0
 * @date 2026
 */

#ifndef API_DEBOUNCE_H_
#define API_DEBOUNCE_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_delay.h"
#include <stdbool.h>
#include <stddef.h>

/* Exported types ------------------------------------------------------------*/

/**
 * @brief Estados internos de la MEF de antirrebote.
 */
typedef enum {
    BUTTON_UP,      /**< Estado de reposo (botón suelto). */
    BUTTON_FALLING, /**< Transición detectada (filtrando ruido de bajada). */
    BUTTON_DOWN,    /**< Estado presionado estable. */
    BUTTON_RISING   /**< Transición detectada (filtrando ruido de subida). */
} debounceState_t;

/**
 * @brief Estructura de control para una instancia de botón.
 * @details Contiene tanto la configuración de hardware como la memoria de estado
 *          necesaria para que el driver sea reentrante.
 */
typedef struct {
    GPIO_TypeDef* port;     /**< Puerto GPIO asociado (ej: GPIOB). */
    uint16_t pin;           /**< Pin GPIO asociado (ej: GPIO_PIN_11). */
    bool inverted;          /**< Lógica: true para Active Low, false para Active High. */
    bool keyPressed;        /**< Flag de evento: indica que ocurrió una pulsación válida. */
    debounceState_t state;  /**< Memoria de estado de la MEF para este botón. */
    delay_t timer;          /**< Objeto de retardo para el filtrado de este botón. */
} button_t;

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief Inicializa la instancia de un botón y su MEF asociada.
 * @param btn Puntero a la estructura button_t del botón a inicializar.
 * @return void
 */
void debounceFSM_Init(button_t* btn);

/**
 * @brief Actualiza la máquina de estados de un botón específico.
 * @details Esta función debe llamarse periódicamente (polling) en el bucle principal o tarea asíncrona.
 * @param btn Puntero a la estructura button_t a procesar.
 * @return void
 */
void debounceFSM_Update(button_t* btn);

/**
 * @brief Lee y resetea el flag de evento del botón.
 * @details Implementa lógica "Clear-on-Read" para asegurar que el evento se procese una sola vez.
 * @param btn Puntero a la estructura button_t.
 * @return true si se detectó una pulsación confirmada desde la última lectura, false en caso contrario.
 */
bool readKey(button_t* btn);

#endif /* API_DEBOUNCE_H_ */
