/*
 * API_debounce.h
 *  Driver antirrebote por MEF
 */
#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "API_delay.h"   // para bool_t

typedef enum {
    BUTTON_UP,        // boton suelto
    BUTTON_FALLING,   // se detecto una pulsacion, falta confirmarla
    BUTTON_DOWN,      // boton presionado
    BUTTON_RISING     // se detecto una liberacion, falta confirmarla
} debounceState_t;

void debounceFSM_init(void);                 // carga el estado inicial
void debounceFSM_update(bool_t buttonRead);  // se llama en cada vuelta del while, con la lectura del boton
void buttonPressed(void);                    // evento: pulsacion confirmada
void buttonReleased(void);                   // evento: liberacion confirmada
bool_t readKey(void);                        // true si hubo una pulsacion nueva (y se resetea)

#endif /* API_INC_API_DEBOUNCE_H_ */
