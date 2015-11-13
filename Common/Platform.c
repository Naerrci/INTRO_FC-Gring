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
#if PL_CONFIG_HAS_SHELL
  #include "Shell.h"
#endif
#if PL_CONFIG_HAS_SNAKE
  #include "Snake.h"
#endif
#if PL_CONFIG_HAS_SHELL_QUEUE
  #include "ShellQueue.h"
#endif
#if PL_HAS_CONFIG_SEMAPHORE
  #include "Sem.h"
#endif
#if PL_CONFIG_HAS_REFLECTANCE
  #include "Reflectance.h"
#endif
#if PL_CONFIG_HAS_MOTOR
  #include "Motor.h"
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
#if PL_CONFIG_HAS_SHELL
  SHELL_Init();
#endif
#if PL_CONFIG_HAS_SNAKE
  //SNAKE_Init();
#endif
#if PL_CONFIG_HAS_SHELL_QUEUE
  SQUEUE_Init();
#endif
#if PL_HAS_CONFIG_SEMAPHORE
  SEM_Init();
#endif
#if PL_CONFIG_HAS_REFLECTANCE
  REF_Init();
#endif
#if PL_CONFIG_HAS_MOTOR
  MOT_Init();
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
#if PL_CONFIG_HAS_SNAKE
  SNAKE_Deinit();
#endif
#if PL_CONFIG_HAS_SHELL
  SHELL_Deinit();
#endif
#if PL_CONFIG_HAS_RTOS
  RTOS_Deinit();
#endif
#if PL_CONFIG_HAS_REFLECTANCE
  REF_Deinit();
#endif
#if PL_HAS_CONFIG_SEMAPHORE
  SEM_Deinit();
#endif
#if PL_CONFIG_HAS_SHELL_QUEUE
  SQUEUE_Deinit();
#endif
#if PL_CONFIG_HAS_MOTOR
  MOT_Deinit();
#endif
}


