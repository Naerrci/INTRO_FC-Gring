/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

#include "Platform.h" /* interface to the platform */
#if PL_CONFIG_HAS_SEMAPHORE
#include "FRTOS1.h"
#include "Sem.h"
#include "LED.h"

#define USE_SEMAPHORES 1

#if USE_SEMAPHORES
static portTASK_FUNCTION(vSlaveTask, pvParameters) {
  /*! \todo Implement functionality */
  xSemaphoreHandle sem;

  sem = (xSemaphoreHandle)pvParameters;
  for(;;) {
    if (sem != NULL) {
      if (FRTOS1_xSemaphoreTake(sem, portMAX_DELAY)==pdTRUE) {
        LED1_Neg();
      }
    }
  }
}

static portTASK_FUNCTION(vMasterTask, pvParameters) {
  /*! \todo Implement functionality */
  xSemaphoreHandle sem = NULL;

  (void)pvParameters; /* parameter not used */
  sem = FRTOS1_xSemaphoreCreateBinary();
  if (sem==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  FRTOS1_vQueueAddToRegistry(sem, "IPC_Sem");
  /* create slave task */
  if (FRTOS1_xTaskCreate(vSlaveTask, "Slave", configMINIMAL_STACK_SIZE, sem, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  for(;;) {
    if (sem != NULL) { /* valid semaphore? */
      (void)xSemaphoreGive(sem); /* give control to other task */
      FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
    }
  }
}
#endif /* USE_SEMAPHORES */

void SEM_Deinit(void) {
  //FRTOS1_vSemaphoreDelete(sem);
  //sem = NULL;
}

/*! \brief Initializes module */
void SEM_Init(void) {
#if USE_SEMAPHORES
  if (FRTOS1_xTaskCreate(vMasterTask, "Master", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}
#endif /* PL_CONFIG_HAS_SEMAPHORE */
