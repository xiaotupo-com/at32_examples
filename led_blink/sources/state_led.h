#ifndef __STATE_LED_H
#define __STATE_LED_H

#include "at32f435_437.h"
#include "at32f435_437_wk_config.h"

#define STATE_LED_PORT LED3_GPIO_PORT
#define STATE_LED_PIN LED3_PIN

// 翻转状态 LED 的亮灭
#define STATE_LED_TOGGLE() STATE_LED_PORT->odt ^= STATE_LED_PIN

struct led_t {
    uint16_t count_value;
    uint32_t count_stop_value;
};

typedef void (*led_handle)();

void led_run(struct led_t *led, led_handle handle);

void state_led_toggle(void);

extern struct led_t state_led;
#endif // __STATE_LED_H
