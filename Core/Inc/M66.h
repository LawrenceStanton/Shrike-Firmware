/**
  ******************************************************************************
  * @file           : M66.h
  * @brief          : Header for M66.h file.
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
#ifndef M66_DRIVER_M66_H_
#define M66_DRIVER_M66_H_

/* Begin Public Includes */
#include "Shrike.h"

/* End Public Includes */

/* Begin Public Defines */

/* Begin Default Pin Definitions */
#ifndef MODULE_VEXT_SENCE_Pin
	#define MODULE_VEXT_SENCE_Pin GPIO_PIN_6
#endif

#ifndef MODULE_VEXT_SENCE_GPIO_Port
	#define MODULE_VEXT_SENCE_GPIO_Port GPIOA
#endif

#ifndef MODULE_EN_Pin
	#define MODULE_EN_Pin GPIO_PIN_15
#endif

#ifndef MODULE_EN_GPIO_Port
	#define MODULE_EN_GPIO_Port GPIOA
#endif

/* End Public Defines */


/* Begin Public Typedefs */


/* End Public Typedefs */

/* Begin Public Function Prototypes */
void M66_Config(UART_HandleTypeDef * huart);

void M66_PowerOn(void);
void M66_PowerOffHard(void);
void M66_PowerOffSoft(void);

bool M66_IsOn(void);

/* End Public Function Prototypes */

#endif /* M66_DRIVER_M66_H_ */

/*** END OF FILE ***/
