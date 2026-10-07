/*
 * API_debounce.c
 *  Driver antirrebote por MEF
 */
#include "main.h"           // HAL y nombres LD1_Pin, LD3_Pin
#include "API_debounce.h"
#include "API_delay.h"
#include "API_GPIO.h"

#define DEBOUNCE_DELAY 40   // tiempo de antirrebote en ms

/* ---- Privado: solo se ve en este archivo ---- */
static debounceState_t actualState;      // estado actual de la MEF
static delay_t debounceDelay;            // delay de 40 ms
static bool_t fallingEdge = false;       // true cuando hubo una pulsacion nueva


/* ---- Funciones publicas ---- */
void debounceFSM_init(void)
{
    actualState = BUTTON_UP;
    delayInit(&debounceDelay, DEBOUNCE_DELAY);
    writeLedOff_GPIO(LD1_Pin);
    writeLedOff_GPIO(LD2_Pin);
    writeLedOff_GPIO(LD3_Pin);
    fallingEdge = false;
}

void debounceFSM_update(bool_t buttonRead)
{
    switch (actualState)
    {
    case BUTTON_UP:
        if (buttonRead == true)
        {
            actualState = BUTTON_FALLING;
            delayRead(&debounceDelay);
        }
        break;

    case BUTTON_FALLING:
        if (delayRead(&debounceDelay))
        {
            if (buttonRead == true)
            {
                actualState = BUTTON_DOWN;
                fallingEdge = true;          // aviso que hubo una pulsacion
                buttonPressed();
            }
            else
            {
                actualState = BUTTON_UP;
            }
        }
        break;

    case BUTTON_DOWN:
        if (buttonRead == false)
        {
            actualState = BUTTON_RISING;
            delayRead(&debounceDelay);
        }
        break;

    case BUTTON_RISING:
        if (delayRead(&debounceDelay))
        {
            if (buttonRead == false)
            {
                actualState = BUTTON_UP;
                buttonReleased();
            }
            else
            {
                actualState = BUTTON_DOWN;
            }
        }
        break;

    default:
        debounceFSM_init();
        break;
    }
}

bool_t readKey(void)
{
    if (fallingEdge)            // hubo una pulsacion nueva?
    {
        fallingEdge = false;    // la "consumo" para que no se lea dos veces
        return true;
    }
    return false;
}

/* ---- Eventos (vacios: en esta app los leds los maneja la secuencia) ---- */
void buttonPressed(void)
{

}

void buttonReleased(void)
{

}
