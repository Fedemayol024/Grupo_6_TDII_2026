/***********************************
 * API_GPIO.h
 *
 *  Created on: Aug 11, 2026
 *      Author: emalu
 *      Function Driver: XXXX
 *
 **********************************/

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

/*Includes*************/
#include <stdint.h>
#include <stdbool.h>

/*Exproted types********************/
typedef uint16_t led_t;
typedef bool buttonStatus_t;

/*Exported function prototypes********/
void MX_GPIO_Init(void);
void writeLedOn_GPIO(led_t LDx);
void writeLedOff_GPIO(led_t LDx);
void toggleLed_GPIO(led_t LDx);
buttonStatus_t readButton_GPIO(void);
#endif /* API_INC_API_GPIO_H_ */
