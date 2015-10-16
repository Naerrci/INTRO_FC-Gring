/**
 * \file
 * \brief Event driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic event driver. We are using numbered events starting with zero.
 * EVNT_HandleEvent() can be used to process the pending events. Note that the event with the number zero
 * has the highest priority and will be handled first.
 * \todo Make this module reentrant and thread safe!
 */

#include "Platform.h"
#include "CS1.h"
#if PL_CONFIG_HAS_EVENTS
#include "Event.h" /* our own interface */

static Event_t eventQueue[MAXEVENT];
static short eventsInQueue = 0;

void EVNT_SetEvent(Event_t event) {
	int i = 0;

	CS1_CriticalVariable();
	CS1_EnterCritical();

	for( i = 0 ; i < MAXEVENT ; i++ )
	{
		if( eventQueue[i].eventName == evNull )
		{
			eventQueue[i] = event;
			eventsInQueue += 1;
			break;
		}
	}

	CS1_ExitCritical();
}

Event_t EVNT_GetEvent() {
	Event_t ev;
	int i = 0;

	CS1_CriticalVariable();
	CS1_EnterCritical();

	ev = eventQueue[0];

	for(  i = 0 ; i < ( MAXEVENT - 1 ) && eventQueue[i].eventName != evNull ; i++ )
	{
		eventQueue[i] = eventQueue[i + 1];
	}

	eventQueue[MAXEVENT - 1].eventName = evNull;
	eventsInQueue -= 1;

	CS1_ExitCritical();

	return ev;
}

short EVNT_EventsInQueue()
{
    return eventsInQueue;
}

void EVNT_Init(void) {
	int i = 0;
	Event_t nullEvent;
	nullEvent.eventName = evNull;
	nullEvent.smName = _smUnknown;

    for( i = 0 ; i < MAXEVENT ; i++ )
    {
        eventQueue[i] = nullEvent;
    }
}

void EVNT_Deinit(void) {
  /* nothing needed */
}

#endif /* PL_HAS_EVENTS */
