/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-13 20:19:26
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-22 19:42:29
 * @FilePath: \MDK_V5d:\projects\at32_examples\ec11_example\sources\led.c
 * @Description:
 *
 * Copyright (c) 2025 by 小土坡, All Rights Reserved.
 */
#include "led.h"

void led3_toggle(void) {
    LED3_GPIO_PORT->odt ^= LED3_PIN;
}

void led2_toggle(void) {
    LED2_GPIO_PORT->odt ^= LED2_PIN;
}

struct led_t led2 = {
    .count_value = 0,
    .step_value = 1,
    .count_stop_value = 500,
    .run_flag = 0x01,
    .id = 0,
};

struct led_t led3 = {
    .count_value = 0,
    .step_value = 1,
    .count_stop_value = 500,
    .run_flag = 0x01,
    .id = 1,
};

// 该函数需要放到滴答定时器的中断函数中，进行 1ms 扫描一次
void led_run(struct led_t *led, led_handle handle) {
    if (led->run_flag) {
        led->count_value++;

        if (led->count_value >= led->count_stop_value) {
            led->count_value = 0; // Clear
            handle();
        }
    }
}

// 调用此函数停止指定 id 的 led 实例停止闪烁，并熄灭 led
// led_id_t: enum led_id_t {
//	LED2_ID,
//	LED3_ID,
//};
void led_stop(enum led_id_t id) {
    switch (id) {
    case LED2_ID: // LED2
        gpio_bits_write(LED2_GPIO_PORT, LED2_PIN, TRUE);
        led2.run_flag = 0x00;
        break;
    case LED3_ID: // LED3
        gpio_bits_write(LED3_GPIO_PORT, LED3_PIN, TRUE);
        led3.run_flag = 0x00;
        break;
    default:
        break;
    }
}