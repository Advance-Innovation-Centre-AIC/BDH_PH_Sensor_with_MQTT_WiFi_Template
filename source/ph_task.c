

#include "ph_task.h"

#define PH4_ADC 1638252
#define PH7_ADC 2054624
#define PH10_ADC 2439090

float calculate_ph(int adc_value);
int smooth_adc_read(cyhal_adc_channel_t *channel, int samples);
void ph_receiver_task(void* param);


QueueHandle_t xQueuePH = NULL;


static cyhal_adc_t adc_obj;
static cyhal_adc_channel_t adc_chan_0_obj;
static int adc_out;
static float ph_value;

static void ph_init(){
	cy_rslt_t result;


	/* Initialize ADC. The ADC block which can connect to pin 10[6] is selected */
	result = cyhal_adc_init(&adc_obj, P10_0, NULL);
	CY_ASSERT(CY_RSLT_SUCCESS == result);

	// ADC configuration structure
	const cyhal_adc_config_t ADCconfig ={
		.continuous_scanning = false,
		.resolution = 12,
		.average_count = 1,
		.average_mode_flags = 0,
		.ext_vref_mv = 0,
		.vneg = CYHAL_ADC_VNEG_VREF,
		.vref = CYHAL_ADC_REF_VDDA,
		.ext_vref = NC,
		.is_bypassed = false,
		.bypass_pin = NC
	};

	// Configure to use VDD as Vref
	result = cyhal_adc_configure(&adc_obj, &ADCconfig);
	CY_ASSERT(CY_RSLT_SUCCESS == result);

	/* Initialize ADC channel, allocate channel number 0 to pin 10[6] as this is the first channel initialized */
	const cyhal_adc_channel_config_t channel_config = { .enable_averaging = false, .min_acquisition_ns = 220, .enabled = true };
	result = cyhal_adc_channel_init_diff(&adc_chan_0_obj, &adc_obj, P10_0, CYHAL_ADC_VNEG, &channel_config);

}


void ph_task(void* param){

	  (void) param;

	  xQueuePH = xQueueCreate(2, sizeof(float));

	  float received_ph;

	  ph_init();

	  /* Repeatedly running part of the task */
	  for (;;) {

		        /* Read smoothed ADC conversion result */
        adc_out = smooth_adc_read(&adc_chan_0_obj, 10); // Average over 10 readings

        // Calculate the pH value
        ph_value = calculate_ph(adc_out);
		if (xQueuePH != NULL) {
		    if (!xQueueSend(xQueuePH, &ph_value, pdMS_TO_TICKS(100))) {
//		        printf("Failed to send item to queue within 100ms.\n");
		    } else {
//		        printf("Successfully sent pH value: %.2f to the queue.\n", test_ph);
		    }
		}
//		printf("Sending pH value: %.2f\n", test_ph);
		vTaskDelay(pdMS_TO_TICKS(1));
	  }


	  vTaskDelete(NULL);
}


void ph_receiver_task(void* param) {
    (void)param;
    float received_ph;

    for (;;) {
        if (xQueuePH != NULL) {
            if (xQueueReceive(xQueuePH, &received_ph, pdMS_TO_TICKS(1000))) {
                printf("Received pH value: %.2f\n", received_ph);
            } else {
                printf("Failed to receive pH value from queue.\n");
            }
        }

        vTaskDelay(pdMS_TO_TICKS(500)); // Delay 500ms before checking again
    }

    vTaskDelete(NULL);
}

float calculate_ph(int adc_value)
{
    float ph_value;

    if (adc_value <= PH4_ADC)
    {
        // Extrapolate below pH 4
        ph_value = 4.0 - ((PH4_ADC - adc_value) * 3.0) / (PH7_ADC - PH4_ADC);
    }
    else if (adc_value <= PH7_ADC)
    {
        // Interpolate between pH 4 and pH 7
        ph_value = 4.0 + ((adc_value - PH4_ADC) * 3.0) / (PH7_ADC - PH4_ADC);
    }
    else if (adc_value <= PH10_ADC)
    {
        // Interpolate between pH 7 and pH 10
        ph_value = 7.0 + ((adc_value - PH7_ADC) * 3.0) / (PH10_ADC - PH7_ADC);
    }
    else
    {
        // Extrapolate above pH 10
        ph_value = 10.0 + ((adc_value - PH10_ADC) * 3.0) / (PH10_ADC - PH7_ADC);
    }

    return ph_value;
}

int smooth_adc_read(cyhal_adc_channel_t *channel, int samples)
{
    int sum = 0;

    for (int i = 0; i < samples; i++)
    {
        sum += cyhal_adc_read_uv(channel); // Read ADC in microvolts
        cyhal_system_delay_ms(10);        // Small delay between readings
    }

    return sum / samples;
}

// Receiver task to get the pH value from the queue
void receiver_task(void* param) {
    float received_ph;

    for (;;) {
        if (xQueueReceive(xQueuePH, &received_ph, portMAX_DELAY) == pdPASS) {
            // Print the received pH value
            printf("Received pH value: %.2f\n", received_ph);
        }
    }

    vTaskDelete(NULL);
}






