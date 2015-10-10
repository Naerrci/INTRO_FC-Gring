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
#define PL_CONFIG_HAS_LED   		PL_CONFIG_NOF_LED > 0
#define PL_CONFIG_HAS_EVENTS        !defined(PL_CONFIG_DISABLE_HAS_EVENTS)
#define PL_CONFIG_HAS_TIMER         !defined(PL_CONFIG_DISABLE_HAS_TIMER)
#define PL_CONFIG_HAS_KEYS          PL_CONFIG_NOF_KEYS > 0
#define PL_CONFIG_HAS_KBI           !defined(PL_CONFIG_DISABLE_HAS_KBI) && PL_CONFIG_HAS_KEYS
#define PL_CONFIG_HAS_EINT			PL_CONFIG_NOF_EINT >= 1

#define PL_CONFIG_HAS_JOYSTICK    	PL_CONFIG_HAS_KEYS
#define PL_KEY_POLLED_KEY1 			1

#define PL_CONFIG_HAS_DEBOUNCE  	0

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
