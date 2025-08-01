/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-15 23:39:20
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-22 19:38:20
 * @FilePath: \MDK_V5d:\projects\at32_examples\ec11_example\sources\key.h
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#ifndef __KEY_H
#define __KEY_H

#include "at32f435_437.h"

#define RELEASED_PROCESS (0)      // 是否启用 key_released_process() 函数 		: 释放处理
#define PRESSED_PROCESS (1)       // 是否启用 key_pressed_process() 函数  		: 按下处理
#define LONG_PRESS_ONCE (1)       // 是否启用 key_long_press_once() 函数  		: 长按单次触发
#define LONG_PRESS_CONTINUOUS (1) // 是否启用 key_long_press_continuous() 函数	: 长按连续触发

// 按键状态机枚举类型定义
enum ButtonState_t {
    STATE_IDLE,                  // 空闲状态
    STATE_PRESS_DEBOUNCE,        // 按下消抖状态
    STATE_PRESSED,               // 成功按下状态
    STATE_LONG_PRESS_ONCE,       // 长按状态，单次触发
    STATE_LONG_PRESS_CONTINUOUS, // 长按状态，连续触发
    STATE_RELEASE_DEBOUNCE,      // 释放消抖状态
    STATE_RELEASED               // 释放成功状态
};

// 长按模式枚举定义
enum LongPressMode_t {
    LONG_PRESS_MODE_ONCE,      // 单次触发模式
    LONG_PRESS_MODE_CONTINUOUS // 连续触发模式
};

// 按键结构体
struct Button_t {
    gpio_type *port;
    uint16_t pin;
    enum ButtonState_t state;             // 状态机枚举
    flag_status pin_state;                // 获取按钮状态，按钮 IO 口的电平高低
    uint8_t debounce_count;               // 消抖次数
    uint32_t press_time;                  // 按下时间(ms)
    enum LongPressMode_t long_press_mode; // 长按模式
    uint8_t id;                           // 按键标识符 id
};

void key_scanf(struct Button_t *buttons);

#if RELEASED_PROCESS
void key_released_process(struct Button_t *button);
#endif

#if PRESSED_PROCESS
void key_pressed_process(struct Button_t *button);
#endif

#if LONG_PRESS_ONCE
void key_long_press_once(struct Button_t *button);
#endif

#if LONG_PRESS_CONTINUOUS
void key_long_press_continuous(struct Button_t *button);
#endif

// 导出声明 buttons 数组
extern struct Button_t buttons[];
#endif // __KEY_H
