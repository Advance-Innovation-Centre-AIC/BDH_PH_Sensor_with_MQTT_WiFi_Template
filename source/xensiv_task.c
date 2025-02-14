/*
 * xensiv_task.c
 *
 *  Created on: Feb 19, 2023
 *      Author: nipon
 */

#include "xensiv_task.h"


#define ADC_MAX_VALUE 4095
#define PRESSURE_SENSOR_VOLTAGE 3.3
#define PRESSURE_SENSOR_SLOPE 0.04
#define PRESSURE_SENSOR_OFFSET 0.1

xensiv_dps3xx_t pressure_sensor;
cyhal_i2c_t i2c;
cyhal_i2c_cfg_t i2c_cfg = {
    .is_slave = false,
    .address = 0,
    .frequencyhal_hz = 400000
};

#define DPS_I2C_SDA (P6_1)
#define DPS_I2C_SCL (P6_0)

QueueHandle_t xQueueXensiv = NULL;

static void xensiv_init(){

	cy_rslt_t result;

	/* Initialize i2c for pressure sensor */
	result = cyhal_i2c_init(&i2c, DPS_I2C_SDA, DPS_I2C_SCL, NULL);
	CY_ASSERT(result == CY_RSLT_SUCCESS);
	result = cyhal_i2c_configure(&i2c, &i2c_cfg);
	CY_ASSERT(result == CY_RSLT_SUCCESS);

	/* Initialize pressure sensor */
	result = xensiv_dps3xx_mtb_init_i2c(&pressure_sensor, &i2c, XENSIV_DPS3XX_I2C_ADDR_DEFAULT);
	CY_ASSERT(result == CY_RSLT_SUCCESS);

}

void xensiv_task(void* param){

	  /* Suppress warning for unused parameter */
	  (void) param;

	  float voltage, pressure_hPa;
//	  float voltage, pressure_hPa, pressure_mbar;
	  xQueueXensiv = xQueueCreate( 5, sizeof(data_xensiv_t));


	  xensiv_init();

	  /* Repeatedly running part of the task */
	  for (;;) {

			/* Get the pressure and temperature data and print the results to the UART */
			float pressure, temperature;
			xensiv_dps3xx_read(&pressure_sensor, &pressure, &temperature);

//			// Convert the ADC reading to voltage
//			voltage = (float) pressure * PRESSURE_SENSOR_VOLTAGE / ADC_MAX_VALUE;
//
//			// Convert the voltage to pressure in hPa
//			pressure_hPa = (voltage - PRESSURE_SENSOR_OFFSET) / PRESSURE_SENSOR_SLOPE;

	        // Convert the pressure to mbar
			// pressure_mbar = pressure_hPa * 10;

			data_xensiv_t data_xensiv = {
					.pressure = pressure,
					.temperature = temperature
			};
			if (xQueueXensiv != NULL) {
				if (!xQueueSend(xQueueXensiv, &data_xensiv, pdMS_TO_TICKS(200))) {
					// puts("Failed to send item to queue within 100ms");
				}
			}

			vTaskDelay(pdMS_TO_TICKS(1));
	  }


	  vTaskDelete(NULL);
}
