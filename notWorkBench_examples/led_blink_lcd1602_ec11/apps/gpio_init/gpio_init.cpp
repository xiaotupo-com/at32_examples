#include "gpio_init.h"

void xtp::gpio::init(void)
{
    /* enable gpiog periph clock */
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOF_PERIPH_CLOCK, TRUE);
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
	
	/* lcd1602 config */
	gpio_bits_reset(LCD1602_RS_PORT, LCD1602_RS_PIN);
    gpio_bits_reset(LCD1602_RW_PORT, LCD1602_RW_PIN);
    gpio_bits_reset(LCD1602_EN_PORT, LCD1602_EN_PIN);
    gpio_bits_reset(LCD1602_D4_PORT, LCD1602_D4_PIN);
    gpio_bits_reset(LCD1602_D5_PORT, LCD1602_D5_PIN);
    gpio_bits_reset(LCD1602_D6_PORT, LCD1602_D6_PIN);
    gpio_bits_reset(LCD1602_D7_PORT, LCD1602_D7_PIN);

    gpio_init_struct.gpio_pins = LCD1602_RS_PIN;
    gpio_init(LCD1602_RS_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD1602_RW_PIN;
    gpio_init(LCD1602_RW_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD1602_EN_PIN;
    gpio_init(LCD1602_EN_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD1602_D4_PIN;
    gpio_init(LCD1602_D4_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD1602_D5_PIN;
    gpio_init(LCD1602_D5_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD1602_D6_PIN;
    gpio_init(LCD1602_D6_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = LCD1602_D7_PIN;
    gpio_init(LCD1602_D7_PORT, &gpio_init_struct);

    /* Buzzer GPIO */
    gpio_bits_reset(BUZZER_PORT, BUZZER_PIN);
    gpio_init_struct.gpio_pins = BUZZER_PIN;
    gpio_init(BUZZER_PORT, &gpio_init_struct);

}