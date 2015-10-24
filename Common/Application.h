/*
 * Application.h
 *
 *  Created on: 29.09.2015
 *      Author: Jon
 */

#ifndef SOURCES_COMMON_APPLICATION_H_
#define SOURCES_COMMON_APPLICATION_H_

#include "Event.h"

/*
** ===================================================================
**     Method      :  void APP_Run(void)
**     Description :
**         This lets the application running.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void APP_Run(void);

void smFRDM(Event_t event);

void smROBO(Event_t event);



#endif /* SOURCES_COMMON_APPLICATION_H_ */
