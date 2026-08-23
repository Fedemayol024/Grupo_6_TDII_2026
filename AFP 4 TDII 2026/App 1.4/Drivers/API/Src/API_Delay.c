/**********************
 * API_GPIO.c
 *
 *  Created on: Aug 20, 2026
 *      Author: emalu
 *********************/

/*Includes*************************************/
#include "main.h"
#include "API_Delay.h"

/*Defines****************************************/

/*Declaration of variables**************************/
//Valores esperados para duration: 100 | 250 | etc

/*Function definition********************************/
/**
 * @brief Initialization Delay Function
 * @param delay_t delay, tick_t duration
 * @reval None
 */
void delayInit(delay_t *delay, tick_t duration)
{
delay->duration=duration;
delay->running=false;
}

/**
 * @brief Control Delay Function
 * @param delay_t delay
 * @reval bool_t
 */
bool_t delayRead(delay_t *delay)
{
	if(!delay->running)
	{
		delay->running=true;
		delay->startTime=HAL_GetTick();
		return false;
	}
	else
	{
		if((HAL_GetTick() - delay->startTime)>=delay->duration)
		{
			delay->running=false;
			return true;
		}
		else
			return false;
	}
}

/**
 * @brief Change Delay Time
 * @param delay_t delay, tick_t duration
 * @reval None
 */
void delayWrite(delay_t *delay, tick_t duration)
{
	delay->duration=duration;
}
