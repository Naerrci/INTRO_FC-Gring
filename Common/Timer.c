/**
 * \file
 * \brief Timer driver
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for all our timers.
  */

#include "Platform.h"
#if PL_CONFIG_HAS_TIMER
#include "Timer.h"
#include "Event.h"
#if PL_CONFIG_HAS_EINT
#include "EInt1.h"
#endif /*PL_CONFIG_HAS_EINT*/

void TMR_OnInterrupt(void) {
	EVNT_SetEvent(EVENT_TIMER);
}

void TMR_Init(void) {
  /* nothing needed right now */
}

void TMR_Deinit(void) {
  /* nothing needed right now */
}

#endif /*PL_CONFIG_HAS_TIMER*/

