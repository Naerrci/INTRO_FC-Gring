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

/**
  * @brief  This function saves the timer in the timerQueue and
  *         set the corresponding TimerID.
  *
  * @param  time    timer duration in mS
  * @param  ev      event name
  * @param  inISR   true if program is in ISR, otherwise false
  *
  * @return timerID
  */
/*unsigned short schedule_timer( uint16 time , event ev, bool inISR )
{
    static uint16 TID;
    int i = 0;

    ENTERCRITICAL( inISR );

    if( TID == 65535 ) TID = 0;

    TID += 1;

    for( i = 0 ; i < MAXTIMER ; i++ )
    {
        if( timerQueue[i].tmId == idNull )
        {
            timerQueue[i].tm = time;
            timerQueue[i].tmEvent = ev;
            timerQueue[i].tmId = TID;
            break;
        }
    }

    LEAVECRITICAL( inISR );

    return TID;
}
*/
/**
  * @brief  This funcion clears a timer selected by the given timer ID.
  *
  * @param  id      Timer ID of the timer which will be cleared
  * @param  inISR   true if program is in ISR, otherwise false
  */
/*void unschedule_timer( uint16 id , bool inISR )
{
    int i = 0;
    event nullEvent = { _smUnknown, _evNull };

    ENTERCRITICAL( inISR );

    for( i = 0 ; i < MAXTIMER ; i++ )
    {
        if( timerQueue[i].tmId == id )
        {
            timerQueue[i].tmId = idNull;
            timerQueue[i].tmEvent = nullEvent;
            timerQueue[i].tm = 0;
            break;
        }
    }

    LEAVECRITICAL( inISR );
}*/

/**
  * @brief  This function is called every 5mS and checks if a timer is
  *         elapsed. In this case, the function pushes the corresponding
  *         event in the eventQueue.
  */
/*void tickTimer( )
{
    int i = 0;

    for( i = 0 ; i < MAXTIMER ; i++ )
    {
        if( timerQueue[i].tmId != idNull )
        {
            timerQueue[i].tm -= 5;

            if( timerQueue[i].tm == 0 )
            {
                pushEvent( timerQueue[i].tmEvent , true );
                unschedule_timer( timerQueue[i].tmId , true );
            }
        }
    }
}*/

#endif /*PL_CONFIG_HAS_TIMER*/

