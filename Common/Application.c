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
	// Key A
	if(event.eventName == evKeyAPressed) {
		CLS1_SendStr("A Pressed\r\n", CLS1_GetStdio()->stdOut);
		LED1_On();
	}

	if(event.eventName == evKeyAReleased) {
		CLS1_SendStr("A Released\r\n", CLS1_GetStdio()->stdOut);
		LED1_Off();
	}

	if(event.eventName == evKeyALongPressed) {
		CLS1_SendStr("A Long Press\r\n", CLS1_GetStdio()->stdOut);
		LED2_Neg();
	}

	if(event.eventName == evKeyAClick) {
		CLS1_SendStr("A Click\r\n", CLS1_GetStdio()->stdOut);
		LED3_On();
	}

	if(event.eventName == evKeyADoubleClick) {
		CLS1_SendStr("A Double Click\r\n", CLS1_GetStdio()->stdOut);
		LED3_Off();
	}

	// Key B
	if(event.eventName == evKeyBPressed ) {
		CLS1_SendStr("B Pressed\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyBReleased ) {
		CLS1_SendStr("B Released\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyBLongPressed ) {
		CLS1_SendStr("B Long Press\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyBClick ) {
		CLS1_SendStr("B Click\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyBDoubleClick ) {
		CLS1_SendStr("B Double Click\r\n", CLS1_GetStdio()->stdOut);
	}

	// Key C
	if(event.eventName == evKeyCPressed ) {
		CLS1_SendStr("C Pressed\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyCReleased ) {
		CLS1_SendStr("C Released\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyCLongPressed ) {
		CLS1_SendStr("C Long Press\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyCClick ) {
		CLS1_SendStr("C Click\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyCDoubleClick ) {
		CLS1_SendStr("C Double Click\r\n", CLS1_GetStdio()->stdOut);
	}

	// Key D
	if(event.eventName == evKeyDPressed ) {
		CLS1_SendStr("D Pressed\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyDReleased ) {
		CLS1_SendStr("D Released\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyDLongPressed ) {
		CLS1_SendStr("D Long Press\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyDClick ) {
		CLS1_SendStr("D Click\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyDDoubleClick ) {
		CLS1_SendStr("D Double Click\r\n", CLS1_GetStdio()->stdOut);
	}

	// Key E
	if(event.eventName == evKeyEPressed ) {
		CLS1_SendStr("E Pressed\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyEReleased ) {
		CLS1_SendStr("E Released\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyELongPressed ) {
		CLS1_SendStr("E Long Press\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyEClick ) {
		CLS1_SendStr("E Click\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyEDoubleClick ) {
		CLS1_SendStr("E Double Click\r\n", CLS1_GetStdio()->stdOut);
	}

	// Key F
	if(event.eventName == evKeyFPressed ) {
		CLS1_SendStr("F Pressed\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyFReleased ) {
		CLS1_SendStr("F Released\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyFLongPressed ) {
		CLS1_SendStr("F Long Press\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyFClick ) {
		CLS1_SendStr("F Click\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyFDoubleClick ) {
		CLS1_SendStr("F Double Click\r\n", CLS1_GetStdio()->stdOut);
	}

	// Key G
	if(event.eventName == evKeyGPressed ) {
		CLS1_SendStr("G Pressed\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyGReleased ) {
		CLS1_SendStr("G Released\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyGLongPressed ) {
		CLS1_SendStr("G Long Press\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyGClick ) {
		CLS1_SendStr("G Click\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyGDoubleClick ) {
		CLS1_SendStr("G Double Click\r\n", CLS1_GetStdio()->stdOut);
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

  Event_t event;

  EVNT_SetEvent((Event_t){_smKey,evStart});
  EVNT_SetEvent((Event_t){_smKeyA,evStart});
  EVNT_SetEvent((Event_t){_smKeyB,evStart});
  EVNT_SetEvent((Event_t){_smKeyC,evStart});
  EVNT_SetEvent((Event_t){_smKeyD,evStart});
  EVNT_SetEvent((Event_t){_smKeyE,evStart});
  EVNT_SetEvent((Event_t){_smKeyF,evStart});
  EVNT_SetEvent((Event_t){_smKeyG,evStart});

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

			  #if PL_CONFIG_IS_FRDM
		  	  case _smKey:
		  	  case _smKeyA:
		  	  case _smKeyB:
		  	  case _smKeyC:
		  	  case _smKeyD:
		  	  case _smKeyE:
		  	  case _smKeyF:
		  	  case _smKeyG:
		  		  smKey(event);
		  		  break;
			  #endif
		  }
	  }
  }
  PL_Deinit();
}



