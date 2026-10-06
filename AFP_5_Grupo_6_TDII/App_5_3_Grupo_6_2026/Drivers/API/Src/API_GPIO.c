/**
 * @file    API_GPIO.c
 * @author  Mayol Federico (UTN FRT) - Grupo 6
 * @brief   Driver para el manejo de los LEDs y el pulsador de la placa.
 * @version 1.0
 * @date    2026
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_GPIO.h"

/* Defines -------------------------------------------------------------------*/
#define LEDS_GPIO_Port LD1_GPIO_Port   /* En la NUCLEO-F767ZI los tres LEDs estan en GPIOB */

/* Function definition -------------------------------------------------------*/

/**
 * @brief  Inicializa los pines de la placa (codigo generado por CubeMX).
 * @param  None
 * @retval None
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/**
 * @brief  Enciende un LED.
 * @param  LDx: LED a encender (LED1, LED2 o LED3).
 * @retval None
 */
void writeLedOn_GPIO(led_t LDx)
{
	HAL_GPIO_WritePin(LEDS_GPIO_Port, LDx, GPIO_PIN_SET);
}

/**
 * @brief  Apaga un LED.
 * @param  LDx: LED a apagar (LED1, LED2 o LED3).
 * @retval None
 */
void writeLedOff_GPIO(led_t LDx)
{
	HAL_GPIO_WritePin(LEDS_GPIO_Port, LDx, GPIO_PIN_RESET);
}

/**
 * @brief  Invierte el estado de un LED.
 * @param  LDx: LED a conmutar (LED1, LED2 o LED3).
 * @retval None
 */
void toggleLed_GPIO(led_t LDx)
{
	HAL_GPIO_TogglePin(LEDS_GPIO_Port, LDx);
}

/**
 * @brief  Lee el pulsador de usuario, sin filtrar rebotes.
 * @param  None
 * @retval true si esta presionado (activo en alto), false si esta liberado.
 */
buttonStatus_t readButton_GPIO(void)
{
	return (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET);
}
