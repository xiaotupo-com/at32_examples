#include "uart_config.h"

#include "at32f435_437.h"


void usart1_init(void)
{
	/* 外设时钟使能 */
    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
	
    gpio_init_type gpio_init_struct;
    gpio_default_para_init(&gpio_init_struct);

    /* configure the TX pin */
    gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE9, GPIO_MUX_7);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = GPIO_PINS_9;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOA, &gpio_init_struct);

    /* configure the RX pin */
    gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE10, GPIO_MUX_7);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = GPIO_PINS_10;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOA, &gpio_init_struct);

    /* configure param */
    usart_init(USART1, 115200, USART_DATA_8BITS, USART_STOP_1_BIT);
    usart_transmitter_enable(USART1, TRUE);
    usart_receiver_enable(USART1, TRUE);
    usart_parity_selection_config(USART1, USART_PARITY_NONE);

    usart_hardware_flow_control_set(USART1, USART_HARDWARE_FLOW_NONE);

    usart_enable(USART1, TRUE);
}