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
#include "CLS1.h"
#include "Keys.h"

#if PL_CONFIG_HAS_LED
  #include "LED.h"
#endif

void smFRDM(Event_t event) {
	return;
}

void smROBO(Event_t event){
	static int timerID = 0;
	Event_t timerEvent = {_smROBO,evTimer};

	if(event.eventName == evBt1Pressed) {
		timerID = schedule_timer(1000,timerEvent);
		LED1_On();
		CLS1_SendStr("Hello World!\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evBt1Released) {
		unschedule_timer(timerID);
		LED1_Off();
	}

	if(event.eventName == evTimer) {
		LED2_Neg();
		CLS1_SendStr("Long pressed!\r\n", CLS1_GetStdio()->stdOut);
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
  TMR_Init();

  Event_t event;

 // CLS1_SendStr("Hello World!\r\n", CLS1_GetStdio()->stdOut);

  for(;;) {
	  KEY_Scan();

	  if(EVNT_EventsInQueue()) {
		  event = EVNT_GetEvent();
		  switch(event.smName) {
		  	  case _smUnknown:
		  		  break;

		  	  case _smAll:
		  		  smROBO(event);
		  		  smFRDM(event);
		  		  break;

		  	  case _smROBO:
		  		  smROBO(event);
		  		  break;

		  	  case _smFRDM:
		  		  smFRDM(event);
		  		  break;
		  }
	  }

	  if(KEY1_Get()) {
	  		LED1_On();
	  } else {
		  LED1_Off();
	  }
  }
  PL_Deinit();
}



