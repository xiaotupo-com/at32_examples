/**
 * @file led.cpp
 * @author xtp (xiaotupo@163.com)
 * @brief 
 * @version V0.1
 * @date 2025-07-27
 * 
 * @copyright Copyright (c) 2025
 * 
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