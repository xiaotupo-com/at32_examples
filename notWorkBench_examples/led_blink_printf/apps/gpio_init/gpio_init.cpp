#include "gpio_init.h"

void xtp::gpio::init(void)
{
    /* enable gpiog periph clock */
    crm_periph_clock_enable(CRM_GPIOG_PERIPH_CLOCK, TRUE);

    gpio_init_type gpio_init_struct;
    gpio_default_para_init(&gpio_init_struct);

    /* gpio input config */
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pins = LED2_PIN | LED3_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init(GPIOG, &gpio_init_struct);
    gpio_bits_set(GPIOG,
                  LED2_PIN | LED3_PIN);  // Set LED pins to high (off state)
}