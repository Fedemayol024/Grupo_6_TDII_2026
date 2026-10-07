/**
 * @file Sys_Config.h
 * @author Mamani Flores Carlos (UTN FRT)
 * @brief Cabecera para la configuración del sistema, relojes y periféricos base de la placa.
 * @details Agrupa las inicializaciones del sistema de reloj (RCC), buses, periféricos GPIO
 *          y comunicación UART para desacoplar el archivo principal (main.c).
 * @version 1.0
 * @date 2026
 */

#ifndef SYS_CONFIG_H_
#define SYS_CONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart3;

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief Configura el reloj del sistema (System Clock) a la frecuencia máxima y estabilidad requerida.
 * @details Configura los osciladores (HSE/PLL), divisores de bus APB/AHB y el modo Over-Drive.
 * @return void
 */
void SystemClock_Config(void);

/**
 * @brief Inicializa los pines y puertos GPIO utilizados en la aplicación.
 * @details Habilita los clocks de los puertos y configura los pines de LEDs y botones.
 * @return void
 */
void MX_GPIO_Init(void);

/**
 * @brief Inicializa el periférico USART3 con su respectiva velocidad y parámetros de trama.
 * @return void
 */
void MX_USART3_UART_Init(void);

#endif /* SYS_CONFIG_H_ */
