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
#include "Platform_local.h"

#if PL_CONFIG_HAS_LED
  #include "LED.h"
#endif

void smFRDM(Event_t event) {
	if(event.eventName == evKeyAPressed) {
		CLS1_SendStr("Key A Pressed\r\n", CLS1_GetStdio()->stdOut);
		LED1_On();
	}

	if(event.eventName == evKeyAReleased) {
		CLS1_SendStr("Key A Released\r\n", CLS1_GetStdio()->stdOut);
		LED1_Off();
	}

	if(event.eventName == evKeyALongPressed) {
		CLS1_SendStr("Key A Long Press\r\n", CLS1_GetStdio()->stdOut);
		LED2_Neg();
	}

	if(event.eventName == evKeyAClick) {
		CLS1_SendStr("Key A Click\r\n", CLS1_GetStdio()->stdOut);
		LED3_On();
	}

	if(event.eventName == evKeyADoubleClick) {
		CLS1_SendStr("Key A Double Click\r\n", CLS1_GetStdio()->stdOut);
		LED3_Off();
	}
}

#if PL_CONFIG_IS_ROBO
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
#endif

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

  Event_t event = {_smKeyA,evStart};

  EVNT_SetEvent(event);

 // CLS1_SendStr("Hello World!\r\n", CLS1_GetStdio()->stdOut);

  for(;;) {
	  KEY_Scan();

	  if(EVNT_EventsInQueue()) {
		  event = EVNT_GetEvent();
		  switch(event.smName) {
		  	  case _smUnknown:
		  		  break;

		  	  case _smAll:
				  #if PL_CONFIG_IS_ROBO
		  		  smROBO(event);
				  #endif
				  #if PL_CONFIG_IS_FRDM
		  		  smFRDM(event);
				  #endif
		  		  break;

		  	  case _smROBO:
				  #if PL_CONFIG_IS_ROBO
		  		  smROBO(event);
				  #endif
		  		  break;

		  	  case _smFRDM:
				  #if PL_CONFIG_IS_FRDM
		  		  smFRDM(event);
				  #endif
		  		  break;

		  	  case _smKeyA:
		  		  smKeyA(event);
		  		  break;
		  }
	  }
  }
  PL_Deinit();
}



