/*
 * Application.c
 *
 *  Created on: 29.09.2015
 *      Author: Jon
 */


#include "Platform.h"
#include "Platform_local.h"
#include "Application.h"
#include "WAIT1.h"
#include "CLS1.h"

#if PL_CONFIG_HAS_TIMER
  #include "Timer.h"
#endif
#if PL_CONFIG_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_CONFIG_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_CONFIG_HAS_BUZZER
  #include "BUZZER1.h"
  #include "Buzzer.h"
#endif
#if PL_CONFIG_HAS_LED
  #include "LED.h"
#endif
#if PL_CONFIG_HAS_RTOS
  #include "RTOS.h"
  #include "FRTOS1.h"
#endif
#if PL_CONFIG_HAS_LCD
  #include "PDC1.h"
  #include "GDisp1.h"
#endif
#if PL_CONFIG_HAS_SNAKE
  #include "Event_Styger.h"
  #include "Snake.h"
#endif

#if PL_CONFIG_IS_FRDM
void smFRDM(Event_t event) {
	// Key A
	if(event.eventName == evKeyAPressed) {
		//CLS1_SendStr("A Pressed\r\n", CLS1_GetStdio()->stdOut);
		//LED1_On();
		#if PL_CONFIG_HAS_SNAKE
			EVNT_SetEvent_Sty(EVNT_SNAKE_UP);
		#endif

	}

	if(event.eventName == evKeyAReleased) {
		//CLS1_SendStr("A Released\r\n", CLS1_GetStdio()->stdOut);
		//LED1_Off();
	}

	if(event.eventName == evKeyALongPressed) {
		//CLS1_SendStr("A Long Press\r\n", CLS1_GetStdio()->stdOut);
		//LED2_Neg();
	}

	if(event.eventName == evKeyAClick) {
		CLS1_SendStr("A Click\r\n", CLS1_GetStdio()->stdOut);
        #if PL_CONFIG_NOF_LED>=3
        	LED3_Off();
        #endif
	}

	if(event.eventName == evKeyADoubleClick) {
		CLS1_SendStr("A Double Click\r\n", CLS1_GetStdio()->stdOut);
		#if PL_CONFIG_NOF_LED>=3
			LED3_Off();
  	  	#endif
	}

	// Key B
	if(event.eventName == evKeyBPressed ) {
		//CLS1_SendStr("B Pressed\r\n", CLS1_GetStdio()->stdOut);
		#if PL_CONFIG_HAS_SNAKE
			EVNT_SetEvent_Sty(EVNT_SNAKE_RIGHT);
		#endif
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
		//CLS1_SendStr("C Pressed\r\n", CLS1_GetStdio()->stdOut);
		#if PL_CONFIG_HAS_SNAKE
			EVNT_SetEvent_Sty(EVNT_SNAKE_DOWN);
		#endif
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
		//CLS1_SendStr("D Pressed\r\n", CLS1_GetStdio()->stdOut);
		#if PL_CONFIG_HAS_SNAKE
			EVNT_SetEvent_Sty(EVNT_SNAKE_LEFT);
		#endif
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
		#if PL_CONFIG_HAS_SNAKE
			EVNT_SetEvent_Sty(EVNT_SNAKE_START_PAUSE);
    	#endif

	}

	if(event.eventName == evKeyEDoubleClick ) {
		CLS1_SendStr("E Double Click\r\n", CLS1_GetStdio()->stdOut);
	}

	// Key F
	if(event.eventName == evKeyFPressed ) {
		//CLS1_SendStr("F Pressed\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyFReleased ) {
		//CLS1_SendStr("F Released\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyFLongPressed ) {
		FRTOS1_vTaskSuspend(SnakeTaskHandle);
		//CLS1_SendStr("F Long Press\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyFClick ) {
//		FRTOS1_vTaskDelete(SnakeTask);
		//CLS1_SendStr("F Click\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evKeyFDoubleClick ) {
		FRTOS1_vTaskResume(SnakeTaskHandle);
		//CLS1_SendStr("F Double Click\r\n", CLS1_GetStdio()->stdOut);
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
#endif

#if PL_CONFIG_IS_ROBO
void smROBO(Event_t event){
	if(event.eventName == evBt1Pressed) {
		CLS1_SendStr("Bt1 pressed\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evBt1Released) {
		CLS1_SendStr("Bt1 released\r\n", CLS1_GetStdio()->stdOut);
	}

	if(event.eventName == evBt1Click) {
		CLS1_SendStr("Bt1 click\r\n", CLS1_GetStdio()->stdOut);
		startBuzzer(High,1000);
	}

	if(event.eventName == evBt1DoubleClick) {
		CLS1_SendStr("Bt1 double click\r\n", CLS1_GetStdio()->stdOut);
		startBuzzer(Middle,1000);
	}

	if(event.eventName == evBt1LongPressed) {
		CLS1_SendStr("Bt1 long pressed\r\n", CLS1_GetStdio()->stdOut);
		startBuzzer(Low,1000);
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
#if PL_CONFIG_HAS_LCD
  PDC1_WriteLineStr(1, "Hello World");
  PDC1_WriteLineStr(2, "from the");
  PDC1_WriteLineStr(3, "KL25Z Freedom");
  PDC1_WriteLineStr(4, "Board!");

  GDisp1_Clear();
  GDisp1_DrawCircle(30, 15, 10, GDisp1_COLOR_BLACK);
  GDisp1_DrawFilledBox(0, 5, 6, 20, GDisp1_COLOR_BLACK);
  GDisp1_DrawLine(30, 30, 45, 60, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
#endif
#if PL_CONFIG_HAS_RTOS
  RTOS_Run();
#endif

  PL_Deinit();
}



