/*
 * common.h
 *
 *  Created on: Feb 10, 2023
 *      Author: nipon
 */

#ifndef CONFIGS_COMMON_H_
#define CONFIGS_COMMON_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "data_task.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "queue.h"
#include "task.h"
#include "cybsp.h"
#include "cyhal.h"
#include "cycfg.h"
#include "cy_retarget_io.h"
#include "cy_rgb_led.h"

#include "mtb_bmx160.h"

#include "biil_config.h"
#include "data_task.h"
#include "bt_task.h"
#include "ph_task.h"
#include "xensiv_task.h"
#include "orientation9axis_task.h"
#include "audio_task.h"


typedef struct
{
	float pressure;
	float temperature;
}__attribute__ ((packed)) data_xensiv_t;


/*Data packet of CY8CKIT-62S2-40312*/
typedef struct
{
	uint32_t seq;
	uint8_t user_bt1;
	uint8_t user_bt2;
	float ph_value;
	uint8_t capsense_bt1;
	uint8_t capsense_bt2;
	uint16_t capsense_slider;
}__attribute__ ((packed)) data_packet1_t;


/*Data packet of CY8CKIT-028-SENSE*/
typedef struct
{
	uint32_t seq;
	float  pressure;
	float  temperature;
	mtb_bmx160_data_t bmx160_data;
	uint32_t analog_mic;
	uint32_t digital_mic;
}__attribute__ ((packed)) data_packet2_t;


extern QueueHandle_t xQueueBT1;
extern QueueHandle_t xQueueBT2;

extern QueueHandle_t xQueuePH;

extern QueueHandle_t xQueueCapsenseBt1;
extern QueueHandle_t xQueueCapsenseBt2;
extern QueueHandle_t xQueueCapsenseSlider;

extern QueueHandle_t xQueueXensiv;
extern QueueHandle_t xQueueOrientation9axis;
extern QueueHandle_t xQueueAudio;

extern QueueHandle_t xQueueData1MQTT;
extern QueueHandle_t xQueueData2MQTT;


#endif /* CONFIGS_COMMON_H_ */
