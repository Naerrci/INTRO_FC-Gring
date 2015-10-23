/*
 * Buzzer.c
 *
 *  Created on: 22.10.2015
 *      Author: Simon
 */

#include "Buzzer.h"
#include "BUZZER1.h"
#include "timer.h"
#include "Event.h"

void startBuzzer(BuzzerFreq_t freq, int time) {
	switch(freq) {
		case High:
			EVNT_SetEvent((Event_t){_smBuzzer,evBuzzerHigh});
			break;

		case Middle:
			EVNT_SetEvent((Event_t){_smBuzzer,evBuzzerMiddle});
			break;

		case Low:
			EVNT_SetEvent((Event_t){_smBuzzer,evBuzzerLow});
			break;
	}

	schedule_timer(time,(Event_t){_smBuzzer,evBuzzerStop});
}

void smBuzzer(Event_t event) {
	static StateSmBuzzer_t state;
	StateSmBuzzer_t oldState = state;

	bool stateChanged = 0;

	static int timerIDBuzzerHigh;
	static int timerIDBuzzerMiddle;
	static int timerIDBuzzerLow;

	switch(state) {
		case stBuzzerNull:
			if(event.eventName = evStart) {
				state = stBuzzerIdle;
			}
			break;

		case stBuzzerIdle:
			if(event.eventName == evBuzzerHigh) {
				state = stSound;
				stateChanged = 1;
			}
			if(event.eventName == evBuzzerMiddle) {
				state = stSound;
				stateChanged = 1;
			}
			if(event.eventName == evBuzzerLow) {
				state = stSound;
				stateChanged = 1;
			}
			break;

		case stSound:
			if(event.eventName == evTimerBuzzerHigh || event.eventName == evBuzzerHigh) {
				state = stSound;
				stateChanged = 1;
			}
			if(event.eventName == evTimerBuzzerMiddle || event.eventName == evBuzzerMiddle) {
				state = stSound;
				stateChanged = 1;
			}
			if(event.eventName == evTimerBuzzerLow || event.eventName == evBuzzerLow) {
				state = stSound;
				stateChanged = 1;
			}
			if(event.eventName == evBuzzerStop) {
				state = stBuzzerIdle;
				stateChanged = 1;
			}
			break;
	}

	if(stateChanged){
		switch(state) {
			case stBuzzerIdle:
				break;

			case stSound:
				if(event.eventName == evTimerBuzzerHigh || event.eventName == evBuzzerHigh) {
					timerIDBuzzerHigh = schedule_timer(1,(Event_t){_smBuzzer,evTimerBuzzerHigh});
					BUZZER1_NegVal();
				}
				if(event.eventName == evTimerBuzzerMiddle || event.eventName == evBuzzerMiddle) {
					timerIDBuzzerHigh = schedule_timer(2,(Event_t){_smBuzzer,evTimerBuzzerMiddle});
					BUZZER1_NegVal();
				}
				if(event.eventName == evTimerBuzzerLow || event.eventName == evBuzzerLow) {
					timerIDBuzzerHigh = schedule_timer(4,(Event_t){_smBuzzer,evTimerBuzzerLow});
					BUZZER1_NegVal();
				}
				break;

		}
	}
}

