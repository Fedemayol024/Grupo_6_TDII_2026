/* USER CODE BEGIN Header */
/*
 * AFP 4 - Tecnicas Digitales II - Grupo 6 - 2025
 * App 1.1 modificada para usar el driver de retardos no bloqueantes
 * (se reemplazo el HAL_Delay por delayInit/delayRead/delayWrite)
 * Placa: NUCLEO-F429ZI
 */
/* USER CODE END Header */

#include "main.h"
#include "header.h"   // driver de delays no bloqueantes (carpeta Drivers/API)

/* USER CODE BEGIN PTD */
typedef struct {
	GPIO_TypeDef *puerto;
	uint16_t pin;
} Led;
/* USER CODE END PTD */

/* USER CODE BEGIN PD */
#define CANT_LEDS 3
#define TIEMPO_ON 200
#define TIEMPO_OFF 200
/* USER CODE END PD */

/* USER CODE BEGIN PV */
Led leds[CANT_LEDS] = {
	{ GPIOB, GPIO_PIN_0 },   // LED1 verde
	{ GPIOB, GPIO_PIN_7 },   // LED2 azul
	{ GPIOB, GPIO_PIN_14 }   // LED3 rojo
};

// variable del driver para el retardo de la secuencia de leds
delay_t retardoLeds;

// para saber en que led estamos y si esta prendido o apagado
uint8_t indiceLed = 0;
uint8_t ledEncendido = 1;   // arranca prendido, por eso el 1
/* USER CODE END PV */

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */
  // pruebas basicas del driver (punto 2 de la consigna), se dejan comentadas
  // para no interferir con la app, sirvieron para probar antes de integrar:
  //
  // delay_t delayPrueba;
  // delayInit(&delayPrueba, 500);
  // while(1){
  //     if(delayRead(&delayPrueba)){
  //         HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
  //     }
  // }

  // prendo el primer led antes de arrancar el while, y cargo el delay
  // con el tiempo de ON para que la primera vuelta funcione bien
  HAL_GPIO_WritePin(leds[indiceLed].puerto, leds[indiceLed].pin, GPIO_PIN_SET);
  delayInit(&retardoLeds, TIEMPO_ON);
  /* USER CODE END 2 */

  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // delayRead se llama todo el tiempo (no bloqueante), y devuelve
    // true recien cuando se cumplio el tiempo cargado
    if (delayRead(&retardoLeds))
    {
      if (ledEncendido)
      {
        // se cumplio el tiempo de ON -> apago el led actual
        HAL_GPIO_WritePin(leds[indiceLed].puerto, leds[indiceLed].pin, GPIO_PIN_RESET);
        ledEncendido = 0;
        delayWrite(&retardoLeds, TIEMPO_OFF);   // ahora cuento el tiempo de OFF
      }
      else
      {
        // se cumplio el tiempo de OFF -> paso al siguiente led y lo prendo
        indiceLed = (indiceLed + 1) % CANT_LEDS;
        HAL_GPIO_WritePin(leds[indiceLed].puerto, leds[indiceLed].pin, GPIO_PIN_SET);
        ledEncendido = 1;
        delayWrite(&retardoLeds, TIEMPO_ON);
      }
    }

    // como delayRead no bloquea, aca abajo podria ir cualquier otra cosa
    // (leer un pulsador, otro led, etc) y funcionaria en paralelo sin
    // esperar a que termine la secuencia de leds - esa es la ventaja
    // de usar retardos no bloqueantes en vez de HAL_Delay
  }
  /* USER CODE END WHILE */
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif
