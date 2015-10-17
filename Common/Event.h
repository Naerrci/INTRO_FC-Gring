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

typedef struct EVNT_Handle {
	enum {
		_smUnknown,
		_smAll,
		_smKeyA,
		_smROBO,
		_smFRDM
	} smName;

	enum {
		evNull,
		evStart,      /*!< System startup Event */
			// Events for Robo
		#if PL_CONFIG_IS_ROBO
			evBt1Pressed,
			evBt1Released,
			evTimer,
		#endif
		// Events for FRDM
		#if PL_CONFIG_IS_FRDM
			evKeyAPressed,
			evKeyAReleased,
			evKeyALongPressed,
			evKeyADoubleClick,
			evKeyAClick,

			evKeyBPressed,
			evKeyBReleased,

			evKeyCPressed,
			evKeyCReleased,

			evKeyDPressed,
			evKeyDReleased,

			evKeyEPressed,
			evKeyEReleased,

			evKeyFPressed,
			evKeyFReleased,

			evKeyGPressed,
			evKeyGReleased,

			evTimer,

			evTimerKeyPressedDeb,
			evTimerKeyReleasedDeb,
			evTimerKeyReleasedDebReturn,
			evTimerNoDoubleClick,
			evTimerDoubleClickDeb,
			evTimerLongPressed,
			evReturn,

		#endif
			/*!< \todo Your events here */
			EVNT_NOF_EVENTS /*!< Must be last one! */
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
