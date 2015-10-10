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
  // all other Inits here
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
  // all other Deinits here
#endif
}


