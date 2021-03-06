/*
 * LineFollow.c
 *
 *  Created on: Feb 15, 2013
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_CONFIG_HAS_LINE_FOLLOW
#include "LineFollow.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "Shell.h"
#include "Motor.h"
#include "Reflectance.h"
#include "Turn.h"
#include "WAIT1.h"
#include "Pid.h"
#include "Drive.h"
#include "Turn.h"
#include "Shell.h"
#include "Maze.h"
#if PL_CONFIG_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_CONFIG_HAS_DRIVE
  #include "Drive.h"
#endif



#define LINE_DEBUG      1   /* careful: this will slow down the PID loop frequency! */
#define LINE_FOLLOW_FW  1   /* test setting to do forward line following */

typedef enum {
  STATE_IDLE,              /* idle, not doing anything */
  STATE_FOLLOW_SEGMENT,    /* line following segment, going forward */
  STATE_TURN,              /* reached an intersection, turning around */
  STATE_FINISHED,          /* reached finish area */
  STATE_STOP               /* stop the engines */
} StateType;

static volatile StateType LF_currState = STATE_IDLE;
static volatile bool LF_stopIt = FALSE;

void LF_StartFollowing(void) {
  PID_Start();
  LF_currState = STATE_FOLLOW_SEGMENT;
  DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode */
}

void LF_StopFollowing(void) {
  LF_stopIt = TRUE;
  LF_currState = STATE_IDLE;
}

static void StateMachine(void);

static void ChangeState(StateType newState) {
  LF_currState = newState;
  StateMachine(); /* need to handle new state */
}

/*!
 * \brief follows a line segment.
 * \return Returns TRUE if still on line segment
 */
static bool FollowSegment(bool forward) {
  uint16_t currLine;
  REF_LineKind currLineKind;

  currLine = REF_GetLineValue();
  currLineKind = REF_GetLineKind();
  if (currLineKind==REF_LINE_STRAIGHT) {
    PID_Line(currLine, REF_MIDDLE_LINE_VALUE); /* move along the line */
    return TRUE;
  } else {
    return FALSE; /* intersection/change of direction or not on line any more */
  }
}

static void StateMachine(void) {
	static bool maze_finished = FALSE;
  switch (LF_currState) {
    case STATE_IDLE:
      break;
    case STATE_FOLLOW_SEGMENT:
      if (!FollowSegment(LINE_FOLLOW_FW)) {
        LF_currState = STATE_TURN; /* stop if we do not have a line any more */
        //SHELL_SendString((unsigned char*)"No line, stopped!\r\n");
      }
      break;
    case STATE_TURN:
    	MAZE_EvaluteTurn(&maze_finished);
    	if(!maze_finished){
    		//TURN_Turn(TURN_STEP_LINE_FW,NULL);
    		LF_currState = STATE_FOLLOW_SEGMENT;
    	}
    	else
    		LF_currState = STATE_STOP;

      break;
    case STATE_FINISHED:
      /*! \todo Handle maze finished? */
      break;
    case STATE_STOP:
      SHELL_SendString("LINE: Stop!\r\n");
      TURN_Turn(TURN_STOP, NULL);
      LF_currState = STATE_IDLE;
      break;
  } /* switch */
}

bool LF_IsFollowing(void) {
  return LF_currState!=STATE_IDLE;
}

static void LineTask (void *pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    if (LF_stopIt) {
      ChangeState(STATE_STOP);
      LF_stopIt = FALSE;
    }
    StateMachine();
    FRTOS1_vTaskDelay(5/portTICK_RATE_MS);
  }
}

static void LF_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"line", (unsigned char*)"Group of line following commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows line help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  start|stop", (unsigned char*)"Starts or stops line following\r\n", io->stdOut);
}

static void LF_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"line follow", (unsigned char*)"\r\n", io->stdOut);
  switch (LF_currState) {
    case STATE_IDLE: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"IDLE\r\n", io->stdOut);
      break;
    case STATE_FOLLOW_SEGMENT: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"FOLLOW_SEGMENT\r\n", io->stdOut);
      break;
    case STATE_STOP: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"STOP\r\n", io->stdOut);
      break;
    case STATE_TURN: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"TURN\r\n", io->stdOut);
      break;
    case STATE_FINISHED: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"FINISHED\r\n", io->stdOut);
      break;
    default: 
      CLS1_SendStatusStr((unsigned char*)"  state", (unsigned char*)"UNKNOWN\r\n", io->stdOut);
      break;
  } /* switch */
}

uint8_t LF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"line help")==0) {
    LF_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"line status")==0) {
    LF_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"line start")==0) {
    LF_StartFollowing();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"line stop")==0) {
    LF_StopFollowing();
    *handled = TRUE;
  }
  return res;
}

void LF_Deinit(void) {
  /* nothing needed */
}

void LF_Init(void) {
  LF_currState = STATE_IDLE;
  if (FRTOS1_xTaskCreate(LineTask, "Line", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_CONFIG_HAS_LINE_FOLLOW */
