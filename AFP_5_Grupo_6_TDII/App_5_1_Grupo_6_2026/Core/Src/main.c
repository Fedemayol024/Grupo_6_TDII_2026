/* USER CODE BEGIN Header */
/*
 * AFP 5 - Tecnicas Digitales II - Grupo 6 - 2026
 * App 1.1 con drivers API_GPIO, API_delay y API_debounce - Placa: NUCLEO-F429ZI
 *
 * App 1.1: Desarrolle una aplicacion que encienda y apague de manera secuencial
 * los tres leds onboard de la placa de desarrollo. La secuencia debe encender 200 ms y
 * apagar 200 ms cada led comenzando por el LED1 (Green), continuando con el LED2 (Blue) y
 * luego el LED3 (Red) para volver a iniciar con el LED1. La aplicacion debe ser de caracter
 * general, de manera que pueda extenderse a una cantidad mayor de leds con minimas modificaciones,
 * por este motivo se sugiere que use un vector para el manejo de los Leds.
 * En esta version, ademas, el pulsador pausa y reanuda la secuencia.
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "API_GPIO.h"
#include "API_delay.h"
#include "API_debounce.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED1 GPIO_PIN_0    // verde
#define LED2 GPIO_PIN_7    // azul
#define LED3 GPIO_PIN_14   // rojo
#define CANT_LEDS 3        // cuantos leds hay en el vector LEDS
#define T_ON  200          // tiempo encendido de cada led, en ms
#define T_OFF 200          // tiempo apagado de cada led, en ms
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  led_t LEDS[CANT_LEDS] = {LED1, LED2, LED3};         // vector con los leds en orden
  int8_t indiceLed = 0;                                // arranco por el primero (verde)
  bool_t ledEncendido = true;                          // arranco con el led prendido
  bool_t pausado = false;                              // la secuencia arranca andando

  delay_t delayLeds;
  delayInit(&delayLeds, T_ON);                         // arranca con el tiempo de encendido

  debounceFSM_init();                                  // MEF del boton (apaga los leds)
  writeLedOn_GPIO(LEDS[indiceLed]);                    // DESPUES prendo el primero
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  debounceFSM_update(readButton_GPIO());      // la MEF del boton, en cada vuelta

	  if (readKey())                              // hubo una pulsacion nueva?
	  {
		  pausado = !pausado;                     // pausa <-> sigue
	  }

	  if (!pausado && delayRead(&delayLeds))      // si no esta pausado y pasaron 200 ms
	  {
		  if (ledEncendido)                       // estaba prendido -> lo apago
		  {
			  writeLedOff_GPIO(LEDS[indiceLed]);
			  ledEncendido = false;
			  delayWrite(&delayLeds, T_OFF);
		  }
		  else                                    // estaba apagado -> paso al siguiente
		  {
			  indiceLed++;
			  if (indiceLed >= CANT_LEDS)
			  {
				  indiceLed = 0;
			  }
			  writeLedOn_GPIO(LEDS[indiceLed]);
			  ledEncendido = true;
			  delayWrite(&delayLeds, T_ON);
		  }
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
