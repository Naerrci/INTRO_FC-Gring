/*
 * LED.h
 *
 *  Created on: 29.09.2015
 *      Author: Jon
 */

#ifndef SOURCES_COMMON_LED_H_
#define SOURCES_COMMON_LED_H_

#include "Platform.h"

#if PL_CONFIG_NOF_LED>=1
  #include "LED1.h"
#endif
#if PL_CONFIG_NOF_LED>=2
  #include "LED2.h"
#endif
#if PL_CONFIG_NOF_LED>=3
  #include "LED3.h"
#endif


/*
** ===================================================================
**     Method      :  void LED_Init(void)
**     Description :
**         Inits all LEDs on PL by turning them off.
**         (independent how many LEDs)
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LED_Init(void);

/*
** ===================================================================
**     Method      :  void LED_Deinit(void)
**     Description :
**         Deinits all LEDs on PL by turning them off
**         (independent how many LEDs)
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LED_Deinit(void);




#endif /* SOURCES_COMMON_LED_H_ */
