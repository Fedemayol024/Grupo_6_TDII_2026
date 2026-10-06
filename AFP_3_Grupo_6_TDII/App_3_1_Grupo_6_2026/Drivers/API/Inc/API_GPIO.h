#include <stdint.h>
#include <stdbool.h>               // ← para usar bool (true / false)

typedef uint16_t led_t;

typedef bool buttonStatus_t;       // ← el boton esta apretado (true) o no (false)

void MX_GPIO_Init(void);
void writeLedOn_GPIO(led_t LDx);
void writeLedOff_GPIO(led_t LDx);
void toggleLed_GPIO(led_t LDx);

buttonStatus_t readButton_GPIO(void);   // ← lee el boton
