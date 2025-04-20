#ifndef __LED_H
#define __LED_H

#include "at32f435_437.h"
#include "at32f435_437_wk_config.h"

#define STATE_LED_PORT LED3_GPIO_PORT
#define STATE_LED_PIN LED3_PIN

enum led_id_t {
	LED2_ID,
	LED3_ID,
};

struct led_t {
    uint16_t count_value;
	uint8_t step_value;
    uint32_t count_stop_value;
	uint8_t run_flag;
	enum led_id_t id;
};

typedef void (*led_handle)(); // 声明一个函数指针类型

void led_run(struct led_t *led, led_handle handle);
void led_stop(enum led_id_t id);
void led2_toggle(void);
void led3_toggle(void);

extern struct led_t led2;
extern struct led_t led3;
#endif // __LED_H
