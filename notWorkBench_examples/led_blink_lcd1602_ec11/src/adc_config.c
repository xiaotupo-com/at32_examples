#include "adc_config.h"

#include "at32f435_437.h"

void adc3_init(void);

void adc_common_init(void)
{
    /* enable adc3 periph clock */
    crm_periph_clock_enable(CRM_ADC3_PERIPH_CLOCK, TRUE);

    adc_common_config_type adc_common_struct;

    adc_reset();

    /* adc_common_settings------------------------------------------------------------ */
    adc_common_default_para_init(&adc_common_struct);
    adc_common_struct.combine_mode = ADC_INDEPENDENT_MODE;
    adc_common_struct.div = ADC_HCLK_DIV_4;
    adc_common_struct.common_dma_mode = ADC_COMMON_DMAMODE_DISABLE;
    adc_common_struct.common_dma_request_repeat_state = FALSE;
    adc_common_struct.sampling_interval = ADC_SAMPLING_INTERVAL_5CYCLES;
    adc_common_struct.tempervintrv_state = FALSE;
    adc_common_struct.vbat_state = FALSE;
    adc_common_config(&adc_common_struct);

    adc3_init();
}

/**
 * @brief  init adc3 function.
 * @param  none
 * @retval none
 */
void adc3_init(void)
{
    gpio_init_type gpio_init_struct;
    adc_base_config_type adc_base_struct;

    gpio_default_para_init(&gpio_init_struct);

    /*gpio--------------------------------------------------------------------*/
    /* configure the IN14 pin */
    gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
    gpio_init_struct.gpio_pins = GPIO_PINS_4;
    gpio_init(GPIOF, &gpio_init_struct);

    /* adc_settings------------------------------------------------------------------- */
    adc_base_default_para_init(&adc_base_struct);
    adc_base_struct.sequence_mode = FALSE;
    adc_base_struct.repeat_mode = FALSE;
    adc_base_struct.data_align = ADC_RIGHT_ALIGNMENT;
    adc_base_struct.ordinary_channel_length = 1;
    adc_base_config(ADC3, &adc_base_struct);

    adc_resolution_set(ADC3, ADC_RESOLUTION_12B);

    /* adc_ordinary_conversionmode---------------------------------------------------- */
    adc_ordinary_channel_set(ADC3, ADC_CHANNEL_14, 1, ADC_SAMPLETIME_2_5);

    adc_ordinary_conversion_trigger_set(ADC3, ADC_ORDINARY_TRIG_TMR1CH1, ADC_ORDINARY_TRIG_EDGE_NONE);

    adc_enable(ADC3, TRUE);
    while (adc_flag_get(ADC3, ADC_RDY_FLAG) == RESET)
        ;

    /* adc calibration---------------------------------------------------------------- */
    adc_calibration_init(ADC3);
    while (adc_calibration_init_status_get(ADC3))
        ;
    adc_calibration_start(ADC3);
    while (adc_calibration_status_get(ADC3))
        ;
}