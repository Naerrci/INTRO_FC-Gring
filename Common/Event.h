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

#if PL_CONFIG_HAS_EVENTS

#define MAXEVENT 16

typedef struct EVNT_Handle {
	enum {
		_smUnknown,
		_smAll,
		_smROBO,
		_smFRDM
	} smName;

	enum {
		evNull,
		evStartUp,      /*!< System startup Event */
			// Events for Robo
		#ifdef PL_CONFIG_HAS_EINT
			evBt1Pressed,
			evBt1Released,
			evTimer,
		#endif
		// Events for FRDM
		#ifdef PL_CONFIG_HAS_KEYS
			evKeyAPressed,
			evKeyAReleased,
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
