/**
 ******************************************************************************
 * @file           : TPS62140.c
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
#include "TPS62140.h"


/* End Private Includes */

/* Begin Private Typedefs */

/* End Private Typedefs */

/* Begin Private Function Prototypes */

/* End Private Function Prototypes */

/* Begin Private Variables */
ADC_HandleTypeDef * hadc;
/* End Private Variables */


/* Begin Source Code */

/**
 * @brief 	Sets the necessary variables for operation.
 * @retval	None
 */
void TPS62140_config(ADC_HandleTypeDef * hadc_sence){
	hadc = hadc_sence;
}

/**
 * @brief	Enables the TPS62140
 * @retval	None
 */
void TPS62140_PowerOn(void) {
	HAL_GPIO_WritePin(SMPS_EN_GPIO_Port, SMPS_EN_Pin, GPIO_PIN_SET);
}

/**
 * @brief	Disables the TPS62140
 * @retval	None
 */
void TPS62140_PowerOff(void) {
	HAL_GPIO_WritePin(SMPS_EN_GPIO_Port, SMPS_EN_Pin, GPIO_PIN_RESET);
}

/**
 * @brief	Toggles the enable state of the TPS62140
 * @retval	None
 */
void TPS62140_PowerToggle(void){
	HAL_GPIO_TogglePin(SMPS_EN_GPIO_Port, SMPS_EN_Pin);
}

/**
 * @brief	Boosts the output of the TPS62140 by 5%.
 * @retval	None
 */
void TPS62140_BoostOn(void){
	HAL_GPIO_WritePin(SMPS_BOOST_GPIO_Port, SMPS_BOOST_Pin, GPIO_PIN_SET);
}

/**
 * @brief	Disables the 5% boost.
 * @retval	None
 */
void TPS62140_BoostOff(void){
	HAL_GPIO_WritePin(SMPS_BOOST_GPIO_Port, SMPS_BOOST_Pin, GPIO_PIN_RESET);
}

/**
 * @brief	Toggles the boost state.
 * @retval	None
 */
void TPS62140_BoostToggle(void){
	HAL_GPIO_TogglePin(SMPS_BOOST_GPIO_Port, SMPS_BOOST_Pin);
}

/**
 * @brief	Forces the frequency selection high or frees the device to the passive state.
 * @param	frequency: TPS62140_FREQUENCY_HIGH or TPS62140_FREQUENCY_DEFAULT
 * @retval	None
 */
void TPS62140_SetFrequency(TPS62140_Frequency frequency){
	GPIO_PinState pinState = (frequency == TPS62140_FREQUENCY_DEFAULT) ? GPIO_PIN_SET : GPIO_PIN_RESET;
	HAL_GPIO_WritePin(SMPS_SENCE_GPIO_Port, SMPS_SENCE_Pin, pinState);
}


/**
 * @brief	Changes the state of the SMPS_SENCE pin to ADC or Open Drain mode.
 * @param 	state: 	TPS62140_SMPS_SENCE_ANALOGUE or TPS62140_SMPS_SENCE_OPEN_DRAIN
 * @retval	None
 */
void TPS62140_SetSenceState(TPS62140_SMPS_SENCE_STATE state){
	if(state == TPS62140_SMPS_SENCE_OPEN_DRAIN){
		GPIO_InitTypeDef GPIO_InitStruct = {0};

		GPIO_InitStruct.Pin = SMPS_SENCE_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(SMPS_SENCE_GPIO_Port, &GPIO_InitStruct);
	}
	else if(state == TPS62140_SMPS_SENCE_ANALOGUE){
		HAL_GPIO_DeInit(SMPS_SENCE_GPIO_Port, SMPS_SENCE_Pin);

		ADC_ChannelConfTypeDef sConfig = {0};

		sConfig.Channel = ADC_CHANNEL_5;
		sConfig.Rank = ADC_REGULAR_RANK_1;
		sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
		HAL_ADC_ConfigChannel(hadc, &sConfig);
	}
}

/**
 * @brief	Reads the Power Good state of the TPS62140
 * @retval	bool: TRUE or FALSE
 * @note	Will reset frequency set to default state.
 * @note	Bus capacitance may void result if by frequency reset the result changes shortly after.
 */
bool TPS62140_PowerGood(void){

	// Reset SMPS_SENCE to Default behaviour.
	TPS62140_SetFrequency(TPS62140_FREQUENCY_DEFAULT);

	// Set SMPS_SENCE to ANALOGUE Mode
	TPS62140_SetSenceState(TPS62140_SMPS_SENCE_ANALOGUE);

	HAL_ADC_Start(hadc);												// Start ADC
	while(HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY) != HAL_OK);	// Wait for conversion
	HAL_ADC_Stop(hadc);													// Stop ADC
	uint32_t adcValue = HAL_ADC_GetValue(hadc);							// Read result

	// Set SMPS_SENCE to OPEN_DRAIN Mode.
	TPS62140_SetSenceState(TPS62140_SMPS_SENCE_OPEN_DRAIN);

	// Return compare result to known threshold.
	return adcValue > SMPS_SENCE_ADC_THRESHOLD ? TRUE : FALSE;
}

/* End Source Code */

/*** END OF FILE ***/
