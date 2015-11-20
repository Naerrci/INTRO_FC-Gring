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
#define PL_CONFIG_NOF_KEYS      	(0)
#define PL_CONFIG_NOF_EINT      	(1)
#define PL_CONFIG_NOF_BUZZ      	(1)
#define PL_CONFIG_NOF_LCD       	(0)
#define PL_CONFIG_NOF_SNAKE     	(0)
#define PL_CONFIG_NOF_SHELL     	(1)
#define PL_CONFIG_NOF_BLUETOOTH 	(1)
#define PL_CONFIG_NOF_USB_CDC   	(1)
#define PL_CONFIG_NOF_SHELL_QUEUE   (1)
#define PL_CONFIG_NOF_NVM			(1)

#define PL_CONFIG_IS_FRDM			(0)
#define PL_CONFIG_IS_ROBO			(1)


/* Name des users
 * Dies muss lokal angepasst werden und dann nicht committed werden */
#define PL_PERSONAL_NAME_IS_JON					(1)
#define PL_PERSONAL_NAME_IS_SIMON				(0)
#define PL_PERSONAL_NAME_IS_MARCO				(0)

#endif /* SOURCES_PLATFORM_LOCAL_H_ */
