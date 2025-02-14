#include "blink_task.h"

#include "cybsp.h"
#include "cyhal.h"
#include "FreeRTOS.h"
#include "cycfg.h"


void blink_task(void* param) {
  /* Suppress warning for unused parameter */
  (void) param;



  /* Repeatedly running part of the task */
  for (;;) {
    cyhal_gpio_toggle(CYBSP_USER_LED1);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
