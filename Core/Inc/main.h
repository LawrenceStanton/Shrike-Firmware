/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

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
#define SMPS_EN_Pin GPIO_PIN_0
#define SMPS_EN_GPIO_Port GPIOA
#define SMPS_BOOST_Pin GPIO_PIN_1
#define SMPS_BOOST_GPIO_Port GPIOA
#define RES_EXT_Pin GPIO_PIN_4
#define RES_EXT_GPIO_Port GPIOA
#define MODULE_SENCE_Pin GPIO_PIN_5
#define MODULE_SENCE_GPIO_Port GPIOA
#define MODULE_VEXT_SENCE_Pin GPIO_PIN_6
#define MODULE_VEXT_SENCE_GPIO_Port GPIOA
#define MODULE_DTR_Pin GPIO_PIN_7
#define MODULE_DTR_GPIO_Port GPIOA
#define MODULE_RI_Pin GPIO_PIN_0
#define MODULE_RI_GPIO_Port GPIOB
#define MODULE_RI_EXTI_IRQn EXTI0_1_IRQn
#define MODULE_DCD_Pin GPIO_PIN_1
#define MODULE_DCD_GPIO_Port GPIOB
#define MODULE_DCD_EXTI_IRQn EXTI0_1_IRQn
#define MODULE_RFTXMON_Pin GPIO_PIN_2
#define MODULE_RFTXMON_GPIO_Port GPIOB
#define MODULE_RFTXMON_EXTI_IRQn EXTI2_3_IRQn
#define MODULE_EN_Pin GPIO_PIN_15
#define MODULE_EN_GPIO_Port GPIOA
#define WKUP_Pin GPIO_PIN_5
#define WKUP_GPIO_Port GPIOB
#define EEPROM_WC_Pin GPIO_PIN_7
#define EEPROM_WC_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
