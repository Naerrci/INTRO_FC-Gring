/*
 * Platform.h
 *
 *  Created on: 29.09.2015
 *      Author: Jon
 */

#ifndef SOURCES_COMMON_PLATFORM_H_
#define SOURCES_COMMON_PLATFORM_H_

#include "Platform_Local.h"
#include "PE_Types.h" /* common Processor Expert types: bool, NULL, ... */

/* configuration macros */
#define PL_CONFIG_HAS_LED   			PL_CONFIG_NOF_LED > 0
#define PL_CONFIG_HAS_EVENTS        	!defined(PL_CONFIG_DISABLE_HAS_EVENTS)
#define PL_CONFIG_HAS_TIMER         	!defined(PL_CONFIG_DISABLE_HAS_TIMER)
#define PL_CONFIG_HAS_KEYS          	PL_CONFIG_NOF_KEYS > 0
#define PL_CONFIG_HAS_KBI           	!defined(PL_CONFIG_DISABLE_HAS_KBI) && PL_CONFIG_HAS_KEYS
#define PL_CONFIG_HAS_EINT				PL_CONFIG_NOF_EINT >= 1

#define PL_CONFIG_HAS_JOYSTICK    		PL_CONFIG_HAS_KEYS
#define PL_KEY_POLLED_KEY1 				1

#define PL_CONFIG_HAS_DEBOUNCE  		0

#define PL_CONFIG_HAS_RTOS		  		1

#define PL_CONFIG_HAS_BUZZER	  		PL_CONFIG_NOF_BUZZ > 0

#define PL_CONFIG_HAS_LCD	  	    	PL_CONFIG_NOF_LCD > 0
#define PL_CONFIG_HAS_SNAKE				((PL_CONFIG_NOF_SNAKE > 0) && PL_CONFIG_HAS_LCD)

#define PL_CONFIG_HAS_SHELL				PL_CONFIG_NOF_SHELL > 0
#define PL_CONFIG_HAS_BLUETOOTH			PL_CONFIG_NOF_BLUETOOTH > 0
#define PL_CONFIG_HAS_USB_CDC			PL_CONFIG_NOF_USB_CDC > 0

#define PL_CONFIG_HAS_SHELL_QUEUE		PL_CONFIG_NOF_SHELL_QUEUE > 0
#define PL_HAS_CONFIG_SEMAPHORE       	(0)
#define PL_CONFIG_HAS_REFLECTANCE     	(1 && defined(PL_BOARD_IS_ROBO))		// PL_CONFIG_IS_ROBO
#define PL_CONFIG_HAS_MOTOR				(1 && defined(PL_BOARD_IS_ROBO))		// PL_CONFIG_IS_ROBO

#define PL_CONFIG_HAS_SEMAPHORE       	(1)
#define PL_SQUEUE_SINGLE_CHAR        	(1)

#define PL_CONFIG_HAS_CONFIG_NVM      	(1 && PL_CONFIG_NOF_NVM > 0)
#define PL_CONFIG_EST                 	(1)

#define PL_CONFIG_HAS_MCP4728           (1 && defined(PL_BOARD_IS_ROBO))
#define PL_CONFIG_HAS_QUADRATURE        (1 && defined(PL_BOARD_IS_ROBO))
#define PL_CONFIG_HAS_QUAD_CALIBRATION  (1 && PL_CONFIG_HAS_QUADRATURE && PL_CONFIG_HAS_MCP4728)

#define PL_CONFIG_HAS_MOTOR_TACHO       (1 && PL_CONFIG_HAS_MOTOR)
#define PL_CONFIG_HAS_ULTRASONIC        (1 && defined(PL_BOARD_IS_ROBO))
#define PL_CONFIG_HAS_PID               (1 && PL_CONFIG_HAS_MOTOR_TACHO)

#define PL_CONFIG_HAS_DRIVE				(1 && PL_CONFIG_HAS_PID)

#define PL_CONFIG_HAS_TURN              (1 && PL_CONFIG_HAS_DRIVE)
#define PL_CONFIG_HAS_LINE_FOLLOW       (1 && PL_CONFIG_HAS_REFLECTANCE)
#define PL_CONFIG_HAS_LINE_MAZE         (1 && PL_CONFIG_HAS_LINE_FOLLOW)

#define PL_CONFIG_HAS_RADIO             (1)
#define PL_CONFIG_HAS_REMOTE            (1 && PL_CONFIG_HAS_RADIO)
#define PL_CONFIG_CONTROL_SENDER        (1 && PL_CONFIG_HAS_JOYSTICK && defined(PL_BOARD_IS_FRDM))




/*
** ===================================================================
**     Method      :  void PL_Init(void)
**     Description :
**         Init platform components
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PL_Init(void);


/*
** ===================================================================
**     Method      :  void PL_Deinit(void)
**     Description :
**         Deinit platform components
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PL_Deinit(void);




#endif /* SOURCES_COMMON_PLATFORM_H_ */
