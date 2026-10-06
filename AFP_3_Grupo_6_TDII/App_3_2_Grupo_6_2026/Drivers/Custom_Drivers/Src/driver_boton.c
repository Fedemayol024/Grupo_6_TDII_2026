/**
 * @file driver_boton.c
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Lógica algorítmica genérica para la evaluación de flancos.
 * @details Gestiona el estado lógico y el historial de múltiples pulsadores,
 * permitiendo capturar eventos de presión y liberación de forma independiente del micro.
 * @version 1.0
 * @date 2026
 */

#include "driver_boton.h"
#include "driver_boton_pal.h"
#include <stddef.h>

#define MAX_BOTONES 4 ///< Límite máximo estático de botones soportados por el sistema

/**
 * @brief Variables privadas globales de archivo para el control del módulo.
 * @details Se utiliza un arreglo estático 'estado_anterior_botones' para retener la memoria
 * de los estados lógicos pasados sin recurrir a la asignación dinámica (malloc).
 */
static uint8_t botones_registrados = 0;
static bool estado_anterior_botones[MAX_BOTONES] = {false};

/**
 * @brief Inicializa el driver de botones vinculando la configuración de la PAL.
 * @param tabla_hardware Puntero opaco (void*) a la tabla física del microcontrolador.
 * @param cantidad_botones Cantidad de pulsadores a administrar (menor o igual a MAX_BOTONES).
 */
void BOTON_Init(const void* tabla_hardware, uint8_t cantidad_botones) {
    /* Barrera de robustez perimetral: Validar puntero y límites estáticos del arreglo */
    if (tabla_hardware != NULL && cantidad_botones > 0 && cantidad_botones <= MAX_BOTONES) {
        botones_registrados = cantidad_botones;

        /* Inicializar el historial de estados en falso (todos los botones sueltos) */
        for (uint8_t i = 0; i < cantidad_botones; i++) {
            estado_anterior_botones[i] = false;
        }

        /* Pasar la configuración a la Capa de Abstracción de Plataforma haciendo un cast seguro */
        BOTON_PAL_Init((const BOTON_Hardware_t*)tabla_hardware, cantidad_botones);
    }
}

/**
 * @brief Lee el estado instantáneo filtrando la polaridad eléctrica.
 * @param indice_boton Índice del pulsador a consultar.
 * @return true si el botón está lógicamente presionado, false si está suelto.
 */
bool BOTON_LeerPresionado(uint8_t indice_boton) {
    /* Verificación de límites seguros para evitar accesos fuera de rango */
    if (indice_boton < botones_registrados) {
        return BOTON_PAL_LeerPinFisico(indice_boton);
    }
    return false;
}

/**
 * @brief Detecta el flanco de presión (cuando el usuario hunde el botón).
 * @param indice_boton Índice del pulsador a evaluar.
 * @return true únicamente en el ciclo donde pasa de suuelto a presionado.
 */
bool BOTON_DetectarFlancoPresionado(uint8_t indice_boton) {
    if (indice_boton >= botones_registrados) {
        return false;
    }

    bool estado_actual = BOTON_PAL_LeerPinFisico(indice_boton);
    bool flanco_detectado = false;

    /** * @note Lógica de Captura de Flanco de Presión:
     * El evento se valida como verdadero si el estado actual es 'true' (lógicamente presionado)
     * y el estado en el ciclo inmediatamente anterior era 'false' (lógicamente suelto).
     */
    if (estado_actual == true && estado_anterior_botones[indice_boton] == false) {
        flanco_detectado = true;
    }

    /* Sincronización del historial para la próxima evaluación en el loop principal */
    estado_anterior_botones[indice_boton] = estado_actual;
    return flanco_detectado;
}

/**
 * @brief Detecta el flanco de liberación (cuando el usuario suelta el botón).
 * @param indice_boton Índice del pulsador a evaluar.
 * @return true únicamente en el ciclo donde pasa de presionado a suelto.
 */
bool BOTON_DetectarFlancoSoltado(uint8_t indice_boton) {
    if (indice_boton >= botones_registrados) {
        return false;
    }

    bool estado_actual = BOTON_PAL_LeerPinFisico(indice_boton);
    bool flanco_detectado = false;

    /** * @note Lógica de Captura de Flanco de Liberación:
     * El evento se valida como verdadero si el estado actual es 'false' (lógicamente suelto)
     * y el estado en el ciclo inmediatamente anterior era 'true' (lógicamente presionado).
     */
    if (estado_actual == false && estado_anterior_botones[indice_boton] == true) {
        flanco_detectado = true;
    }

    /* Sincronización del historial para la próxima evaluación en el loop principal */
    estado_anterior_botones[indice_boton] = estado_actual;
    return flanco_detectado;
}
