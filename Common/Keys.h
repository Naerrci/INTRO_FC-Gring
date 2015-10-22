/**
 * \file
 * \brief Key/switch driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 4 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#ifndef KEYS_H_
#define KEYS_H_

#include "Platform.h"
#include "Event.h"

#define LONG_PRESSED_TIME	500
#define DOUBLE_CLICK_TIME	200

#if PL_CONFIG_HAS_KEYS

#define DEBOUNCE_TIME		30

#define smKeyInit(key)	((SmKey_t){stNull,stNull,\
						(Event_t){_smKey##key,evNull},\
						(Event_t){_smKey##key,evReturn},\
						(Event_t){_smFRDM,evKey##key##Pressed},\
						(Event_t){_smFRDM,evKey##key##Released},\
						(Event_t){_smFRDM,evKey##key##LongPressed},\
						(Event_t){_smFRDM,evKey##key##DoubleClick},\
						(Event_t){_smFRDM,evKey##key##Click},\
						IdNull,IdNull,IdNull,IdNull,IdNull,IdNull})

typedef enum {
	stNull,
	stIdle,
	stKeyPressed,
	stKeyPressedDeb,
	stKeyLongPressed,
	stKeyReleased,
	stKeyReleasedDeb,
	stDoubleClick,
	stClick
}StateSmKey_t;

typedef struct {
	StateSmKey_t 	state;
	StateSmKey_t 	oldState;
	Event_t 		evTimerEvent;
	Event_t			evReturn;
	Event_t			evKeyPressed;
	Event_t			evKeyReleased;
	Event_t			evKeyLongPressed;
	Event_t			evKeyDoubleClick;
	Event_t			evKeyClick;
	int 			timerIDKeyPressedDeb;
	int 			timerIDKeyReleasedDeb;
	int 			timerIDKeyReleasedDebReturn;
	int 			timerIDNoDoubleClick;
	int 			timerIDDoubleClickDeb;
	int 			timerIDLongPressed;
} SmKey_t;

typedef enum {
#if PL_CONFIG_NOF_KEYS>=1
  KEY_BTN1, /*!< button 1 */
#endif
#if PL_CONFIG_NOF_KEYS>=2
  KEY_BTN2, /*!< button 2 */
#endif
#if PL_CONFIG_NOF_KEYS>=3
  KEY_BTN3, /*!< button 3 */
#endif
#if PL_CONFIG_NOF_KEYS>=4
  KEY_BTN4, /*!< button 4 */
#endif
#if PL_CONFIG_NOF_KEYS>=5
  KEY_BTN5, /*!< button 5 */
#endif
#if PL_CONFIG_NOF_KEYS>=6
  KEY_BTN6, /*!< button 6 */
#endif
#if PL_CONFIG_NOF_KEYS>=7
  KEY_BTN7, /*!< button 7 */
#endif
  KEY_BTN_LAST /*!< must be last */
} KEY_Buttons;

#if PL_CONFIG_NOF_KEYS>=1
  #include "SW1.h"

  #define KEY1_Get()  (!(SW1_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY1_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_CONFIG_NOF_KEYS>=2
  #include "SW2.h"

  #define KEY2_Get()  (!(SW2_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY2_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_CONFIG_NOF_KEYS>=3
  #include "SW3.h"

  #define KEY3_Get()  (!(SW3_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY3_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_CONFIG_NOF_KEYS>=4
  #include "SW4.h"

  #define KEY4_Get()  (!(SW4_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY4_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_CONFIG_NOF_KEYS>=5
  #include "SW5.h"

  #define KEY5_Get()  (!(SW5_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY5_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_CONFIG_NOF_KEYS>=6
  #include "SW6.h"

  #define KEY6_Get()  (!(SW6_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY6_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_CONFIG_NOF_KEYS>=7
  #include "SW7.h"

  #define KEY7_Get()  (!(SW7_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY7_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

/*!
 * \brief Checks the key status and generates the events.
 */
void KEY_Scan(void);

/*! \brief Get access to key hardware. Use KEY_Close() afterwards. */
void KEY_Open(void);

/*! \brief Finish access to key hardware. Called after KEY_Open(). */
void KEY_Close(void);

/*! \brief Key driver initialization */
void KEY_Init(void);

/*! \brief Key driver de-initialization */
void KEY_Deinit(void);

void smKey(Event_t event);

#endif /* PL_HAS_KEYS */

/*! \brief Key interrupt */
#if PL_CONFIG_HAS_EINT

typedef enum {
	stNull,
	stIdle,
	stBt1Pressed,
	stBt1LongPressed,
	stBt1Released,
	stBt1DoubleClick,
	stBt1Click
}StateSmEInt_t;

void KEY_EInt(void);

void smEInt(Event_t event);

#endif


#endif /* KEYS_H_ */
