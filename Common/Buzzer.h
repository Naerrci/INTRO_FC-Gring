
#include "Event.h"

typedef enum {
	stBuzzerNull,
	stBuzzerIdle,
	stSound
}StateSmBuzzer_t;

void smBuzzer(Event_t event);
