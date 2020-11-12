/**
  ******************************************************************************
  * @file           : M66.c
  * @brief          : Source File
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

/* Begin Private Includes */
#include "Shrike.h"
#include <string.h>

/* End Private Includes */

/* Begin Private Defines */
#define MODULE_STARTUP_TIME_ALLOWANCE 5000
#define MODULE_STARTUP_CHECK_INTERVAL 100

/* End Private Defines */

/* Begin Private Typedefs */


/* End Private Typedefs */

/* Begin Private Function Prototypes */


/* End Private Function Prototypes */

/* Begin Private Variables */
UART_HandleTypeDef * huart;

/* End Private Variables */

/* Begin Source Code */
/**
 * @brief	Configures variables for the M66.
 * @retval	None
 */
void M66_Config(UART_HandleTypeDef * huart_M66){
	huart = huart_M66;
}

/**
 * @brief	Powers on the M66.
 * @retval	None
 */
void M66_PowerOn(void){
	TPS62140_PowerOn();
	HAL_Delay(100);
	assert_param(TPS62140_PowerGood() == TRUE);

	HAL_GPIO_WritePin(MODULE_EN_GPIO_Port, MODULE_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(5000);
	while(HAL_GPIO_ReadPin(MODULE_VEXT_SENCE_GPIO_Port, MODULE_VEXT_SENCE_Pin) == GPIO_PIN_RESET) HAL_Delay(10);
	HAL_Delay(3000);

	int maxChecks = MODULE_STARTUP_TIME_ALLOWANCE/MODULE_STARTUP_CHECK_INTERVAL;
	for(int i = 0; i < maxChecks; i++){
		if(M66_IsOn() == TRUE) break;
		else HAL_Delay(MODULE_STARTUP_CHECK_INTERVAL);
	}

	HAL_GPIO_WritePin(MODULE_EN_GPIO_Port, MODULE_EN_Pin, GPIO_PIN_RESET);
	assert_param(M66_IsOn() == TRUE);
}

/**
 * @brief	Powers off the M66 via the PWRKEY
 * @retval	None
 */
void M66_PowerOffHard(void){
	HAL_GPIO_WritePin(MODULE_EN_GPIO_Port, MODULE_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);

	while(HAL_GPIO_ReadPin(MODULE_VEXT_SENCE_GPIO_Port, MODULE_VEXT_SENCE_Pin) == GPIO_PIN_SET);

	TPS62140_PowerOff();
	assert_param(M66_IsOn() == FALSE);
}

/**
 * @brief	Powers off the module via UART.
 * @retval	None
 */
void M66_PowerOffSoft(void);

/**
 * Determines if the module is powered on.
 */
bool M66_IsOn(){
	uint8_t AT[] = "AT\n\r";
	uint8_t OK[] = "\n\rOK\n\n";
	uint8_t res[sizeof(OK)];

	HAL_UART_Transmit(huart, AT, sizeof(AT), HAL_MAX_DELAY);
	HAL_UART_Receive(huart, res, sizeof(res), HAL_MAX_DELAY);
	return strcmp((const char *)OK, (const char *)res) ? TRUE : FALSE;
}


/* End Source Code */


/*** END OF FILE ***/
