/*
 * Platform_local.h
 *
 *  Created on: 29.09.2015
 *      Author: Jon
 */

#ifndef SOURCES_PLATFORM_LOCAL_H_
#define SOURCES_PLATFORM_LOCAL_H_

/* number of LED's on platform */
#define PL_CONFIG_NOF_LED       	(2)
#define PL_CONFIG_NOF_KEYS      	(7)		// 7 Robot Shield
#define PL_CONFIG_NOF_EINT      	(0)
#define PL_CONFIG_NOF_BUZZ      	(0)
#define PL_CONFIG_NOF_LCD       	(0)
#define PL_CONFIG_NOF_SNAKE     	(1)
#define PL_CONFIG_NOF_SHELL     	(1)
#define PL_CONFIG_NOF_BLUETOOTH 	(0)
#define PL_CONFIG_NOF_USB_CDC   	(1)
#define PL_CONFIG_NOF_SHELL_QUEUE   (1)
#define PL_CONFIG_NOF_NVM			(0)

#define PL_CONFIG_IS_FRDM			(1)
#define PL_CONFIG_IS_ROBO			(0)


/* disable macros, defined or not */
//#define PL_CONFIG_DISABLE_HAS_LED



#endif /* SOURCES_PLATFORM_LOCAL_H_ */
