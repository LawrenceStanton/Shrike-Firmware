/**
  ******************************************************************************
  * @file           : TPS62140.h
  * @brief          : Header for TPS62140.c file.
  * @author			: Lawrence Stanton
  * @revised		: Oct 10, 2020
  ******************************************************************************
  * @attention
  *
  * © LD Stanton 2020
  * All rights reserved.
  *
  * This software component is licensed by LD Stanton. Please refer to the accompanying
  * LICENCE file for details. Use outside of the license is prohibited except for
  * exclusive use by the University of Cape Town for degree-granting activities.
  ******************************************************************************
  */

/** Configuration
 * 	This file requires inclusion of the STM32 HAL Libraries
 *
 * 	Please define the following:
 *
 * 		1. SMPS_EN_GPIO_Port, 	 SMPS_EN_GPIO_Pin		(Enable Line)
 * 		2. SMPS_BOOST_GPIO_Port, SMPS_BOOST_GPIO_Pin	(DEF Line)
 * 		3. SMPS_SENCE_GPIO_Port, SMPS_SENCE_GPIO_Pin	(FSW/PG Line)
 *	Defaults are defined below.
 */
#ifndef TPS62140_H_
#define TPS62140_H_


/* Public Includes */
#include"Shrike.h"

/* Begin Public Defines */

/* Begin Default Pin Definitions */
#ifndef SMPS_EN_Pin
	#define SMPS_EN_Pin 			GPIO_PIN_0
#endif
#ifndef SMPS_EN_GPIO_Port
	#define SMPS_EN_GPIO_Port 		GPIOA
#endif
#ifndef SMPS_BOOST_GPIO_Pin
	#define SMPS_BOOST_Pin 			GPIO_PIN_1
#endif
#ifndef SMPS_BOOST_GPIO_Port
	#define SMPS_BOOST_GPIO_Port 	GPIOA
#endif
#ifndef SMPS_SENCE_GPIO_Pin
	#define SMPS_SENCE_Pin 			GPIO_PIN_5
#endif
#ifndef SMPS_SECNCE_GPIO_Port
	#define SMPS_SENCE_GPIO_Port 	GPIOA
#endif


#define SMPS_SENCE_ADC_THRESHOLD 	80
/* End Public Defines */


/* Begin Public Typedefs */
typedef enum {
	TPS62140_FREQUENCY_DEFAULT,
	TPS62140_FREQUENCY_HIGH
} TPS62140_Frequency;


typedef enum {
	TPS62140_SMPS_SENCE_ANALOGUE,
	TPS62140_SMPS_SENCE_OPEN_DRAIN
} TPS62140_SMPS_SENCE_STATE;

/* End Public Typedefs */


/* Begin Public Function Prototypes */
void TPS62140_config(ADC_HandleTypeDef * hadc_sence);

void TPS62140_PowerOn(void);
void TPS62140_PowerOff(void);
void TPS62140_PowerToggle(void);

void TPS62140_BoostOn(void);
void TPS62140_BoostOff(void);
void TPS62140_BoostToggle(void);

void TPS62140_SetFrequency(TPS62140_Frequency frequency);

void TPS62140_SetSenceState(TPS62140_SMPS_SENCE_STATE state);

bool TPS62140_PowerGood(void);

/* End Public Function Prototypes */


#endif /* SHRIKE_DRIVER_TPS62140_H_ */


/*** END OF FILE ***/
