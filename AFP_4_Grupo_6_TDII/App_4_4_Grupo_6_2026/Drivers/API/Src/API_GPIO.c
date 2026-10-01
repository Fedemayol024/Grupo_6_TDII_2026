/**********************
 * API_GPIO.c
 *
 *  Created on: Aug 11, 2026
 *      Author: emalu
 *********************/

/*Includes*************************************/
#include "main.h"
#include "API_GPIO.h"

/*Defines****************************************/

/*Declaration of variables**************************/
//Valores esperados para LDx: LED1 | LED2 | LED3
led_t LDx;


/**
 * @brief GPIO Led On function
 * @param led_t LDx
 * @reval None
 */
void writeLedOn_GPIO(led_t LDx)
{
	HAL_GPIO_WritePin(GPIOC, LDx, GPIO_PIN_SET);
}

/**
 * @brief GPIO Led Off function
 * @param led_t LDx
 * @reval None
 */
void writeLedOff_GPIO(led_t LDx)
{
	HAL_GPIO_WritePin(GPIOC, LDx, GPIO_PIN_RESET);
}

/**
 * @brief GPIO Toggle Led function
 * @param led_t LDx
 * @reval None
 */
void toggleLed_GPIO(led_t LDx)
{
	HAL_GPIO_TogglePin(GPIOC, LDx);
}

/**
 * @brief GPIO Toggle Led function
 * @param led_t LDx
 * @reval None
 */
buttonStatus_t readButton_GPIO(void)
{
	return HAL_GPIO_ReadPin(GPIOC, BT_Pin);
}

