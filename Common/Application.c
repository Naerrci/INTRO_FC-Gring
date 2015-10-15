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

void localEventHandler(Event_t event){
	static int timerID = 0;

	if(event == evBt1Pressed) {
		timerID = schedule_timer(1000,evTimer);
		LED1_On();
	}

	if(event == evBt1Released) {
		if(getTimerInQueue() == 1)
			unschedule_timer(timerID);
		LED1_Off();
	}

	if(event == evTimer) {
		LED2_Neg();
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



