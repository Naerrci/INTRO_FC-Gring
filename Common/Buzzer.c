/*
 * Buzzer.c
 *
 *  Created on: 22.10.2015
 *      Author: Simon
 */

#include "Buzzer.h"
#include "BUZZER1.h"
#include "timer.h"

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
			if(event.eventName == evTimerBuzzerHigh) {
				state = stSound;
				stateChanged = 1;
			}
			if(event.eventName == evTimerBuzzerMiddle) {
				state = stSound;
				stateChanged = 1;
			}
			if(event.eventName == evTimerBuzzerLow) {
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

				}
				break;

		}
	}
}

