#ifndef API_DELAY_H
#define API_DELAY_H

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t tick_t;

// Estructura que guarda la información de cada "cronómetro"
typedef struct {
    tick_t startTime;
    tick_t duration;
    bool running;
} delay_t;

void delayInit(delay_t * delay, tick_t duration);
bool delayRead(delay_t * delay);
void delayWrite(delay_t * delay, tick_t duration);

#endif
