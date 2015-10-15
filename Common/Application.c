/*
 * Application.c
 *
 *  Created on: 29.09.2015
 *      Author: Jon
 */


#include "Platform.h"
#include "Application.h"
#include "WAIT1.h"
#include "Event.h"
#include "Timer.h"

#if PL_CONFIG_HAS_LED
  #include "LED.h"
#endif

void localEventHandler(EVNT_Handle event){
	static int counter = 0;

	if(event == EVENT_TIMER) {
		counter += 1;
		if(counter >= 1000/TMR_TICK_MS)
			LED1_Neg();
		counter %= 1000/TMR_TICK_MS;
	}

	if(event == EVENT_BT1_PRESSED) {
		LED2_On();
	}

	if(event == EVENT_BT1_RELEASED) {
		LED2_Off();
	}
}

/*
** ===================================================================
**     Method      :  APP_Run(void)
**     Description :
**         This lets the application running.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void APP_Run(void) {
  PL_Init();
  EVNT_Init();

  for(;;) {
	  EVNT_HandleEvent(localEventHandler);
  }
  PL_Deinit();
}



