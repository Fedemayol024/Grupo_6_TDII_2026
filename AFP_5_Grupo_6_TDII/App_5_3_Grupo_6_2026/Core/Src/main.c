/* USER CODE BEGIN Header */
/**
 * @file    main.c
 * @author  Mayol Federico (UTN FRT) - Grupo 6
 * @brief   App 5.3: cuatro secuencias de LEDs seleccionables con el pulsador.
 * @details AFP 5 - Tecnicas Digitales II - 2026. Placa NUCLEO-F767ZI.
 *          Usa los drivers API_GPIO, API_delay y API_debounce.
 *          Cada pulsacion valida pasa a la secuencia siguiente:
 *            Secuencia 1: LED1 -> LED2 -> LED3, T_ON encendido y T_OFF apagado.
 *            Secuencia 2: los tres LEDs parpadean juntos cada T_SEQ2.
 *            Secuencia 3: cada LED parpadea con su propio tiempo.
 *            Secuencia 4: LED1 y LED3 juntos y LED2 en oposicion, cada T_SEQ4.
 * @version 1.0
 * @date    2026
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

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
#define LED1 LD1_Pin   /* LED verde */
#define LED2 LD2_Pin   /* LED azul  */
#define LED3 LD3_Pin   /* LED rojo  */

#define CANT_LEDS       3   /* Cantidad de LEDs del vector LEDS */
#define CANT_SECUENCIAS 4   /* Cantidad de secuencias seleccionables */

/* Tiempos en ms */
#define T_ON        150   /* Secuencia 1: tiempo encendido */
#define T_OFF       150   /* Secuencia 1: tiempo apagado */
#define T_SEQ2      300   /* Secuencia 2: alternancia de los tres LEDs */
#define T_SEQ3_LED1 100   /* Secuencia 3: alternancia del LED1 */
#define T_SEQ3_LED2 300   /* Secuencia 3: alternancia del LED2 */
#define T_SEQ3_LED3 600   /* Secuencia 3: alternancia del LED3 */
#define T_SEQ4      150   /* Secuencia 4: alternancia */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma location=0x2007c000
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
#pragma location=0x2007c0a0
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

#elif defined ( __CC_ARM )  /* MDK ARM Compiler */

__attribute__((at(0x2007c000))) ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
__attribute__((at(0x2007c0a0))) ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

#elif defined ( __GNUC__ ) /* GNU Compiler */

ETH_DMADescTypeDef DMARxDscrTab[ETH_RX_DESC_CNT] __attribute__((section(".RxDecripSection"))); /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef DMATxDscrTab[ETH_TX_DESC_CNT] __attribute__((section(".TxDecripSection")));   /* Ethernet Tx DMA Descriptors */
#endif

ETH_TxPacketConfig TxConfig;

ETH_HandleTypeDef heth;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */
led_t LEDS[CANT_LEDS] = {LED1, LED2, LED3};   /* Vector de LEDs */

int8_t indiceLed = 0;            /* LED actual dentro de LEDS */
bool_t ledEncendido = true;      /* Fase del LED actual en la secuencia 1 */
uint8_t secuenciaActual = 0;     /* Secuencia en ejecucion: 0 a CANT_SECUENCIAS - 1 */

delay_t delayLeds;               /* Retardo principal (secuencias 1, 2 y 4) */
delay_t delayLed1;               /* Retardo del LED1 (secuencia 3) */
delay_t delayLed2;               /* Retardo del LED2 (secuencia 3) */
delay_t delayLed3;               /* Retardo del LED3 (secuencia 3) */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
/* USER CODE BEGIN PFP */
void iniciarSecuencia(void);
void actualizarSecuencia(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/**
 * @brief  Apaga los LEDs y deja lista la secuencia indicada por secuenciaActual.
 * @param  None
 * @retval None
 */
void iniciarSecuencia(void)
{
	for (indiceLed = 0; indiceLed < CANT_LEDS; indiceLed++)
	{
		writeLedOff_GPIO(LEDS[indiceLed]);
	}
	indiceLed = 0;

	switch (secuenciaActual)
	{
	case 0:   /* Secuencia 1: arranca con LED1 encendido */
		writeLedOn_GPIO(LEDS[indiceLed]);
		ledEncendido = true;
		delayInit(&delayLeds, T_ON);
		break;

	case 1:   /* Secuencia 2 */
		delayInit(&delayLeds, T_SEQ2);
		break;

	case 2:   /* Secuencia 3 */
		delayInit(&delayLed1, T_SEQ3_LED1);
		delayInit(&delayLed2, T_SEQ3_LED2);
		delayInit(&delayLed3, T_SEQ3_LED3);
		break;

	case 3:   /* Secuencia 4: LED1 y LED3 encendidos, LED2 apagado */
		writeLedOn_GPIO(LED1);
		writeLedOn_GPIO(LED3);
		delayInit(&delayLeds, T_SEQ4);
		break;

	default:
		secuenciaActual = 0;
		break;
	}
}

/**
 * @brief  Ejecuta un paso de la secuencia actual. No bloquea.
 * @param  None
 * @retval None
 */
void actualizarSecuencia(void)
{
	switch (secuenciaActual)
	{
	case 0:   /* Secuencia 1: un LED por vez, T_ON encendido y T_OFF apagado */
		if (delayRead(&delayLeds))
		{
			if (ledEncendido)
			{
				writeLedOff_GPIO(LEDS[indiceLed]);
				ledEncendido = false;
				delayWrite(&delayLeds, T_OFF);
			}
			else
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
		break;

	case 1:   /* Secuencia 2: los tres LEDs parpadean juntos */
		if (delayRead(&delayLeds))
		{
			toggleLed_GPIO(LED1 | LED2 | LED3);
		}
		break;

	case 2:   /* Secuencia 3: cada LED con su propio tiempo */
		if (delayRead(&delayLed1))
		{
			toggleLed_GPIO(LED1);
		}
		if (delayRead(&delayLed2))
		{
			toggleLed_GPIO(LED2);
		}
		if (delayRead(&delayLed3))
		{
			toggleLed_GPIO(LED3);
		}
		break;

	case 3:   /* Secuencia 4: LED1 y LED3 juntos, LED2 en oposicion */
		if (delayRead(&delayLeds))
		{
			toggleLed_GPIO(LED1 | LED2 | LED3);
		}
		break;

	default:
		secuenciaActual = 0;
		iniciarSecuencia();
		break;
	}
}
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
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  /* USER CODE BEGIN 2 */
  debounceFSM_init();
  iniciarSecuencia();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    /* 1. Pulsador: se filtra con la MEF antirrebote */
    debounceFSM_update(readButton_GPIO());

    /* 2. Cada pulsacion valida pasa a la secuencia siguiente */
    if (readKey())
    {
      secuenciaActual++;
      if (secuenciaActual >= CANT_SECUENCIAS)
      {
        secuenciaActual = 0;
      }
      iniciarSecuencia();
    }

    /* 3. Secuencia de LEDs, sin bloquear*/
    actualizarSecuencia();
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
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

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
