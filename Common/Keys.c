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

#if PL_CONFIG_HAS_KEYS
void KEY_Scan(void) {
  /*! \todo check handling all keys */
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


#if PL_CONFIG_HAS_EINT
void KEY_EInt(void) {
	if(EInt1_GetVal() == 0){
		EVNT_SetEvent(EVENT_BT1_PRESSED);
	} else {
		EVNT_SetEvent(EVENT_BT1_RELEASED);
	}
}
#endif
