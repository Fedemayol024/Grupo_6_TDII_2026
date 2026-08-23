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

/*Function definition********************************/
/**
 * @brief GPIO initialization function
 * @param None
 * @reval None
 */
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD_GPIO_Port, LD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BT_Pin */
  GPIO_InitStruct.Pin = BT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : LD_Pin */
  GPIO_InitStruct.Pin = LD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

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

