/**
 * @file driver_boton_pal.c
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Implementación física de la lectura de pulsadores para STM32.
 * @details Administra el acceso directo a los registros GPIO a través de la HAL de ST,
 * resolviendo la inversión lógica según la configuración eléctrica del pin.
 * @version 1.0
 * @date 2026
 */

#include "driver_boton_pal.h"
#include <stddef.h>

/**
 * @brief Variables privadas de la capa PAL con alcance de archivo para STM32.
 * @details Almacenan la referencia a la tabla de hardware física inyectada por la aplicación.
 */
static const BOTON_Hardware_t* tabla_botones_plataforma = NULL;
static uint8_t cantidad_botones_plataforma = 0;

/**
 * @brief Vincula la capa PAL con la tabla de estructuras físicas de los botones.
 * @param tabla Puntero al arreglo de estructuras BOTON_Hardware_t de la aplicación.
 * @param cantidad Cantidad total de pulsadores registrados en la tabla física.
 */
void BOTON_PAL_Init(const BOTON_Hardware_t* tabla, uint8_t cantidad) {
    /* Barrera de robustez perimetral: Evitar inicializaciones con datos nulos o vacíos */
    if (tabla != NULL && cantidad > 0) {
        tabla_botones_plataforma = tabla;
        cantidad_botones_plataforma = cantidad;
    }
}

/**
 * @brief Lee el estado eléctrico del pin y lo normaliza según su configuración.
 * @param indice Posición del pulsador a consultar dentro de la tabla física.
 * @return true si el botón está lógicamente presionado, false si está suelto.
 */
bool BOTON_PAL_LeerPinFisico(uint8_t indice) {
    /* Protección contra accesos fuera de rango o consultas antes de inicializar la PAL */
    if (indice >= cantidad_botones_plataforma || tabla_botones_plataforma == NULL) {
        return false;
    }

    /* 1. Leer el estado eléctrico directo desde los registros del silicio de ST */
    GPIO_PinState estado_real = HAL_GPIO_ReadPin(tabla_botones_plataforma[indice].puerto, tabla_botones_plataforma[indice].pin);

    /** * @note Normalización de la Polaridad Eléctrica:
     * Traduce los niveles de tensión (SET/RESET) a un estado booleano conceptual puro
     * independiente de cómo esté cableado el circuito en el PCB:
     * - BOTON_ACTIVO_BAJO (Pull-Up): El pin cae a 0V (RESET) al presionar -> Retorna true.
     * - BOTON_ACTIVO_ALTO (Pull-Down): El pin sube a VCC (SET) al presionar -> Retorna true.
     */
    if (tabla_botones_plataforma[indice].modo == BOTON_ACTIVO_BAJO) {
        return (estado_real == GPIO_PIN_RESET);
    } else {
        return (estado_real == GPIO_PIN_SET);
    }
}
