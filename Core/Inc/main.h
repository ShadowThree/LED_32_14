/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define HC_Pin GPIO_PIN_12
#define HC_GPIO_Port GPIOB
#define HB_Pin GPIO_PIN_13
#define HB_GPIO_Port GPIOB
#define HA_Pin GPIO_PIN_14
#define HA_GPIO_Port GPIOB
#define DBI_Pin GPIO_PIN_15
#define DBI_GPIO_Port GPIOB
#define DGI_Pin GPIO_PIN_8
#define DGI_GPIO_Port GPIOA
#define DRI_Pin GPIO_PIN_9
#define DRI_GPIO_Port GPIOA
#define LAT_Pin GPIO_PIN_10
#define LAT_GPIO_Port GPIOA
#define OE_Pin GPIO_PIN_11
#define OE_GPIO_Port GPIOA
#define CLK_Pin GPIO_PIN_12
#define CLK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
