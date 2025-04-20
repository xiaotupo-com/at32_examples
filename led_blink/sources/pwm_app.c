/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-13 21:02:57
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-14 22:31:59
 * @FilePath: \MDK_V5d:\projects\at32_examples\led_blink\sources\pwm_app.c
 * @Description:
 *
 * Copyright (c) 2025 by 小土坡, All Rights Reserved.
 */
#include "pwm_app.h"
#include "set_pwm_duty_cycle.h"
#include "set_pwm_frequency.h"
#include "state_led.h"

// 创建一个 pwm 对象
struct pwm_t pwm = {
    .count = 0,
    .dir_flag = 0x00,
    .run_interval_count_value = 0,
    .run_interval_count_stop_value = 20, // 20ms 执行一次 set_pwm_duty_cycle() 函数
    .run_flag = 0x00,                    // 默认为停止模式
};

// 一些 pwm 初始化工作
void pwm_init(void) {
    // 默认停止输出 PWM
    set_pwm_run(pwm.run_flag);
	set_pwm_frequency(200000);
	set_pwm_duty_cycle(50);
}

// 该函数需要放到滴答定时器中断函数中，进行 1ms 扫描一次
void pwm_app_run(void) {
    pwm.run_interval_count_value++;

    // 用于判断 20ms 是否到，每隔 20ms 执行一次
    if (pwm.run_interval_count_value >= pwm.run_interval_count_stop_value) {
        pwm.run_interval_count_value = 0; // Clear

        if (pwm.dir_flag == 0x00) {
            pwm.count++;
        } else {
            pwm.count--;
        }

        if (pwm.count >= 100 | pwm.count <= 0) {
            pwm.dir_flag = !pwm.dir_flag;
        };
        set_pwm_duty_cycle(pwm.count);
    }
}


// 通过参数指定 PWM 运行/停止
// @value 当 value 为 0 时停止，非零时运行
void set_pwm_run(uint8_t value) {
    tmr_output_enable(TMR1, (confirm_state)value);
    tmr_channel_enable(TMR1, TMR_SELECT_CHANNEL_1, (confirm_state)value);
}
