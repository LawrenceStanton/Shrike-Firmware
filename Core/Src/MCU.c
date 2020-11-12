/**
  ******************************************************************************
  * @file           : MCU.c
  * @brief          : Source File
  * @author			: Lawrence Stanton
  * @revised		: Nov 12, 2020
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
#include "MCU.h"
#include "TPS62140.h"
#include "M66.h"
#include <string.h>
/* End Private Includes */

/* Begin Private Defines */
#define EXTERN_RX_BUFFER_DEFAULT_SIZE 32

/* End Private Defines */

/* Begin Private Typedefs */


/* End Private Typedefs */

/* Begin Private Function Prototypes */
static void resetExternBuffer(void);
static void pushExternBuffer(uint8_t);

static void decodeCommand(void);
static void forwardMessage(void);

/* End Private Function Prototypes */

/* Begin Private Variables */
static UART_HandleTypeDef * huart_extern;
static UART_HandleTypeDef * huart_module;

static uint8_t Extern_Rx_Buffer[EXTERN_RX_BUFFER_DEFAULT_SIZE];	// External Command Receive Buffer
static uint8_t Extern_Rx_Buffer_Index = 0;
static uint8_t Rx_Prev = '\0';
bool command_start = FALSE;

static const uint8_t cr = '\r';


/* End Private Variables */

/* Begin Source Code */

/**
 * @brief	Configures uart handles and resets the External Buffer.
 * @param 	huart_ext	External UART handle
 * @param 	huart_mod	Module UART handle
 */
void MCU_config(UART_HandleTypeDef * huart_ext, UART_HandleTypeDef * huart_mod){
	huart_extern = huart_ext;
	huart_module = huart_mod;

	resetExternBuffer();
}

void MCU_UART_Rx_EXTERN_ISR(uint8_t * Rx){
	/* Echo */
	HAL_UART_Transmit(huart_extern, Rx, sizeof(Rx), HAL_MAX_DELAY);

	if(strcmp((char *)Rx, (char *)&cr)){
		pushExternBuffer(*Rx);
		command_start = FALSE;
		decodeCommand();
		resetExternBuffer();
	}
	else{
		if(command_start == TRUE) pushExternBuffer(*Rx);
		else if(*Rx != 'T') Rx_Prev = *Rx;
		else if(Rx_Prev == 'A'){
			command_start = TRUE;
			resetExternBuffer();
		}
	}
}


void MCU_UART_Rx_MODULE_ISR(uint8_t * Rx){
	/* Simply forward message */
	HAL_UART_Transmit(huart_extern, Rx, sizeof(Rx), HAL_MAX_DELAY);
}

/**
 * @brief	Decodes and executes a received command if found to be valid.
 * 			Else forwards to module
 */
static void decodeCommand(){
	/* List of supported MCU commands. */



	/* No command valid. Forwarding to Module */
	forwardMessage();
}


static void forwardMessage(){
	if(M66_IsOn() == FALSE)M66_PowerOn();
	uint16_t validLength = strcspn((const char*)Extern_Rx_Buffer, (const char*)&cr);
	HAL_UART_Transmit(huart_module, Extern_Rx_Buffer, validLength, HAL_MAX_DELAY);
}

/**
 * @brief	Resets the buffer to "AT" and resets the index to 2.
 */
static void resetExternBuffer(){
	for(int i = 0; i < sizeof(Extern_Rx_Buffer); i++) Extern_Rx_Buffer[i] = 0;
	Extern_Rx_Buffer[0] = 'A';
	Extern_Rx_Buffer[1] = 'T';
	Extern_Rx_Buffer_Index = 2;
}

/**
 * @brief	Pushes a character to the end of the buffer.
 * @param
 */
static void pushExternBuffer(uint8_t c){
	Extern_Rx_Buffer[Extern_Rx_Buffer_Index] = c;
	Extern_Rx_Buffer_Index++;
}

/* End Source Code */


/*** END OF FILE ***/
