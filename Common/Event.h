/**
 * \file
 * \brief Event driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic event driver. We are using numbered events starting with zero.
 * EVNT_HandleEvent() can be used to process the pending events. Note that the event with the number zero
 * has the highest priority and will be handled first
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "Platform.h"
#include "Platform_local.h"

#if PL_CONFIG_HAS_EVENTS

#define MAXEVENT 16

typedef struct Event_ {
	enum {
		_smUnknown,
		_smAll,
		#if PL_CONFIG_IS_FRDM
		_smKey,
		_smKeyA,
		_smKeyB,
		_smKeyC,
		_smKeyD,
		_smKeyE,
		_smKeyF,
		_smKeyG,
		_smFRDM,
		#endif

		#if PL_CONFIG_IS_ROBO
		_smROBO,
		_smEInt,
		_smBuzzer
		#endif
	} smName;

	enum {
		evNull,
		evStart,      /*!< System startup Event */
			// Events for Robo
		#if PL_CONFIG_IS_ROBO
			evBt1Pressed,
			evBt1Released,
			evBt1LongPressed,
			evBt1DoubleClick,
			evBt1Click,

			evTimerNoDoubleClick,
			evTimerLongPressed,
			evReturn,

			// Buzzer Events
			evBuzzerHigh,
			evBuzzerMiddle,
			evBuzzerLow,
			evTimerBuzzerHigh,
			evTimerBuzzerMiddle,
			evTimerBuzzerLow,
			evBuzzerStop,

			// LineSensor Events
			evRefStartStopCalibration,

			// shit events
			evTimer,
		#endif
		// Events for FRDM
		#if PL_CONFIG_IS_FRDM
			evKeyPressed,
			evKeyReleased,

			evKeyAPressed,
			evKeyAReleased,
			evKeyALongPressed,
			evKeyADoubleClick,
			evKeyAClick,

			evKeyBPressed,
			evKeyBReleased,
			evKeyBLongPressed,
			evKeyBDoubleClick,
			evKeyBClick,

			evKeyCPressed,
			evKeyCReleased,
			evKeyCLongPressed,
			evKeyCDoubleClick,
			evKeyCClick,

			evKeyDPressed,
			evKeyDReleased,
			evKeyDLongPressed,
			evKeyDDoubleClick,
			evKeyDClick,

			evKeyEPressed,
			evKeyEReleased,
			evKeyELongPressed,
			evKeyEDoubleClick,
			evKeyEClick,

			evKeyFPressed,
			evKeyFReleased,
			evKeyFLongPressed,
			evKeyFDoubleClick,
			evKeyFClick,

			evKeyGPressed,
			evKeyGReleased,
			evKeyGLongPressed,
			evKeyGDoubleClick,
			evKeyGClick,

			evTimer,

			evTimerKeyPressedDeb,
			evTimerKeyReleasedDeb,
			evTimerKeyReleasedDebReturn,
			evTimerNoDoubleClick,
			evTimerDoubleClickDeb,
			evTimerLongPressed,
			evReturn,

			#if PL_CONFIG_HAS_SNAKE
			  evSnakeStartPause,
			  evSnakeUp,
			  evSnakeDown,
			  evSnakeLeft,
			  evSnakeRight,
			#endif

		#endif
			/*!< \todo Your events here */
			//EVNT_NOF_EVENTS /*!< Must be last one! */
			  EVNT_LAST
	} eventName;
} Event_t;

/*!
 * \brief Sets an event.
 * \param[in] event The handle of the event to set.
 */
void EVNT_SetEvent(Event_t event);

/*!
 * \brief Clears an event.
 * \param[in] event The event handle of the event to clear.
 */
Event_t EVNT_GetEvent();

short EVNT_EventsInQueue();

/*! \brief Event module initialization */
void EVNT_Init(void);

/*! \brief Event module de-initialization */
void EVNT_Deinit(void);

#endif /* PL_HAS_EVENTS */


#endif /* EVENT_H_ */
