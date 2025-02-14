/*
 * orientation9axis_task.c
 *
 *  Created on: Feb 19, 2023
 *      Author: nipon
 */


#include "orientation9axis_task.h"

/** Number of axis used and sample data format */
#define INERTIAL_AXIS_SAMPLED   3

/*******************************************************************************
* Constants
*******************************************************************************/
#ifdef CY_BMX_160_IMU_SPI
    #define IMU_SPI_FREQUENCY 10000000

#endif

QueueHandle_t xQueueOrientation9axis = NULL;


#ifdef CY_BMX_160_IMU_SPI
    /* BMX160 driver structures */
    static mtb_bmx160_t motion_sensor;
    static mtb_bmx160_data_t raw_data;
//    static float imu_data[INERTIAL_AXIS_SAMPLED];

    /* SPI object for data transmission */
    static cyhal_spi_t mSPI;

    bool ret = false;

#endif

static void orientation9axis_init(){

	cy_rslt_t result;
#ifdef CY_IMU_SPI

    /* Make sure BMX160 Accelerometer gets SS pin high early after power-up, so it switches to SPI mode */
        result = cyhal_gpio_init(mSPI_SS, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, 1);
        CY_ASSERT(result == CY_RSLT_SUCCESS);

        /* SPI chip select is controlled by the BMX160 driver, not the SPI controller */
        result = cyhal_spi_init(&mSPI, mSPI_MOSI, mSPI_MISO, mSPI_SCLK, NC, NULL, 8, CYHAL_SPI_MODE_00_MSB, false);
        CY_ASSERT(result == CY_RSLT_SUCCESS);

        result = cyhal_spi_set_frequency(&mSPI, SPI_FREQ_HZ);
        CY_ASSERT(result == CY_RSLT_SUCCESS);

        result = mtb_bmx160_init_spi(&motion_sensor, &mSPI, mSPI_SS);
        if (result != CY_RSLT_SUCCESS)
        {
            printf("ERR: IMU init failed (0x%04x)!\n", ret);
        }
        else {
        	ret = true;
            printf("BMX160 IMU is online\n");
        }

#endif

}


/*******************************************************************************
* Function Name: sensor_get_data
********************************************************************************
* Summary:
*   Return sensor data. This function is blocking. Only returns when data is
*   available.
*
* Parameters:
*     None
*
* Return:
*   Returns success if data returned.
*******************************************************************************/
static cy_rslt_t sensor_get_data(void)
{
    /* Read data from IMU sensor */
    cy_rslt_t result;


    #ifdef CY_BMX_160_IMU_SPI
    	result = mtb_bmx160_read(&motion_sensor, &raw_data);
//        bool ret = false;

        if(result == CY_RSLT_SUCCESS) {


			if (xQueueOrientation9axis != NULL) {
				if (!xQueueSend(xQueueOrientation9axis, &raw_data, pdMS_TO_TICKS(100))) {
					// puts("Failed to send item to queue within 100ms");
				}
			}

        }
#endif
    return CY_RSLT_SUCCESS;
}

void orientation9axis_task(void* param){

	/* Suppress warning for unused parameter */
	(void) param;

	xQueueOrientation9axis = xQueueCreate( 5, sizeof(mtb_bmx160_data_t));

	cy_rslt_t result;

	orientation9axis_init();

	/* Repeatedly running part of the task */
	for (;;) {


#ifdef CY_BMX_160_IMU_SPI
        result = sensor_get_data();
        CY_ASSERT(result == CY_RSLT_SUCCESS);
        vTaskDelay(pdMS_TO_TICKS(1));
#endif


	}
	vTaskDelete(NULL);

}
