/*
 * data_task.c
 *
 *  Created on: Feb 13, 2023
 *      Author: nipon
 */

//#include <biil_packet_json.h>
#include "data_task.h"

QueueHandle_t xQueueData1MQTT = NULL;
QueueHandle_t xQueueData2MQTT = NULL;

void data_task(void* param){

  /* Suppress warning for unused parameter */
  (void) param;



  xQueueData1MQTT = xQueueCreate( 4, sizeof(data_packet1_t));
  xQueueData2MQTT = xQueueCreate( 4, sizeof(data_packet2_t));

  printf("\x1b[2J\x1b[;H");

  printf("Bangsaen Design House (BDH)\n");
  printf("Started Data collection.\n");

  /* Repeatedly running part of the task */
  for (;;) {


#if 1
/*******************************************************************************
* 					Begin data-set of CY8CKIT-62S2-40312
*******************************************************************************/
	  static uint32_t counter1 = 0;
	  uint8_t user_bt1 = 0;
	  if (xQueueBT1 != NULL) {
		  if (xQueueReceive(xQueueBT1, &user_bt1, pdMS_TO_TICKS(0)) == pdPASS) {
			//    printf("Received user_bt1: %d\n", user_bt1);
		  }else{
			  // puts("Failed to receive item within 0 ms");
		  }
	  }

	  uint8_t user_bt2 = 0;
	  if (xQueueBT1 != NULL) {
		  if (xQueueReceive(xQueueBT2, &user_bt2, pdMS_TO_TICKS(0)) == pdPASS) {
			  // printf("Received bt2: %d\n", user_bt2);
		  }else{
			  // puts("Failed to receive item within 0 ms");
		  }
	  }

	  float ph_value = 0;
	  if (xQueuePH != NULL) {
		  if (xQueueReceive(xQueuePH, &ph_value, pdMS_TO_TICKS(0)) == pdPASS) {
//			   printf("Received adc_24v: %.2f\n", ph_value);
		  }else{
			  // puts("Failed to receive item within 0 ms");
		  }
	  }

	  uint8_t capsense_bt1 = 0;
	  if (xQueueCapsenseBt1 != NULL) {
		  if (xQueueReceive(xQueueCapsenseBt1, &capsense_bt1, pdMS_TO_TICKS(0)) == pdPASS) {
			  // printf("Received capsense_bt1: %d\n", capsense_bt1);
		  }else{
			  // puts("Failed to receive item within 0 ms");
		  }
	  }

	  uint8_t capsense_bt2 = 0;
	  if (xQueueCapsenseBt2 != NULL) {
		  if (xQueueReceive(xQueueCapsenseBt2, &capsense_bt2, pdMS_TO_TICKS(0)) == pdPASS) {
			  // printf("Received capsense_bt2: %d\n", capsense_bt2);
		  }else{
			  // puts("Failed to receive item within 0 ms");
		  }
	  }

	  uint16_t capsense_slider = 0;
	  if (xQueueCapsenseSlider != NULL) {
		  if (xQueueReceive(xQueueCapsenseSlider, &capsense_slider, pdMS_TO_TICKS(0)) == pdPASS) {
			  //	printf("Received capsense_slider: %d\n", capsense_slider);
		  }else{
			  // puts("Failed to receive item within 0 ms");
		  }
	  }

	  counter1++;
	  /* For Serial Studio */
	  /*couter, bt1, bt2, V, cap_bt1, cap_bt2, cap_slider*/
	  /*43,0,0,10,0,0,0*/
//	  printf("/*%ld,%d,%d,%d,%d,%d,%d*/\r\n",counter1, user_bt1, user_bt2, potentionmeter, capsense_bt1, capsense_bt2, capsense_slider);




#if 1
	  /* For MQTT */
	  data_packet1_t data_packet1 = {
		  .seq = counter1,
		  .user_bt1 = user_bt1,
		  .user_bt2 = user_bt2,
		  .ph_value = ph_value,
		  .capsense_bt1 = capsense_bt1,
		  .capsense_bt2 = capsense_bt2,
		  .capsense_slider = capsense_slider
	  };

	  if (xQueueData1MQTT != NULL) {
		  if (xQueueSend(xQueueData1MQTT, &data_packet1, pdMS_TO_TICKS(100)) == pdPASS) {

		  }else{
			  // puts("Failed to receive item within 0 ms");
		  }
	  }

//	  char data_buf[PAYLOAD_MQTT_SIZE];
//	  print_packet1_json(&data_packet1, data_buf);


#endif

/*******************************************************************************
* 						End data-set of CY8CKIT-62S2-40312
*******************************************************************************/
#endif

#if 1
/*******************************************************************************
* 					Begin data-set of CY8CKIT-028-SENSE
*******************************************************************************/
	  	static uint32_t counter2 = 0;
		data_xensiv_t data_xensiv;
		if (xQueueXensiv != NULL) {
		  if (xQueueReceive(xQueueXensiv, &data_xensiv, pdMS_TO_TICKS(0)) == pdPASS) {
//				printf("Pressure   : %.2f\r\n", round(data_xensiv.pressure*100)/100);
//				printf("Temperature: %.2f Celcius\r\n\r\n", round(data_xensiv.temperature*100)/100);
		  }else{
			  // puts("Failed to receive item within 0 ms");
		  }
		}


		mtb_bmx160_data_t raw_data;
		if (xQueueOrientation9axis != NULL) {
		  if (xQueueReceive(xQueueOrientation9axis, &raw_data, pdMS_TO_TICKS(0)) == pdPASS) {
//				  printf("Accelerometer: X:%6d Y:%6d Z:%6d\r\n", raw_data.accel.x, raw_data.accel.y, raw_data.accel.z);
//				  printf("Gyroscope: X:%6d Y:%6d Z:%6d\r\n\r\n", raw_data.gyro.x, raw_data.gyro.y, raw_data.gyro.z);
//				  printf("Magnetometer: X:%6d Y:%6d Z:%6d\r\n\r\n", raw_data.mag.x, raw_data.mag.y, raw_data.mag.z);

		  }else{
			  // puts("Failed to receive item within 0 ms");
		  }
		}


		uint32_t volume;
		if (xQueueAudio != NULL) {
		  if (xQueueReceive(xQueueAudio, &volume, pdMS_TO_TICKS(0)) == pdPASS) {
//			  printf("valume: %ld\r\n", volume);

		  }else{
			  // puts("Failed to receive item within 0 ms");
		  }
		}

	  counter2++;
	  /* For Serial Studio */
	  /*couter, pressure, temperature, accel_x, accel_y, accel_z, gyro_x, gyro_z, gyro_y, mag_x, mag_y, mag_z, analog_mic, digital_mic*/
//	  printf("/*%ld,%.4f,%.2f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%ld*/\r\n",
//			  counter2, data_xensiv.pressure, data_xensiv.temperature,
//			  raw_data.accel.x, raw_data.accel.y, raw_data.accel.z,
//			  raw_data.gyro.x,raw_data.gyro.y, raw_data.gyro.z,
//			  raw_data.mag.x, raw_data.mag.y, raw_data.mag.z,
//			  0, volume);



			  data_packet2_t data_packet2 = {
					  .seq = counter2,
					  .pressure = round(data_xensiv.pressure*100)/100,
					  .temperature = round(data_xensiv.temperature*100)/100,
					  .bmx160_data.accel.x = raw_data.accel.x,
					  .bmx160_data.accel.y = raw_data.accel.y,
					  .bmx160_data.accel.z = raw_data.accel.z,
					  .bmx160_data.gyro.x = raw_data.gyro.x,
					  .bmx160_data.gyro.y = raw_data.gyro.y,
					  .bmx160_data.gyro.z = raw_data.gyro.z,
					  .bmx160_data.mag.x = raw_data.mag.x,
					  .bmx160_data.mag.y = raw_data.mag.y,
					  .bmx160_data.mag.z = raw_data.mag.z,
					  .analog_mic = 0,
					  .digital_mic = volume
				  };

//			 char data_buf[PAYLOAD_MQTT_SIZE];
//			 print_packet2_json(&data_packet2, data_buf);
//			 printf("%s\r\n", data_buf);

			  if (xQueueData2MQTT != NULL) {
				  if (xQueueSend(xQueueData2MQTT, &data_packet2, pdMS_TO_TICKS(100)) == pdPASS) {

				  }else{
					  // puts("Failed to receive item within 0 ms");
				  }
			  }


/*******************************************************************************
* 						End data-set of CY8CKIT-028-SENSE
*******************************************************************************/
#endif

	  cyhal_gpio_toggle(CYBSP_USER_LED1);
	  vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelete(NULL);

}
