/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-07-20 23:07:56
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-07-21 21:46:06
 * @FilePath: \freertos_04d:\dev\at32_work\learn-examples\freertos_05\app\bsp\led.cpp
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#include "led.h"
#include "freertos_app.h"
#include "at32f435_437_wk_config.h"

void xtp::led_run(void) {
	static uint8_t led_state = 0;
	led_state = !led_state;
	gpio_bits_write(LED2_GPIO_PORT, LED2_PIN, static_cast<confirm_state>( led_state));
	vTaskDelay(pdMS_TO_TICKS(200));
}