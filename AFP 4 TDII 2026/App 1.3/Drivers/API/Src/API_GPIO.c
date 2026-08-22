/*
 * API_GPIO.c
 *
 *  Created on: 09.08.2026
 *      Author: fedem
 */
/* API_GPIO.c */
#include "main.h"
#include "API_GPIO.h"

void WriteLedOn_GPIO(led_t LDx)
{
    HAL_GPIO_WritePin(GPIOB, LDx, GPIO_PIN_SET);
}

void WriteLedOff_GPIO(led_t LDx)
{
    HAL_GPIO_WritePin(GPIOB, LDx, GPIO_PIN_RESET);
}

void ToggleLed_GPIO(led_t LDx)
{
    HAL_GPIO_TogglePin(GPIOB, LDx);
}

buttonStatus_t ReadButton_GPIO(void)
{
    // Comparamos el estado del pin y devolvemos true o false
    if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET) {
        return true;
    }
    return false;
}
