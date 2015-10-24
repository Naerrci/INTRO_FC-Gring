

#ifndef SOURCES_COMMON_BUZZER_H_
#define SOURCES_COMMON_BUZZER_H_

#include "Event.h"

typedef enum {
	stBuzzerNull,
	stBuzzerIdle,
	stSound
}StateSmBuzzer_t;

typedef enum {
	High,
	Middle,
	Low
} BuzzerFreq_t;

void startBuzzer(BuzzerFreq_t freq, int time);

void smBuzzer(Event_t event);




#endif /*SOURCES_COMMON_BUZZER_H_*/

