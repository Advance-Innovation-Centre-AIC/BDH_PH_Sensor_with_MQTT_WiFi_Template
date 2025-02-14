/*
 * orientation9axis_task.h
 *
 *  Created on: Feb 19, 2023
 *      Author: nipon
 */

#ifndef SOURCE_ORIENTATION9AXIS_TASK_H_
#define SOURCE_ORIENTATION9AXIS_TASK_H_

#include "common.h"
#include "mtb_bmx160.h"
#include <math.h>


#define CY_BMX_160_IMU_SPI
//#define CY_BMX_160_IMU_I2C

#ifdef CY_BMX_160_IMU_SPI
	#define CY_IMU_SPI
#endif

/***************************************
*            Constants
****************************************/
/* SPI related */
#define SPI_FREQ_HZ         (8000000UL)
#define mSPI_MOSI           CYBSP_SPI_MOSI
#define mSPI_MISO           CYBSP_SPI_MISO
#define mSPI_SCLK           CYBSP_SPI_CLK
#define mSPI_SS             CYBSP_SPI_CS


void orientation9axis_task(void* param);

#endif /* SOURCE_ORIENTATION9AXIS_TASK_H_ */
