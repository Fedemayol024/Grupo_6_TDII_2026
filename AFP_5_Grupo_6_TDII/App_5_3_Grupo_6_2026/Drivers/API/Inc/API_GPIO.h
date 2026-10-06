/**
 * @file    API_GPIO.h
 * @author  Mayol Federico (UTN FRT) - Grupo 6
 * @brief   Driver para el manejo de los LEDs y el pulsador de la placa.
 * @version 1.0
 * @date    2026
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "API_delay.h"   /* bool_t */

/* Exported types ------------------------------------------------------------*/
typedef uint16_t led_t;            /* Debe ser uint16_t: es el pin del LED */
typedef bool_t buttonStatus_t;     /* true = pulsador presionado */

/* Exported functions prototypes ---------------------------------------------*/
void MX_GPIO_Init(void);
void writeLedOn_GPIO(led_t LDx);
void writeLedOff_GPIO(led_t LDx);
void toggleLed_GPIO(led_t LDx);
buttonStatus_t readButton_GPIO(void);

#endif /* API_INC_API_GPIO_H_ */
