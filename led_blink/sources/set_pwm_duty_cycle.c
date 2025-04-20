/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-13 14:25:52
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-13 19:24:00
 * @FilePath: \MDK_V5d:\projects\at32_examples\led_blink\project\src\set_pwm_duty_cycle.c
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */

#include "set_pwm_duty_cycle.h"

// 设置 PWM 的占空比
void set_pwm_duty_cycle(uint8_t duty_cycle)
{
    if (duty_cycle > 100) {
        duty_cycle = 100;
    }

    // 获取定时器的周期
    uint32_t period = tmr_period_value_get(TMR1);
		
	// 计算比较值，用于设置占空比
    uint32_t compare_value = (period * duty_cycle) / 100;
	
	// 设置 PWM 通道的比较值
    tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_1, compare_value);
}
