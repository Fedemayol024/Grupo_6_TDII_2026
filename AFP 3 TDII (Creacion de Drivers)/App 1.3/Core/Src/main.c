/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_GPIO.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int Contador;

#define LED1 led_verde_Pin
#define LED2 led_azul_Pin
#define LED3 led_rojo_Pin

uint32_t tiempo_led1 = 0;
uint32_t tiempo_led2 = 0;
uint32_t tiempo_led3 = 0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;
PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
//void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
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

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

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
  MX_USB_OTG_FS_PCD_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
Reinicio:
HAL_GPIO_WritePin(led_verde_GPIO_Port, led_verde_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(led_azul_GPIO_Port, led_azul_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(led_rojo_GPIO_Port, led_rojo_Pin, GPIO_PIN_RESET);
  Contador = 0; //Reinicia el valor del contador.
    while (1)
    {
    	while (ReadButton_GPIO()==GPIO_PIN_RESET && Contador==0)
    	{

    	}
    	if(Contador==0){Contador  ++;}
        if(Contador==1)
        {
        	ToggleLed_GPIO(LED1);
        	HAL_Delay(150);
        	ToggleLed_GPIO(LED2);
        	HAL_Delay(150);
        	ToggleLed_GPIO(LED3);
        	HAL_Delay(150);
        	ToggleLed_GPIO(LED1);
            HAL_Delay(150);
            ToggleLed_GPIO(LED2);
            HAL_Delay(150);
            ToggleLed_GPIO(LED3);
            HAL_Delay(150);
            uint32_t tiempo_inicio = HAL_GetTick(); // Tomamos la "foto" del tiempo actual
            while ((HAL_GetTick() - tiempo_inicio) < 1000) // Corre en bucle por exactamente 3000 ms
                      {
                          if (ReadButton_GPIO() == GPIO_PIN_SET)
                          {
                            Contador++;    // Sumamos 1 al Contador de la placa
                            HAL_Delay(300); // Anti Rebote.
                          }
                      }
        }
        if(Contador==2)
                {
        	ToggleLed_GPIO(LED1);
        	ToggleLed_GPIO(LED2);
        	ToggleLed_GPIO(LED3);
                	HAL_Delay(300);
            ToggleLed_GPIO(LED1);
            ToggleLed_GPIO(LED2);
            ToggleLed_GPIO(LED3);
                    HAL_Delay(300);
            uint32_t tiempo_inicio = HAL_GetTick(); // Tomamos la "foto" del tiempo actual
                    while ((HAL_GetTick() - tiempo_inicio) < 1000) // Corre en bucle por exactamente 3000 ms
                              {
                                  if (ReadButton_GPIO() == GPIO_PIN_SET)
                                  {
                                    Contador++;    // Sumamos 1 al Contador de la placa
                                    HAL_Delay(300); // Anti Rebote.
                                  }
                              }
                }
        if(Contador == 3)
        {
            // 1. Inicializamos los cronómetros para los 3 segundos y para cada LED
            uint32_t tiempo_inicio = HAL_GetTick();
            uint32_t tiempo_led1   = tiempo_inicio;
            uint32_t tiempo_led2   = tiempo_inicio;
            uint32_t tiempo_led3   = tiempo_inicio;

            // 2. Ventana de análisis de 3000 ms
            while ((HAL_GetTick() - tiempo_inicio) < 3000)
            {
                uint32_t ahora = HAL_GetTick();

                // LED1: Alternancia cada 100 ms
                if (ahora - tiempo_led1 >= 100) {
                    tiempo_led1 = ahora;
                    ToggleLed_GPIO(LED1);
                }
                // LED2: Alternancia cada 300 ms
                if (ahora - tiempo_led2 >= 300) {
                    tiempo_led2 = ahora;
                    ToggleLed_GPIO(LED2);
                }
                // LED3: Alternancia cada 600 ms
                if (ahora - tiempo_led3 >= 600) {
                    tiempo_led3 = ahora;
                    ToggleLed_GPIO(LED3);
                }
            }
            WriteLedOff_GPIO(LED1);
            WriteLedOff_GPIO(LED2);
            WriteLedOff_GPIO(LED3);
        }
                    uint32_t tiempo_inicio = HAL_GetTick(); // Tomamos la "foto" del tiempo actual
                    while ((HAL_GetTick() - tiempo_inicio) < 1000) // Corre en bucle por exactamente 3000 ms
                              {
                                  if (ReadButton_GPIO() == GPIO_PIN_SET)
                                  {
                                    Contador++;    // Sumamos 1 al Contador de la placa
                                    HAL_Delay(300); // Anti Rebote.
                                  }
                              }
                    if(Contador == 4)
                    {
                        // LED1 (Verde) y LED3 (Rojo) ENCENDIDOS. LED2 (Azul) APAGADO.
                    	WriteLedOn_GPIO(LED1);
                    	WriteLedOn_GPIO(LED3);
                    	WriteLedOff_GPIO(LED2);

                        // 2. Inicializamos cronómetros
                        uint32_t tiempo_inicio = HAL_GetTick();
                        uint32_t tiempo_led    = tiempo_inicio; // Un solo cronómetro para los tres leds ya que van al mismo ritmo

                        uint8_t boton_listo = 1; // Flag para contar un solo clic por pulsación

                        // 3. Ventana de análisis de 3000 ms
                        while ((HAL_GetTick() - tiempo_inicio) < 3000)
                        {
                            uint32_t ahora = HAL_GetTick();
                            if (ahora - tiempo_led >= 150)
                            {
                                tiempo_led = ahora;

                                // Truco: Al hacerle toggle a los tres juntos, los que estaban en 1 pasan a 0
                                // y el que estaba en 0 pasa a 1. Se mantiene la inversión perfecta.
                                ToggleLed_GPIO(LED1);
                                ToggleLed_GPIO(LED2);
                                ToggleLed_GPIO(LED3);
                            }

                            if (ReadButton_GPIO() == GPIO_PIN_SET)
                            {
                                if (boton_listo)
                                {
                                    Contador++;       // Sumamos al Contador de la placa
                                    boton_listo = 0;  // Bloqueamos para evitar falsos conteos
                                }
                            }
                            else
                            {
                                boton_listo = 1; // Queda listo para el próximo toque al soltarlo
                            }

                            HAL_Delay(10); // Margen de estabilidad para el bucle
                        }
                    }
if (Contador>=5)
{goto Reinicio;}



                }
    }
    /* USER CODE END WHILE */
  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

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
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
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
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

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
