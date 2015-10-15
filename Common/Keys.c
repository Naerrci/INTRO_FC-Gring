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
	short mask = 0;
	mask = (KEY7_Get() << 6 | KEY6_Get() << 5 | KEY5_Get() << 4 | KEY4_Get() << 3 |
					KEY3_Get() << 2 | KEY2_Get() << 1 | KEY1_Get());


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
		EVNT_SetEvent(evBt1Pressed);
	} else {
		EVNT_SetEvent(evBt1Released);
	}
}
#endif
