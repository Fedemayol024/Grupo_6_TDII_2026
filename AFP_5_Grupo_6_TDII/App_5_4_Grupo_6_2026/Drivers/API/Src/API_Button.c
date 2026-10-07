/*
 * Driver_Button.c
 *
 *  Created on: Sep 29, 2026
 *      Author: emalu
 */


#include <API_Button.h>
#include "main.h"

/*Defines****************************************/
enum state
{
	Inicializacion,
	Inactivo,
	Activo_Espera,
	Activo,
	Inactivo_Espera
};
/*Declaration of variables**************************/
//Valores esperados para duration: 20 | 30 | etc
tick_t duration=30;
buttonStatus_t EAC;
delay_t delay_press;
/*Function definition********************************/
/**
 * @brief Initialization Delay Function
 * @param delay_t delay, tick_t duration
 * @reval None
 */
void init_Time_Button_t(button_t *states_t)
{
		states_t->duration=duration;
		states_t->state=Inactivo;
		states_t->press=false;
}

void PressButton(button_t *states_t)
{
	switch (states_t->state)
	{
	case Inactivo: caseInactivo(states_t); break;
	case Activo_Espera:caseActivo_Espera(states_t); break;
	case Activo: caseActivo(states_t); break;
	case Inactivo_Espera: caseInactivo_Espera(states_t); break;
	default: init_Time_Button_t(states_t); break;
	}
}


void caseInactivo(button_t *states_t)
{
	if(!readButton_GPIO())
	{
		states_t->state=Activo_Espera;
		delayInit(&delay_press, states_t->duration);
		states_t->press=false;
	}
	else
		states_t->press=false;
}
void caseActivo_Espera(button_t *states_t)
{
	if(delayRead(&delay_press))
	{
	if (!readButton_GPIO())
	{
		states_t->state=Activo;
		states_t->press=true;
	}
	else
	{
		states_t->state=Inactivo;
		states_t->press=false;
	}
	}
}
void caseActivo(button_t *states_t)
{
	if(!readButton_GPIO())
		states_t->press=false;
	else
	{
		states_t->state=Inactivo_Espera;
		states_t->press=false;
	}
}
void caseInactivo_Espera(button_t *states_t)
{
	if(delayRead(&delay_press))
	{
	if(!readButton_GPIO())
	{
		states_t->state=Activo;
		states_t->press=false;
	}
	else
	{
		states_t->state=Inactivo;
		states_t->press=false;
	}
	}
}

