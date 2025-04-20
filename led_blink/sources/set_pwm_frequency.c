/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-14 23:28:55
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-15 00:04:43
 * @FilePath: \MDK_V5d:\projects\at32_examples\led_blink\sources\set_pwm_frequency.c
 * @Description:
 *
 * Copyright (c) 2025 by 小土坡, All Rights Reserved.
 */
#include "set_pwm_frequency.h"

// 设置 pwm 的频率
void set_pwm_frequency(uint32_t frequency) {
    uint16_t psc, arr;
    psc = 288 - 1; // 预分频到 1MHz
    arr = (1000000 / frequency) - 1;

    tmr_div_value_set(TMR1, psc);    // 设置预分频值
    tmr_period_value_set(TMR1, arr); // 设置周期计数值
}
