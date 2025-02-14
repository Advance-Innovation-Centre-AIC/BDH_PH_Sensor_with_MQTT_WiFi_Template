/*
 * bt_task.c
 *
 *  Created on: Feb 13, 2023
 *      Author: nipon
 */

#include "bt_task.h"

#define GPIO_INTERRUPT_PRIORITY (7u)

QueueHandle_t xQueueBT1 = NULL;
QueueHandle_t xQueueBT2 = NULL;


static cyhal_gpio_callback_data_t gpio_btn1_callback_data;
static cyhal_gpio_callback_data_t gpio_btn2_callback_data;
//volatile uint8_t bt1_intr_flag = false;
//volatile uint8_t bt2_intr_flag = false;

static void bt1_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event);
static void bt2_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event);


static void bt_init(){

	cy_rslt_t result;

	/* Initialize the user button2 */
	result = cyhal_gpio_init(CYBSP_USER_BTN1, CYHAL_GPIO_DIR_INPUT,
					CYBSP_USER_BTN_DRIVE, CYBSP_BTN_OFF);
	/* User button init failed. Stop program execution */
	CY_ASSERT(CY_RSLT_SUCCESS == result);

	/* Initialize the user button2 */
	result = cyhal_gpio_init(CYBSP_USER_BTN2, CYHAL_GPIO_DIR_INPUT,
					CYBSP_USER_BTN_DRIVE, CYBSP_BTN_OFF);
	/* User button init failed. Stop program execution */
	CY_ASSERT(CY_RSLT_SUCCESS == result);


	 /* Configure GPIO interrupt */
	gpio_btn1_callback_data.callback = bt1_interrupt_handler;
	cyhal_gpio_register_callback(CYBSP_USER_BTN1,
								 &gpio_btn1_callback_data);
	cyhal_gpio_enable_event(CYBSP_USER_BTN1, CYHAL_GPIO_IRQ_FALL,
								 GPIO_INTERRUPT_PRIORITY, true);

	gpio_btn2_callback_data.callback = bt2_interrupt_handler;
	cyhal_gpio_register_callback(CYBSP_USER_BTN2,
								 &gpio_btn2_callback_data);
	cyhal_gpio_enable_event(CYBSP_USER_BTN2, CYHAL_GPIO_IRQ_FALL,
								 GPIO_INTERRUPT_PRIORITY, true);

}


void bt_task(void* param){

	/* Suppress warning for unused parameter */
	(void) param;

    xQueueBT1 = xQueueCreate( 1, sizeof(uint8_t));
    xQueueBT2 = xQueueCreate( 1, sizeof(uint8_t));


    /*Button initial*/
    bt_init();

	/* Repeatedly running part of the task */
	for (;;) {
/*
		if (true == bt1_intr_flag)
		{
			//	printf("user_btn1 is pressed\r\n");
			 uint8_t bt1 = 1;
			 if (xQueueBT1 != NULL) {
				 if (!xQueueSend(xQueueBT1, &bt1, pdMS_TO_TICKS(100))) {
					 //	puts("Failed to send item to queue within 1ms");
				 }
			 }
			 bt1_intr_flag = false;
		}

		if (true == bt2_intr_flag)
		{
			//	printf("user_btn2 is pressed\r\n");
			uint8_t bt2 = 1;
			if (xQueueBT2 != NULL) {
				if (!xQueueSend(xQueueBT2, &bt2, pdMS_TO_TICKS(100))) {
					// puts("Failed to send item to queue within 1ms");
				}
			}
			bt2_intr_flag = false;
		}
*/

		//cyhal_gpio_toggle(CYBSP_USER_LED);
		vTaskDelay(pdMS_TO_TICKS(1000));

	}

	vTaskDelete(NULL);
}


static void bt1_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event)
{
//	bt1_intr_flag = true;

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    /* Send the command and data to publisher task over the queue */
	uint8_t bt = 1;
	if(xQueueBT1 != NULL){
		xQueueSendFromISR(xQueueBT1, &bt, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}

}

static void bt2_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event)
{
//	bt2_intr_flag = true;

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    /* Send the command and data to publisher task over the queue */
	uint8_t bt = 1;
	xQueueSendFromISR(xQueueBT2, &bt, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}
