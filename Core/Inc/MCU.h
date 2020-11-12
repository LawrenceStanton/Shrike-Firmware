/**
  ******************************************************************************
  * @file           : MCU.h
  * @brief          : Header for MCU.c file.
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
#ifndef INC_MCU_H_
#define INC_MCU_H_

/* Begin Public Includes */
#include "stm32g0xx_hal.h"

/* End Public Includes */

/* Begin Public Defines */


/* Begin Default Pin Definitions */

/* End Public Defines */


/* Begin Public Typedefs */


/* End Public Typedefs */

/* Begin Public Function Prototypes */

/* UART Receive ISRs */
void MCU_config(UART_HandleTypeDef*, UART_HandleTypeDef*);

void MCU_UART_Rx_EXTERN_ISR(uint8_t *);
void MCU_UART_Rx_MODULE_ISR(uint8_t *);


/* End Public Function Prototypes */

#endif /* INC_MCU_H_ */


/*** END OF FILE ***/
