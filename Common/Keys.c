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
  #include "Keys.h"
#endif

#include "timer.h"


#if PL_CONFIG_HAS_KEYS
#define KeyAMask (0x01 << 0)
#define KeyBMask (0x01 << 1)
#define KeyCMask (0x01 << 2)
#define KeyDMask (0x01 << 3)
#define KeyEMask (0x01 << 4)
#define KeyFMask (0x01 << 5)
#define KeyGMask (0x01 << 6)

bool normalSpeedPressed = 0;
bool fastSpeedPressed = 0;
bool retourSpeedPressed = 0;

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
				EVNT_SetEvent((Event_t){_smKeyA,evKeyPressed});
			else
				EVNT_SetEvent((Event_t){_smKeyA,evKeyReleased});
			break;

		case KeyBMask:
			if(mask & KeyBMask)
				EVNT_SetEvent((Event_t){_smKeyB,evKeyPressed});
			else
				EVNT_SetEvent((Event_t){_smKeyB,evKeyReleased});
			break;

		case KeyCMask:
			if(mask & KeyCMask)
				EVNT_SetEvent((Event_t){_smKeyC,evKeyPressed});
			else
				EVNT_SetEvent((Event_t){_smKeyC,evKeyReleased});
			break;

		case KeyDMask:
			if(mask & KeyDMask)
				EVNT_SetEvent((Event_t){_smKeyD,evKeyPressed});
			else
				EVNT_SetEvent((Event_t){_smKeyD,evKeyReleased});
			break;

		case KeyEMask:
			if(mask & KeyEMask)
				EVNT_SetEvent((Event_t){_smKeyE,evKeyPressed});
			else
				EVNT_SetEvent((Event_t){_smKeyE,evKeyReleased});
			break;

		case KeyFMask:
			if(mask & KeyFMask)
				EVNT_SetEvent((Event_t){_smKeyF,evKeyPressed});
			else
				EVNT_SetEvent((Event_t){_smKeyF,evKeyReleased});
			break;

		case KeyGMask:
			if(mask & KeyGMask)
				EVNT_SetEvent((Event_t){_smKeyG,evKeyPressed});
			else
				EVNT_SetEvent((Event_t){_smKeyG,evKeyReleased});
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

void smKey(Event_t event) {
	static SmKey_t smKeyA;
	static SmKey_t smKeyB;
	static SmKey_t smKeyC;
	static SmKey_t smKeyD;
	static SmKey_t smKeyE;
	static SmKey_t smKeyF;
	static SmKey_t smKeyG;

	// Init state machines with macro
	if(event.eventName == evStart && event.smName == _smKey) {
		smKeyA = smKeyInit(A);
		smKeyB = smKeyInit(B);
		smKeyC = smKeyInit(C);
		smKeyD = smKeyInit(D);
		smKeyE = smKeyInit(E);
		smKeyF = smKeyInit(F);
		smKeyG = smKeyInit(G);
	}

	SmKey_t* pSmKey;

	// Set pointer to correct state machine
	switch(event.smName) {
	case _smKeyA:
		pSmKey = &smKeyA;
		pSmKey->oldState = pSmKey->state;
		break;

	case _smKeyB:
		pSmKey = &smKeyB;
		pSmKey->oldState = pSmKey->state;
		break;

	case _smKeyC:
		pSmKey = &smKeyC;
		pSmKey->oldState = pSmKey->state;
		break;

	case _smKeyD:
		pSmKey = &smKeyD;
		pSmKey->oldState = pSmKey->state;
		break;

	case _smKeyE:
		pSmKey = &smKeyE;
		pSmKey->oldState = pSmKey->state;
		break;

	case _smKeyF:
		pSmKey = &smKeyF;
		pSmKey->oldState = pSmKey->state;
		break;

	case _smKeyG:
		pSmKey = &smKeyG;
		pSmKey->oldState = pSmKey->state;
		break;

	default:
		return;
	}

	// Select next state
	switch(pSmKey->state) {
	case stNull:
		if(event.eventName == evStart) {
			pSmKey->state = stIdle;
		}
		break;

	case stIdle:
		if(event.eventName == evKeyPressed) {
			pSmKey->state = stKeyPressed;
		}
		break;

	case stKeyPressed:
		if(event.eventName == evTimerKeyPressedDeb) {
			pSmKey->state = stKeyPressedDeb;
		}
		if(event.eventName == evTimerDoubleClickDeb) {
			pSmKey->state = stDoubleClick;
		}
		break;

	case stKeyPressedDeb:
		if(event.eventName == evTimerLongPressed) {
			pSmKey->state = stKeyLongPressed;
		}
		if(event.eventName == evKeyReleased) {
			pSmKey->state = stKeyReleased;
		}
		break;

	case stKeyLongPressed:
		if(event.eventName == evKeyReleased) {
			pSmKey->state = stKeyReleased;
		}
		break;

	case stKeyReleased:
		if(event.eventName == evTimerKeyReleasedDeb) {
			pSmKey->state = stKeyReleasedDeb;
		}
		if(event.eventName == evTimerKeyReleasedDebReturn) {
			pSmKey->state = stIdle;
		}
		break;

	case stKeyReleasedDeb:
		if(event.eventName == evKeyPressed) {
			pSmKey->state = stKeyPressed;
		}
		if(event.eventName == evTimerNoDoubleClick) {
			pSmKey->state = stClick;
		}
		break;

	case stClick:
		if(event.eventName == evReturn) {
			pSmKey->state = stIdle;
		}
		break;

	case stDoubleClick:
		if(event.eventName == evKeyReleased) {
			pSmKey->state = stKeyReleased;
		}
		break;
	}

	// do things when entring state
	if(pSmKey->oldState != pSmKey->state) {
		switch(pSmKey->state) {
		case stIdle:
			break;

		case stKeyPressed:
			EVNT_SetEvent(pSmKey->evKeyPressed);
			if(pSmKey->oldState == stIdle) {
				pSmKey->evTimerEvent.eventName = evTimerKeyPressedDeb;
				pSmKey->timerIDKeyPressedDeb = schedule_timer(DEBOUNCE_TIME,pSmKey->evTimerEvent);
			}
			if(pSmKey->oldState == stKeyReleasedDeb) {
				EVNT_SetEvent(pSmKey->evKeyDoubleClick);
				pSmKey->evTimerEvent.eventName = evTimerDoubleClickDeb;
				pSmKey->timerIDDoubleClickDeb = schedule_timer(DEBOUNCE_TIME,pSmKey->evTimerEvent);
			}
			break;

		case stKeyPressedDeb:
			pSmKey->evTimerEvent.eventName = evTimerLongPressed;
			pSmKey->timerIDLongPressed = schedule_timer(LONG_PRESSED_TIME,pSmKey->evTimerEvent);
			break;

		case stKeyLongPressed:
			EVNT_SetEvent(pSmKey->evKeyLongPressed);
			break;

		case stKeyReleased:
			EVNT_SetEvent(pSmKey->evKeyReleased);
			if(pSmKey->oldState == stKeyPressedDeb) {
				pSmKey->evTimerEvent.eventName = evTimerKeyReleasedDeb;
				pSmKey->timerIDKeyReleasedDeb = schedule_timer(DEBOUNCE_TIME,pSmKey->evTimerEvent);
			}
			if(pSmKey->oldState == stKeyLongPressed | pSmKey->oldState == stDoubleClick) {
				pSmKey->evTimerEvent.eventName = evTimerKeyReleasedDebReturn;
				pSmKey->timerIDKeyReleasedDebReturn = schedule_timer(DEBOUNCE_TIME,pSmKey->evTimerEvent);
			}
			break;

		case stKeyReleasedDeb:
			pSmKey->evTimerEvent.eventName = evTimerNoDoubleClick;
			pSmKey->timerIDNoDoubleClick = schedule_timer(DOUBLE_CLICK_TIME - 2 * DEBOUNCE_TIME,pSmKey->evTimerEvent);
			break;

		case stDoubleClick:
			break;

		case stClick:
			EVNT_SetEvent(pSmKey->evReturn);
			EVNT_SetEvent(pSmKey->evKeyClick);
			break;
		}

		// do things when leaving state
		switch(pSmKey->oldState) {

		case stIdle:
			break;

		case stKeyPressed:
			break;

		case stKeyPressedDeb:
			if(event.eventName == evKeyReleased) {
				unschedule_timer(pSmKey->timerIDLongPressed);
			}
			break;

		case stKeyLongPressed:
			break;

		case stKeyReleased:
			break;

		case stKeyReleasedDeb:
			if(event.eventName == evKeyPressed) {
				unschedule_timer(pSmKey->timerIDNoDoubleClick);
			}
			break;

		case stDoubleClick:
			break;

		case stClick:
			break;
		}
	}
}

#endif

#if PL_CONFIG_HAS_EINT

void smEInt(Event_t event){

	static StateSmEInt_t state;
	StateSmEInt_t oldState = state;

	static int timerIDLongPressed = IdNull;
	static int timerIDNoDoubleClick = IdNull;

	switch(state){

	case stNull:
		if(event.eventName == evStart) {
			state = stIdle;
		}
		break;

	case stIdle:
		if(event.eventName == evBt1Pressed) {
			state = stBt1Pressed;
		}
		break;

	case stBt1Pressed:
		if(event.eventName == evBt1Released) {
			state = stBt1Released;
		}
		if(event.eventName == evTimerLongPressed) {
			state = stBt1LongPressed;
		}
		break;

	case stBt1Released:
		if(event.eventName == evTimerNoDoubleClick) {
			state = stIdle;
		}
		if(event.eventName == evBt1Pressed) {
			state = stBt1DoubleClick;
		}
		break;

	case stBt1LongPressed:
		if(event.eventName == evBt1Released) {
			state = stIdle;
		}
		break;

	case stBt1DoubleClick:
		if(event.eventName == evBt1Released) {
			state = stIdle;
		}
		break;

	default:
		state = stIdle;
		break;
	}

	if(oldState != state) {

		switch(state) {

			case stNull:
				break;

			case stIdle:
				break;

			case stBt1Pressed:
				EVNT_SetEvent((Event_t){_smROBO, evBt1Pressed});
				timerIDLongPressed = schedule_timer(LONG_PRESSED_TIME, (Event_t){_smEInt, evTimerLongPressed});
				break;

			case stBt1Released:
				EVNT_SetEvent((Event_t){_smROBO, evBt1Released});
				timerIDNoDoubleClick = schedule_timer(DOUBLE_CLICK_TIME, (Event_t){_smEInt, evTimerNoDoubleClick});
				break;

			case stBt1LongPressed:
				EVNT_SetEvent((Event_t){_smROBO, evBt1LongPressed});
				break;

			case stBt1DoubleClick:
				EVNT_SetEvent((Event_t){_smROBO, evBt1DoubleClick});
				break;

			default:
				state = stIdle;
				break;
		}

		switch(oldState) {

			case stBt1Pressed:
				if(event.eventName == evBt1Released) {
					unschedule_timer(timerIDLongPressed);
				}
				break;

			case stBt1Released:
				if(event.eventName == evBt1Pressed) {
					unschedule_timer(timerIDNoDoubleClick);
				}
				if(event.eventName == evTimerNoDoubleClick) {
					EVNT_SetEvent((Event_t){_smROBO, evBt1Click});
				}
				break;

			case stBt1LongPressed:
				EVNT_SetEvent((Event_t){_smROBO, evBt1Released});
				break;

			case stBt1DoubleClick:
				EVNT_SetEvent((Event_t){_smROBO, evBt1Released});
				break;

			default:
				break;
		}
	}
}

void KEY_EInt(void) {
	if(EInt1_GetVal() == 0){
		EVNT_SetEvent((Event_t){_smEInt,evBt1Pressed});
	} else {
		EVNT_SetEvent((Event_t){_smEInt,evBt1Released});
	}
}
#endif
