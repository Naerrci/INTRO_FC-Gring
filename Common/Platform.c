/*
 * Platform.c
 *
 *  Created on: 29.09.2015
 *      Author: Jon
 */

#include "Platform.h"

#if PL_CONFIG_HAS_LED
  #include "LED.h"
#endif
#if PL_CONFIG_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_CONFIG_HAS_TIMER
  #include "Timer.h"
#endif
#if PL_CONFIG_HAS_RTOS
  #include "RTOS.h"
#endif


/*
** ===================================================================
**     Method      :  void PL_Init(void)
**     Description :
**         Init platform components
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PL_Init(void) {

#if PL_CONFIG_HAS_LED
  LED_Init();
#endif

#if PL_CONFIG_HAS_EVENTS
  EVNT_Init();
#endif

#if PL_CONFIG_HAS_TIMER
  TMR_Init();
#endif

#if PL_CONFIG_HAS_RTOS
  RTOS_Init();
#endif
}


/*
** ===================================================================
**     Method      :  void PL_Deinit(void)
**     Description :
**         Deinit platform components
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PL_Deinit(void) {
#if PL_CONFIG_HAS_LED
  LED_Deinit();
#endif
}


