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

#include "CS1.h"

Timer_t timerQueue[MAXTIMER];
int timerInQueue = 0;

void TMR_OnInterrupt(void) {
	tickTimer();
}

void TMR_Init(void) {
	clearTimerQueue();
}

void TMR_Deinit(void) {
  /* nothing needed right now */
}

void clearTimerQueue(void) {

	for( int i = 0 ; i < MAXTIMER ; i++ ) {
		timerQueue[i].tm = 0;
		timerQueue[i].tmEvent = evNull;
		timerQueue[i].tmId = IdNull;
	}
}

unsigned int schedule_timer( uint16 time , Event_t ev ) {
    static uint16 TID = 0;
    int i = 0;

    CS1_CriticalVariable();
    CS1_EnterCritical();

    TID %= 65536;

    for( i = 0 ; i < MAXTIMER ; i++ )
    {
        if( timerQueue[i].tmId == IdNull )
        {
            timerQueue[i].tm = time;
            timerQueue[i].tmEvent = ev;
            timerQueue[i].tmId = ++TID;
            break;
        }
    }

    timerInQueue += 1;

    CS1_ExitCritical();

    return TID;
}

void unschedule_timer( uint16 id ) {
    int i = 0;
    Event_t nullEvent = evNull;

    CS1_CriticalVariable();
    CS1_EnterCritical();

    for( i = 0 ; i < MAXTIMER ; i++ )
    {
        if( timerQueue[i].tmId == id )
        {
            timerQueue[i].tmId = IdNull;
            timerQueue[i].tmEvent = nullEvent;
            timerQueue[i].tm = 0;
            break;
        }
    }

    timerInQueue -= 1;

    CS1_ExitCritical();
}

void tickTimer( ) {
    int i = 0;

    if( timerInQueue == 0 )
    	return;

    for( i = 0 ; i < MAXTIMER ; i++ )
    {
        if( timerQueue[i].tmId != IdNull )
        {
            timerQueue[i].tm -= TMR_TICK_MS;

            if( timerQueue[i].tm <= 0 )
            {
                EVNT_SetEvent( timerQueue[i].tmEvent  );
                unschedule_timer( timerQueue[i].tmId );
            }
        }
    }
}

int getTimerInQueue(){
	return timerInQueue;
}

#endif /*PL_CONFIG_HAS_TIMER*/

