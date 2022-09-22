/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TFT_CS_Pin GPIO_PIN_1
#define TFT_CS_GPIO_Port GPIOB
#define TFT_RST_Pin GPIO_PIN_2
#define TFT_RST_GPIO_Port GPIOB
#define TFT_DC_Pin GPIO_PIN_10
#define TFT_DC_GPIO_Port GPIOB
#define BUT_Pin GPIO_PIN_13
#define BUT_GPIO_Port GPIOB
#define RF_SET_Pin GPIO_PIN_14
#define RF_SET_GPIO_Port GPIOB
#define PIN_R_Pin GPIO_PIN_15
#define PIN_R_GPIO_Port GPIOB
#define RF_CS_Pin GPIO_PIN_8
#define RF_CS_GPIO_Port GPIOA
#define BUT2_Pin GPIO_PIN_15
#define BUT2_GPIO_Port GPIOA
#define SD_CS_Pin GPIO_PIN_3
#define SD_CS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
