/**
 * \file
 * \brief Timer driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for the timers used in the system.
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "TU1.h"
#include "Event.h"


#define TMR_TICK_MS  (1000/(TU1_CNT_INP_FREQ_U_0 / TU1_OFFSET_0_TICKS))
  /*!< we get called every TMR_TICK_MS ms */

/*! \brief Function called from timer interrupt every TMR_TICK_MS. */
void TMR_OnInterrupt(void);

/*! \brief Timer driver initialization */
void TMR_Init(void);

/*! \brief Timer driver de-initialization */
void TMR_Deinit(void);

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
unsigned int schedule_timer( uint16 time , Event_t ev, bool inISR );

/**
  * @brief  This funcion clears a timer selected by the given timer ID.
  *
  * @param  id      Timer ID of the timer which will be cleared
  * @param  inISR   true if program is in ISR, otherwise false
  */
void unschedule_timer( uint16 id , bool inISR );

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

#endif /* TIMER_H_ */
