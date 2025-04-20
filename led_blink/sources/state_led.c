/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-13 20:19:26
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-13 21:46:29
 * @FilePath: \MDK_V5d:\projects\at32_examples\led_blink\sources\state_led.c
 * @Description:
 *
 * Copyright (c) 2025 by 小土坡, All Rights Reserved.
 */
#include "state_led.h"

struct led_t state_led = {
    .count_value = 0,
    .count_stop_value = 500,
};

// 该函数需要放到滴答定时器的中断函数中，进行 1ms 扫描一次
void led_run(struct led_t *led, led_handle handle) {
	led->count_value++;
	led->count_stop_value = led->count_stop_value;
    if (led->count_value >= led->count_stop_value) {
        led->count_value = 0; // Clear
        handle();
    }
}

void state_led_toggle(void)
{
	STATE_LED_TOGGLE();
}
