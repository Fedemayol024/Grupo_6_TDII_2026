/**
 * @file driver_boton.h
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Interfaz genérica para control de pulsadores configurables.
 * @details Provee tipos de datos lógicos para abstraer la polaridad y flancos
 * de cualquier botón conectado al sistema.
 * @version 1.0
 * @date 2026
 */

#ifndef DRIVER_BOTON_H_
#define DRIVER_BOTON_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Define el modo de conexión eléctrica del pulsador (Polaridad).
 */
typedef enum {
    BOTON_ACTIVO_BAJO = 0, ///< Configuración en Pull-Up (Presionado = 0 lógico)
    BOTON_ACTIVO_ALTO      ///< Configuración en Pull-Down (Presionado = 1 lógico)
} Boton_Modo_t;

/**
 * @brief Inicializa el driver de botones vinculando la configuración de la PAL.
 * @param tabla_hardware Puntero opaco a la tabla física del microcontrolador.
 * @param cantidad_botones Cantidad de pulsadores a administrar.
 */
void BOTON_Init(const void* tabla_hardware, uint8_t cantidad_botones);

/**
 * @brief Lee el estado instantáneo filtrando la polaridad eléctrica.
 * @param indice_boton Índice del pulsador a consultar.
 * @return true si el botón está físicamente presionado, false si está suelto.
 */
bool BOTON_LeerPresionado(uint8_t indice_boton);

/**
 * @brief Detecta el flanco de presión (cuando el usuario hunde el botón).
 * @param indice_boton Índice del pulsador.
 * @return true únicamente en el ciclo donde pasa de suelto a presionado.
 */
bool BOTON_DetectarFlancoPresionado(uint8_t indice_boton);

/**
 * @brief Detecta el flanco de liberación (cuando el usuario suelta el botón).
 * @param indice_boton Índice del pulsador.
 * @return true únicamente en el ciclo donde pasa de presionado a suelto.
 */
bool BOTON_DetectarFlancoSoltado(uint8_t indice_boton);

#endif /* DRIVER_BOTON_H_ */
