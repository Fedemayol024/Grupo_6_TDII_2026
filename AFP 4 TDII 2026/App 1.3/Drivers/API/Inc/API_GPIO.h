/*
 * API_GPIO.h
 *
 *  Created on: 09.08.2026
 *      Author: fedem
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_
#include <stdint.h>
#include <stdbool.h>


typedef uint16_t led_t;
typedef bool buttonStatus_t;


void MX_GPIO_Init(void);
void WriteLedOn_GPIO(led_t LDx);
void WriteLedOff_GPIO(led_t LDx);
void ToggleLed_GPIO(led_t LDx);
buttonStatus_t ReadButton_GPIO(void);

#endif /* API_INC_API_GPIO_H_ */
