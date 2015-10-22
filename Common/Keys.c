/**
 * \file
 * \brief Key/Switch driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 7 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_CONFIG_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_CONFIG_HAS_EINT
	#include "EInt1.h"
#endif

#include "timer.h"

#define KeyAMask (0x01 << 0)
#define KeyBMask (0x01 << 1)
#define KeyCMask (0x01 << 2)
#define KeyDMask (0x01 << 3)
#define KeyEMask (0x01 << 4)
#define KeyFMask (0x01 << 5)
#define KeyGMask (0x01 << 6)

#if PL_CONFIG_HAS_KEYS
void KEY_Scan(void) {
	static short oldMask = 0;
	short mask = (KEY7_Get() << 6 | KEY6_Get() << 5 | KEY5_Get() << 4 | KEY4_Get() << 3 |
					KEY3_Get() << 2 | KEY2_Get() << 1 | KEY1_Get());
	if((oldMask ^ mask) == 0 )
		return;
	else {
		switch(oldMask ^ mask) {
		case KeyAMask:
			if(mask & KeyAMask)
				EVNT_SetEvent((Event_t){_smKeyA,evKeyAPressed});
			else
				EVNT_SetEvent((Event_t){_smKeyA,evKeyAReleased});
			break;

		case KeyBMask:
			if(mask & KeyBMask)
				EVNT_SetEvent((Event_t){_smKeyB,evKeyBPressed});
			else
				EVNT_SetEvent((Event_t){_smKeyB,evKeyBReleased});
			break;

		case KeyCMask:
			if(mask & KeyCMask)
				EVNT_SetEvent((Event_t){_smFRDM,evKeyCPressed});
			else
				EVNT_SetEvent((Event_t){_smFRDM,evKeyCReleased});
			break;

		case KeyDMask:
			if(mask & KeyDMask)
				EVNT_SetEvent((Event_t){_smFRDM,evKeyDPressed});
			else
				EVNT_SetEvent((Event_t){_smFRDM,evKeyDReleased});
			break;

		case KeyEMask:
			if(mask & KeyEMask)
				EVNT_SetEvent((Event_t){_smFRDM,evKeyEPressed});
			else
				EVNT_SetEvent((Event_t){_smFRDM,evKeyEReleased});
			break;

		case KeyFMask:
			if(mask & KeyFMask)
				EVNT_SetEvent((Event_t){_smFRDM,evKeyFPressed});
			else
				EVNT_SetEvent((Event_t){_smFRDM,evKeyFReleased});
			break;

		case KeyGMask:
			if(mask & KeyGMask)
				EVNT_SetEvent((Event_t){_smFRDM,evKeyGPressed});
			else
				EVNT_SetEvent((Event_t){_smFRDM,evKeyGReleased});
			break;
		}
	}
	oldMask = mask;
}

/*! \brief Key driver initialization */
void KEY_Init(void) {
  /* nothing needed for now */
}

/*! \brief Key driver de-initialization */
void KEY_Deinit(void) {
  /* nothing needed for now */
}
#endif

void smKeyA(Event_t event) {
	static StateSmKey_t state;
	StateSmKey_t oldState = state;

	static int timerIDKeyPressedDeb = -2;
	static int timerIDKeyReleasedDeb = -2;
	static int timerIDKeyReleasedDebReturn = -2;
	static int timerIDNoDoubleClick = -2;
	static int timerIDDoubleClickDeb = -2;
	static int timerIDLongPressed = -2;

	switch(state) {
	case stNull:
		if(event.eventName == evStart) {
			state = stIdle;
		}
		break;

	case stIdle:
		if(event.eventName == evKeyAPressed) {
			state = stKeyPressed;
		}
		break;

	case stKeyPressed:
		if(event.eventName == evTimerKeyPressedDeb) {
			state = stKeyPressedDeb;
		}
		if(event.eventName == evTimerDoubleClickDeb) {
			state = stDoubleClick;
		}
		break;

	case stKeyPressedDeb:
		if(event.eventName == evTimerLongPressed) {
			state = stKeyLongPressed;
		}
		if(event.eventName == evKeyAReleased) {
			state = stKeyReleased;
		}
		break;

	case stKeyLongPressed:
		if(event.eventName == evKeyAReleased) {
			state = stKeyReleased;
		}
		break;

	case stKeyReleased:
		if(event.eventName == evTimerKeyReleasedDeb) {
			state = stKeyReleasedDeb;
		}
		if(event.eventName == evTimerKeyReleasedDebReturn) {
			state = stIdle;
		}
		break;

	case stKeyReleasedDeb:
		if(event.eventName == evKeyAPressed) {
			state = stKeyPressed;
		}
		if(event.eventName == evTimerNoDoubleClick) {
			state = stClick;
		}
		break;

	case stClick:
		if(event.eventName == evReturn) {
			state = stIdle;
		}
		break;

	case stDoubleClick:
		if(event.eventName == evKeyAReleased) {
			state = stKeyReleased;
		}
		break;
	}

	if(oldState != state) {
		switch(state) {
		case stIdle:
			break;

		case stKeyPressed:
			EVNT_SetEvent((Event_t){_smFRDM,evKeyAPressed});
			if(oldState == stIdle) {
				timerIDKeyPressedDeb = schedule_timer(DEBOUNCE_TIME,(Event_t){_smKeyA,evTimerKeyPressedDeb});
			}
			if(oldState == stKeyReleasedDeb) {
				EVNT_SetEvent((Event_t){_smFRDM,evKeyADoubleClick});
				timerIDDoubleClickDeb = schedule_timer(DEBOUNCE_TIME,(Event_t){_smKeyA,evTimerDoubleClickDeb});
			}
			break;

		case stKeyPressedDeb:
			timerIDLongPressed = schedule_timer(LONG_PRESSED_TIME,(Event_t){_smKeyA,evTimerLongPressed});
			break;

		case stKeyLongPressed:
			EVNT_SetEvent((Event_t){_smFRDM,evKeyALongPressed});
			break;

		case stKeyReleased:
			EVNT_SetEvent((Event_t){_smFRDM,evKeyAReleased});
			if(oldState == stKeyPressedDeb) {
				timerIDKeyReleasedDeb = schedule_timer(DEBOUNCE_TIME,(Event_t){_smKeyA,evTimerKeyReleasedDeb});
			}
			if(oldState == stKeyLongPressed | oldState == stDoubleClick) {
				timerIDKeyReleasedDebReturn = schedule_timer(DEBOUNCE_TIME,(Event_t){_smKeyA,evTimerKeyReleasedDebReturn});
			}
			break;

		case stKeyReleasedDeb:
			timerIDNoDoubleClick = schedule_timer(DOUBLE_CLICK_TIME - 2 * DEBOUNCE_TIME,(Event_t){_smKeyA,evTimerNoDoubleClick});
			break;

		case stDoubleClick:
			break;

		case stClick:
			EVNT_SetEvent((Event_t){_smKeyA,evReturn});
			EVNT_SetEvent((Event_t){_smFRDM,evKeyAClick});
			break;
		}

		switch(oldState) {

		case stIdle:
			break;

		case stKeyPressed:
			break;

		case stKeyPressedDeb:
			if(event.eventName == evKeyAReleased) {
				unschedule_timer(timerIDLongPressed);
			}
			break;

		case stKeyLongPressed:
			break;

		case stKeyReleased:
			break;

		case stKeyReleasedDeb:
			if(event.eventName == evKeyAPressed) {
				unschedule_timer(timerIDNoDoubleClick);
			}
			break;

		case stDoubleClick:
			break;

		case stClick:
			break;
		}
	}
}

void smKeyB(Event_t event) {
	static StateSmKey_t state;
	StateSmKey_t oldState = state;

	static int timerIDKeyPressedDeb = -2;
	static int timerIDKeyReleasedDeb = -2;
	static int timerIDKeyReleasedDebReturn = -2;
	static int timerIDNoDoubleClick = -2;
	static int timerIDDoubleClickDeb = -2;
	static int timerIDLongPressed = -2;

	switch(state) {
	case stNull:
		if(event.eventName == evStart) {
			state = stIdle;
		}
		break;

	case stIdle:
		if(event.eventName == evKeyBPressed) {
			state = stKeyPressed;
		}
		break;

	case stKeyPressed:
		if(event.eventName == evTimerKeyPressedDeb) {
			state = stKeyPressedDeb;
		}
		if(event.eventName == evTimerDoubleClickDeb) {
			state = stDoubleClick;
		}
		break;

	case stKeyPressedDeb:
		if(event.eventName == evTimerLongPressed) {
			state = stKeyLongPressed;
		}
		if(event.eventName == evKeyBReleased) {
			state = stKeyReleased;
		}
		break;

	case stKeyLongPressed:
		if(event.eventName == evKeyBReleased) {
			state = stKeyReleased;
		}
		break;

	case stKeyReleased:
		if(event.eventName == evTimerKeyReleasedDeb) {
			state = stKeyReleasedDeb;
		}
		if(event.eventName == evTimerKeyReleasedDebReturn) {
			state = stIdle;
		}
		break;

	case stKeyReleasedDeb:
		if(event.eventName == evKeyBPressed) {
			state = stKeyPressed;
		}
		if(event.eventName == evTimerNoDoubleClick) {
			state = stClick;
		}
		break;

	case stClick:
		if(event.eventName == evReturn) {
			state = stIdle;
		}
		break;

	case stDoubleClick:
		if(event.eventName == evKeyBReleased) {
			state = stKeyReleased;
		}
		break;
	}

	if(oldState != state) {
		switch(state) {
		case stIdle:
			break;

		case stKeyPressed:
			EVNT_SetEvent((Event_t){_smFRDM,evKeyBPressed});
			if(oldState == stIdle) {
				timerIDKeyPressedDeb = schedule_timer(DEBOUNCE_TIME,(Event_t){_smKeyB,evTimerKeyPressedDeb});
			}
			if(oldState == stKeyReleasedDeb) {
				EVNT_SetEvent((Event_t){_smFRDM,evKeyBDoubleClick});
				timerIDDoubleClickDeb = schedule_timer(DEBOUNCE_TIME,(Event_t){_smKeyB,evTimerDoubleClickDeb});
			}
			break;

		case stKeyPressedDeb:
			timerIDLongPressed = schedule_timer(LONG_PRESSED_TIME,(Event_t){_smKeyB,evTimerLongPressed});
			break;

		case stKeyLongPressed:
			EVNT_SetEvent((Event_t){_smFRDM,evKeyBLongPressed});
			break;

		case stKeyReleased:
			EVNT_SetEvent((Event_t){_smFRDM,evKeyBReleased});
			if(oldState == stKeyPressedDeb) {
				timerIDKeyReleasedDeb = schedule_timer(DEBOUNCE_TIME,(Event_t){_smKeyB,evTimerKeyReleasedDeb});
			}
			if(oldState == stKeyLongPressed | oldState == stDoubleClick) {
				timerIDKeyReleasedDebReturn = schedule_timer(DEBOUNCE_TIME,(Event_t){_smKeyB,evTimerKeyReleasedDebReturn});
			}
			break;

		case stKeyReleasedDeb:
			timerIDNoDoubleClick = schedule_timer(DOUBLE_CLICK_TIME - 2 * DEBOUNCE_TIME,(Event_t){_smKeyB,evTimerNoDoubleClick});
			break;

		case stDoubleClick:
			break;

		case stClick:
			EVNT_SetEvent((Event_t){_smKeyB,evReturn});
			EVNT_SetEvent((Event_t){_smFRDM,evKeyBClick});
			break;
		}

		switch(oldState) {

		case stIdle:
			break;

		case stKeyPressed:
			break;

		case stKeyPressedDeb:
			if(event.eventName == evKeyBReleased) {
				unschedule_timer(timerIDLongPressed);
			}
			break;

		case stKeyLongPressed:
			break;

		case stKeyReleased:
			break;

		case stKeyReleasedDeb:
			if(event.eventName == evKeyBPressed) {
				unschedule_timer(timerIDNoDoubleClick);
			}
			break;

		case stDoubleClick:
			break;

		case stClick:
			break;
		}
	}
}


#if PL_CONFIG_HAS_EINT
void KEY_EInt(void) {
	if(EInt1_GetVal() == 0){
		EVNT_SetEvent((Event_t){_smROBO,evBt1Pressed});
	} else {
		EVNT_SetEvent((Event_t){_smROBO,evBt1Released});
	}
}
#endif
