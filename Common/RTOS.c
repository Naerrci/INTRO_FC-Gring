/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_CONFIG_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "LED.h"
#include "Event.h"
#include "Keys.h"
#include "Application.h"
#include "BUZZER1.h"
#include "EInt1.h"

#define TEST_RTOS_TASKS  (1)

#if TEST_RTOS_TASKS

static void LED1Task(void* pvParameters) {
	(void)pvParameters;
	for(;;) {
		LED1_Neg();
		FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
	}
}

static void LED2Task(void* pvParameters) {
	(void)pvParameters;
  for(;;) {
	  LED2_Neg();
	  FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

#if PL_CONFIG_IS_ROBO
static void BuzzerTask(void* pvParameters) {
	(void)pvParameters;
	for(;;) {
		if(EInt1_GetVal() == 0){
			BUZZER1_NegVal();
		} else
		{
			BUZZER1_ClrVal();
		}
		FRTOS1_vTaskDelay(1/portTICK_RATE_MS);
	}
}
#endif	// PL_CONFIG_IS_ROBO
#endif	// TEST_RTOS_TASKS

static void AppTask(void* pvParameters) {
	(void)pvParameters;
    //EVNT_SetEvent(EVNT_STARTUP); /* set startup event */

	Event_t event;

	#if PL_CONFIG_IS_FRDM
	EVNT_SetEvent((Event_t){_smKey,evStart});
	EVNT_SetEvent((Event_t){_smKeyA,evStart});
	EVNT_SetEvent((Event_t){_smKeyB,evStart});
	EVNT_SetEvent((Event_t){_smKeyC,evStart});
	EVNT_SetEvent((Event_t){_smKeyD,evStart});
	EVNT_SetEvent((Event_t){_smKeyE,evStart});
	EVNT_SetEvent((Event_t){_smKeyF,evStart});
	EVNT_SetEvent((Event_t){_smKeyG,evStart});
	#endif

	#if PL_CONFIG_IS_ROBO
	EVNT_SetEvent((Event_t){_smEInt,evStart});
	EVNT_SetEvent((Event_t){_smBuzzer,evStart});
	#endif

	for(;;) {
	// CLS1_SendStr("Hello World!\r\n", CLS1_GetStdio()->stdOut);

		#if PL_CONFIG_IS_FRDM
		KEY_Scan();
		#endif

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

				#if PL_CONFIG_IS_ROBO
				case _smROBO:
					smROBO(event);
					break;

				case _smEInt:
					smEInt(event);
					break;

				case _smBuzzer:
//					smBuzzer(event);	// disabled for testing Buzzer Task
					break;
					#endif

				#if PL_CONFIG_IS_FRDM
				case _smFRDM:
					smFRDM(event);
					break;

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

    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

void RTOS_Run(void) {
	FRTOS1_vTaskStartScheduler();  /* does usually not return! */
}

void RTOS_Init(void) {
	/*! \todo Add tasks here */
	if (FRTOS1_xTaskCreate(AppTask,
			(signed portCHAR *)"App",
			configMINIMAL_STACK_SIZE,
			NULL,
			tskIDLE_PRIORITY,
			NULL) != pdPASS) {
		for(;;){} /* error */
	}
#if TEST_RTOS_TASKS
	if (FRTOS1_xTaskCreate(LED1Task,
			(signed portCHAR *)"LED1Task",
			configMINIMAL_STACK_SIZE,
			NULL,
			tskIDLE_PRIORITY,
			NULL) != pdPASS) {
		for(;;){} /* error */
	}
	if (FRTOS1_xTaskCreate(LED2Task,
			(signed portCHAR *)"LED2Task",
			configMINIMAL_STACK_SIZE,
			NULL,
			tskIDLE_PRIORITY,
			NULL) != pdPASS) {
		for(;;){} /* error */
	}
#if PL_CONFIG_IS_ROBO
	if (FRTOS1_xTaskCreate(BuzzerTask,
			(signed portCHAR *)"Buzzer",
			configMINIMAL_STACK_SIZE,
			NULL,
			tskIDLE_PRIORITY,
			NULL) != pdPASS) {
		for(;;){} /* error */
	}
#endif	// PL_CONFIG_IS_ROBO
#endif	// TEST_RTOS_TASKS
}

void RTOS_Deinit(void) {
  /* nothing needed */
}

#endif /* PL_HAS_RTOS */
