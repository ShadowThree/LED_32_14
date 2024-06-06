/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dbger.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED_DELAY_US(us)		do {counter = us; HAL_TIM_Base_Start_IT(&htim4); while(counter);} while(0)

#define CLK_LOW		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET)
#define CLK_HIGH	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET)

#define LAT_LOW		HAL_GPIO_WritePin(LAT_GPIO_Port, LAT_Pin, GPIO_PIN_RESET)
#define LAT_HIGH	HAL_GPIO_WritePin(LAT_GPIO_Port, LAT_Pin, GPIO_PIN_SET)

#define OE_LOW		HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_RESET)
#define OE_HIGH		HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_SET)

#define DRI_LOW		HAL_GPIO_WritePin(DRI_GPIO_Port, DRI_Pin, GPIO_PIN_RESET)
#define DRI_HIGH	HAL_GPIO_WritePin(DRI_GPIO_Port, DRI_Pin, GPIO_PIN_SET)
#define DGI_LOW		HAL_GPIO_WritePin(DGI_GPIO_Port, DGI_Pin, GPIO_PIN_RESET)
#define DGI_HIGH	HAL_GPIO_WritePin(DGI_GPIO_Port, DGI_Pin, GPIO_PIN_SET)
#define DBI_LOW		HAL_GPIO_WritePin(DBI_GPIO_Port, DBI_Pin, GPIO_PIN_RESET)
#define DBI_HIGH	HAL_GPIO_WritePin(DBI_GPIO_Port, DBI_Pin, GPIO_PIN_SET)

// CLK	A
#define HA_LOW		HAL_GPIO_WritePin(HA_GPIO_Port, HA_Pin, GPIO_PIN_RESET)
#define HA_HIGH		HAL_GPIO_WritePin(HA_GPIO_Port, HA_Pin, GPIO_PIN_SET)
// RK(BK) B
#define HB_LOW		HAL_GPIO_WritePin(HB_GPIO_Port, HB_Pin, GPIO_PIN_RESET)
#define HB_HIGH		HAL_GPIO_WritePin(HB_GPIO_Port, HB_Pin, GPIO_PIN_SET)
// SDI C
#define HC_LOW		HAL_GPIO_WritePin(HC_GPIO_Port, HC_Pin, GPIO_PIN_RESET)
#define HC_HIGH		HAL_GPIO_WritePin(HC_GPIO_Port, HC_Pin, GPIO_PIN_SET)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define LINE_NUM		14		// 14 lines
#define CLOUMN_NUM	32		// 32 cloumns
#define COLOR_NUM		3			// R G B

uint32_t color[LINE_NUM][COLOR_NUM];

extern volatile uint32_t counter; 
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void set_line(uint8_t line);
void set_data(uint8_t line);
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
	LOG_INIT();
	LOG_DBG("\n\nLED_32_14 start\n");
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
#if 0	// test delay us
	for(uint8_t i = 0; i < 10; i++) {
		LED_DELAY_US(1000000);
	}
#endif

	// color value init
	for(uint8_t i = 0; i < LINE_NUM; i++) {
		color[i][0] = 0xFFFFFFFF;
		color[i][1] = 0;
		color[i][2] = 0;
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
#if 1		// LED driver
		for(uint8_t i = 0; i < LINE_NUM; i++) {
			set_line(i);
			set_data(i);
		}
#else
		HAL_Delay(1000);
		LOG_DBG("delay 1s by HAL\n");
#endif
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void set_line(uint8_t line)
{
	HB_LOW;
	for(uint8_t i = 0; i < LINE_NUM; i++) {
		HA_LOW;
		(i == line) ? HC_HIGH : HC_LOW;
		LED_DELAY_US(1);
		HA_HIGH;
		LED_DELAY_US(1);
	}
	HB_HIGH;
}

void set_data(uint8_t line)
{
	for(uint8_t i = 0; i < CLOUMN_NUM; i++) {
		CLK_LOW;
		(color[line][0] & (1 << i)) ? DRI_HIGH : DRI_LOW;
		(color[line][1] & (1 << i)) ? DGI_HIGH : DGI_LOW;
		(color[line][2] & (1 << i)) ? DBI_HIGH : DBI_LOW;
		LED_DELAY_US(1);
		CLK_HIGH;
		LED_DELAY_US(1);
	}
	LAT_HIGH;
	LED_DELAY_US(1);
	LAT_LOW;
	OE_LOW;
	LED_DELAY_US(80);		// less than 100
	OE_HIGH;
}
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

#ifdef  USE_FULL_ASSERT
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
