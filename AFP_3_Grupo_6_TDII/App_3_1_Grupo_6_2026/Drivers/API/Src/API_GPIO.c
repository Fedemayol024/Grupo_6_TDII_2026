/*
 * API_GPIO.c
 *
 *  Created on: Oct 5, 2026
 *      Author: santi
 */


#include "main.h"       // trae la HAL y los nombres LD1_Pin, GPIOB, etc.
#include "API_GPIO.h"   // mi propio header
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}
// prende el led que le paso
void writeLedOn_GPIO(led_t LDx)
{
    HAL_GPIO_WritePin(GPIOB, LDx, 1);
}
void writeLedOff_GPIO(led_t LDx)
{
    HAL_GPIO_WritePin(GPIOB, LDx, 0);
}
void toggleLed_GPIO(led_t LDx)
{
	 HAL_GPIO_TogglePin(GPIOB, LDx);   // invierte: 1→0 o 0→1
}
// lee el boton azul: devuelve true si esta apretado
buttonStatus_t readButton_GPIO(void)
{
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13); //leé el pin 13 del puerto C y devolvé lo que te dé
;
}

