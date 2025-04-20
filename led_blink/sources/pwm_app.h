/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-13 21:03:11
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-14 19:44:48
 * @FilePath: \MDK_V5d:\projects\at32_examples\led_blink\sources\pwm_app.h
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#ifndef __PWM_APP_H
#define __PWM_APP_H

#include "at32f435_437.h"

struct pwm_t {
	uint8_t count;
	uint8_t dir_flag;
	uint8_t run_interval_count_value;
	uint8_t run_interval_count_stop_value;
	uint8_t run_flag;
};

void pwm_init(void);
void pwm_app_run(void);
void set_pwm_run(uint8_t value);
#endif // __PWM_APP_H
