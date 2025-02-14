/*
 * audio_task.c
 *
 *  Created on: Feb 20, 2023
 *      Author: nipon
 */


#include "audio_task.h"

/*******************************************************************************
* Macros
********************************************************************************/
/* Define how many samples in a frame */
#define FRAME_SIZE                  (1024)
/* Noise threshold hysteresis */
#define THRESHOLD_HYSTERESIS        3u
/* Volume ratio for noise and print purposes */
#define VOLUME_RATIO                (4*FRAME_SIZE)
/* Desired sample rate. Typical values: 8/16/22.05/32/44.1/48kHz */
#define SAMPLE_RATE_HZ              8000u
/* Decimation Rate of the PDM/PCM block. Typical value is 64 */
#define DECIMATION_RATE             64u
/* Audio Subsystem Clock. Typical values depends on the desire sample rate:
- 8/16/48kHz    : 24.576 MHz
- 22.05/44.1kHz : 22.579 MHz */
#define AUDIO_SYS_CLOCK_HZ          24576000u
/* PDM/PCM Pins */
#define PDM_DATA                    P10_5
#define PDM_CLK                     P10_4

/*******************************************************************************
* Function Prototypes
********************************************************************************/
static void pdm_pcm_isr_handler(void *arg, cyhal_pdm_pcm_event_t event);
static void clock_init(void);

/*******************************************************************************
* Global Variables
********************************************************************************/
/* Interrupt flags */
volatile bool pdm_pcm_flag = true;

/* Volume variables */
uint32_t volume = 0;
uint32_t noise_threshold = THRESHOLD_HYSTERESIS;

/* HAL Object */
cyhal_pdm_pcm_t pdm_pcm;
cyhal_clock_t   audio_clock;
cyhal_clock_t   pll_clock;

QueueHandle_t xQueueAudio = NULL;

/* HAL Config */
const cyhal_pdm_pcm_cfg_t pdm_pcm_cfg =
{
    .sample_rate     = SAMPLE_RATE_HZ,
    .decimation_rate = DECIMATION_RATE,
    .mode            = CYHAL_PDM_PCM_MODE_STEREO,
    .word_length     = 16,  /* bits */
    .left_gain       = 0,   /* dB */
    .right_gain      = 0,   /* dB */
};


/*******************************************************************************
* Function Name: clock_init
********************************************************************************
* Summary:
*  Initialize the clocks in the system.
*
*******************************************************************************/
static void clock_init(void){
    /* Initialize the PLL */
    cyhal_clock_reserve(&pll_clock, &CYHAL_CLOCK_PLL[0]);
    cyhal_clock_set_frequency(&pll_clock, AUDIO_SYS_CLOCK_HZ, NULL);
    cyhal_clock_set_enabled(&pll_clock, true, true);

    /* Initialize the audio subsystem clock (CLK_HF[1])
     * The CLK_HF[1] is the root clock for the I2S and PDM/PCM blocks */
    cyhal_clock_reserve(&audio_clock, &CYHAL_CLOCK_HF[1]);

    /* Source the audio subsystem clock from PLL */
    cyhal_clock_set_source(&audio_clock, &pll_clock);
    cyhal_clock_set_enabled(&audio_clock, true, true);
}

static void audio_init(){
	cy_rslt_t result;

	 xQueueAudio = xQueueCreate( 20, sizeof(uint32_t));

    /* Init the clocks */
    clock_init();

    /* Initialize the PDM/PCM block */
    result = cyhal_pdm_pcm_init(&pdm_pcm, PDM_DATA, PDM_CLK, &audio_clock, &pdm_pcm_cfg);
    CY_ASSERT(CY_RSLT_SUCCESS == result);
    cyhal_pdm_pcm_register_callback(&pdm_pcm, pdm_pcm_isr_handler, NULL);
    cyhal_pdm_pcm_enable_event(&pdm_pcm, CYHAL_PDM_PCM_ASYNC_COMPLETE, CYHAL_ISR_PRIORITY_DEFAULT, true);
    result = cyhal_pdm_pcm_start(&pdm_pcm);
    CY_ASSERT(CY_RSLT_SUCCESS == result);
}

void audio_task(void* param){

	/* Suppress warning for unused parameter */
	(void) param;
	int16_t  audio_frame[FRAME_SIZE] = {0};

	audio_init();

	/* Repeatedly running part of the task */
	for (;;) {
        /* Check if any microphone has data to process */
        if (pdm_pcm_flag)
        {
            /* Clear the PDM/PCM flag */
            pdm_pcm_flag = 0;

            /* Reset the volume */
            volume = 0;

            /* Calculate the volume by summing the absolute value of all the
             * audio data from a frame */
            for (uint32_t index = 0; index < FRAME_SIZE; index++)
            {
                volume += abs(audio_frame[index]);
            }

            /* Prepare line to report the volume */
//            printf("\n\r");

            /* Report the volume */
//            for (uint32_t index = 0; index < (volume/VOLUME_RATIO); index++)
//            {
//                printf("-");
//            }

            /* Turn ON the LED when the volume is higher than the threshold */
            if ((volume/VOLUME_RATIO) > noise_threshold)
            {
//                cyhal_gpio_write((cyhal_gpio_t) CYBSP_USER_LED2, CYBSP_LED_STATE_ON);
            	 cy_rgb_led_on(CY_RGB_LED_COLOR_GREEN, 40);
            }
            else
            {
//                cyhal_gpio_write((cyhal_gpio_t) CYBSP_USER_LED2, CYBSP_LED_STATE_OFF);
                cy_rgb_led_off();
            }

            volume = volume/VOLUME_RATIO;
			if (xQueueAudio != NULL) {
				if (!xQueueSend(xQueueAudio, &volume, pdMS_TO_TICKS(10))) {
					// puts("Failed to send item to queue within 10ms");
				}
			}
			//printf("valume: %ld", volume/VOLUME_RATIO);

            /* Setup to read the next frame */
            cyhal_pdm_pcm_read_async(&pdm_pcm, audio_frame, FRAME_SIZE);
        }

		vTaskDelay(pdMS_TO_TICKS(1));
	}

	vTaskDelete(NULL);
}


/*******************************************************************************
* Function Name: pdm_pcm_isr_handler
********************************************************************************
* Summary:
*  PDM/PCM ISR handler. Set a flag to be processed in the main loop.
*
* Parameters:
*  arg: not used
*  event: event that occurred
*
*******************************************************************************/
void pdm_pcm_isr_handler(void *arg, cyhal_pdm_pcm_event_t event)
{
    (void) arg;
    (void) event;

    pdm_pcm_flag = true;
}
