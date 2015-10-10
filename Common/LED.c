/*
 * LED.c
 *
 *  Created on: 29.09.2015
 *      Author: Jon
 */


#include "Platform.h"
#if PL_CONFIG_HAS_LED
#include "LED.h"

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
void LED_Init(void) {
#if PL_CONFIG_NOF_LED>=1
  LED1_Off();
#endif
#if PL_CONFIG_NOF_LED>=2
  LED2_Off();
#endif
#if PL_CONFIG_NOF_LED>=3
  LED3_Off();
#endif
#if PL_CONFIG_NOF_LED>=4
  #error "only 3 LEDs supported"
#endif
}


/*
** ===================================================================
**     Method      :  void LED_Deinit(void)
**     Description :
**         Deinits all LEDs on PL by turning them off.
**         (independent how many LEDs)
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void LED_Deinit(void) {
#if PL_CONFIG_NOF_LED>=1
  LED1_Off();
#endif
#if PL_CONFIG_NOF_LED>=2
  LED2_Off();
#endif
#if PL_CONFIG_NOF_LED>=3
  LED3_Off();
#endif
#if PL_CONFIG_NOF_LED>=4
  #error "only 3 LEDs supported"
#endif
}
#endif /* PL_CONFIG_HAS_LED */



