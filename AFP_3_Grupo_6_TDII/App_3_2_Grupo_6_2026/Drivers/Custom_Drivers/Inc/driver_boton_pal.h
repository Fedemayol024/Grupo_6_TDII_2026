/**
 * @file driver_boton_pal.h
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Capa de Abstracción de Plataforma (PAL) para botones en STM32.
 * @details Define la estructura de hardware física y las interfaces de bajo nivel
 * necesarias para conectar el driver genérico con la HAL de ST.
 * @version 1.0
 * @date 2026
 */

#ifndef DRIVER_BOTON_PAL_H_
#define DRIVER_BOTON_PAL_H_

#include "main.h"
#include "driver_boton.h"

/**
 * @brief Configuración física e individual de un pulsador en la plataforma.
 * @details Agrupa los elementos de hardware de la HAL de ST junto con el modo
 * de conexión eléctrica (polaridad) del pin.
 */
typedef struct {
    GPIO_TypeDef* puerto;   ///< Puerto GPIO real de la MCU (GPIOA, GPIOB, etc.)
    uint16_t pin;           ///< Pin físico real de la MCU (GPIO_PIN_X)
    Boton_Modo_t modo;      ///< Polaridad eléctrica: BOTON_ACTIVO_ALTO o BOTON_ACTIVO_BAJO
} BOTON_Hardware_t;

/**
 * @brief Vincula la capa PAL con la tabla de estructuras físicas de los botones.
 * @param tabla Puntero al arreglo de estructuras BOTON_Hardware_t definido por la aplicación.
 * @param cantidad Cantidad total de pulsadores registrados en la tabla.
 */
void BOTON_PAL_Init(const BOTON_Hardware_t* tabla, uint8_t cantidad);

/**
 * @brief Lee el estado eléctrico del pin y lo normaliza según su configuración.
 * @details Realiza la lectura mediante HAL_GPIO_ReadPin y aplica la inversión lógica
 * en caso de que el pulsador esté configurado como BOTON_ACTIVO_BAJO (Pull-Up).
 * @param indice Posición del pulsador a consultar dentro de la tabla física.
 * @return true si el botón está lógicamente presionado, false si está suelto.
 */
bool BOTON_PAL_LeerPinFisico(uint8_t indice);

#endif /* DRIVER_BOTON_PAL_H_ */
