/* USER CODE BEGIN Header */
/*
 * App 1.1 - Tecnicas Digitales II - 2025
 * Secuencia de leds onboard: verde -> azul -> rojo
 * Placa: NUCLEO-F429ZI
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"   // incluye las definiciones de la HAL y de la placa

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// Estructura para guardar los datos de cada led (puerto y pin)
typedef struct {
    GPIO_TypeDef *puerto;   // puerto donde esta conectado el led (ej: GPIOB)
    uint16_t pin;           // pin del puerto (ej: GPIO_PIN_0)
} Led;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CANT_LEDS 3      // cantidad de leds de la placa
#define TIEMPO_ON 200    // tiempo encendido en ms (lo pide la consigna)
#define TIEMPO_OFF 200   // tiempo apagado en ms (lo pide la consigna)
/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
// Vector con los 3 leds de la placa, en el orden que pide la consigna
Led leds[CANT_LEDS] = {
    {GPIOB, GPIO_PIN_0},    // LED1 verde (LD1)
    {GPIOB, GPIO_PIN_7},    // LED2 azul (LD2)
    {GPIOB, GPIO_PIN_14}    // LED3 rojo (LD3)
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);       // configura el reloj del micro
static void MX_GPIO_Init(void);      // configura los pines GPIO

int main(void)
{
  HAL_Init();              // inicializa la HAL y el SysTick (base de tiempo de 1 ms)
  SystemClock_Config();    // configura el reloj del sistema
  MX_GPIO_Init();          // configura los pines de los leds como salida

  /* USER CODE BEGIN WHILE */
  while (1)   // bucle infinito, el micro repite esto para siempre
  {
    // recorro el vector de leds uno por uno
    for (int i = 0; i < CANT_LEDS; i++)
    {
      // enciendo el led actual (pongo el pin en 1)
      HAL_GPIO_WritePin(leds[i].puerto, leds[i].pin, GPIO_PIN_SET);

      // espero 200 ms con el led prendido
      HAL_Delay(TIEMPO_ON);

      // apago el led actual (pongo el pin en 0)
      HAL_GPIO_WritePin(leds[i].puerto, leds[i].pin, GPIO_PIN_RESET);

      // espero 200 ms con el led apagado antes de pasar al siguiente
      HAL_Delay(TIEMPO_OFF);
    }
    // cuando termina el for, el while vuelve a empezar desde el LED1
  }
  /* USER CODE END WHILE */
}

/* Configuracion del reloj del sistema */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};   // estructura para el oscilador
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};   // estructura para los relojes

  __HAL_RCC_PWR_CLK_ENABLE();   // habilita el reloj del modulo de energia
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  // uso el oscilador interno HSI de 16 MHz, sin PLL
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();   // si algo falla, va al manejador de errores
  }

  // configuro los relojes del sistema y de los buses
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;   // fuente: HSI
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;       // sin division
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* Configuracion de los pines GPIO de los leds */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};   // estructura de configuracion del pin

  __HAL_RCC_GPIOB_CLK_ENABLE();   // habilita el reloj del puerto B (sin esto no anda)

  // arranco con los 3 leds apagados
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14;  // los 3 pines de los leds
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;    // modo salida push-pull
  GPIO_InitStruct.Pull = GPIO_NOPULL;            // sin resistencia pull-up ni pull-down
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;   // velocidad baja alcanza para un led
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);        // aplica la configuracion al puerto B
}

/* Manejador de errores: si algo falla el programa queda aca */
void Error_Handler(void)
{
  __disable_irq();   // deshabilita las interrupciones
  while (1)          // se queda trabado para poder debuggear
  {
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif
