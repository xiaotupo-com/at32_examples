/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-17 22:15:51
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-18 01:15:41
 * @FilePath: \MDK_V5d:\projects\at32_examples\ec11_example\sources\buzzer.c
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#include "buzzer.h"

#include "at32f435_437_wk_config.h"

struct buzzer_t buzzer = {
	.on_count = 0,
	.stop_value = 10,
	.run_flag = 0x00, // 0x00 不执行 buzzer_run, 非零 执行 buzzer_run
};

/**
 * 调用位置: vApplicationTickHook(void)
 * 使用: 当我们把 buzzer.run_flag 赋值为非零时，就会执行 buzzer_run
 * 蜂鸣器会发出响声，当声音长度达到 stop_value时会自动关闭蜂鸣器，并且清除 on_count 和 run_flag
 */
void buzzer_run(void)
{
	gpio_bits_write(BUZZER_GPIO_PORT, BUZZER_PIN, TRUE);
	buzzer.on_count++;
	if (buzzer.on_count >= buzzer.stop_value) {
		gpio_bits_write(BUZZER_GPIO_PORT, BUZZER_PIN, FALSE);
		buzzer.on_count = 0;
		buzzer.run_flag = 0x00;
	}
}