/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-15 23:39:20
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-22 19:38:20
 * @FilePath: key.h
 * @Description:
 *
 * Copyright (c) 2025 by 小土坡, All Rights Reserved.
 */
#ifndef __KEY_H
#define __KEY_H

#include "at32f435_437.h"

#define M_RELEASED_PROCESS (0)       		// 是否启用 key_released_process() 函数 		: 释放处理
#define M_PRESSED_PROCESS (1)        		// 是否启用 key_pressed_process() 函数  		: 按下处理
#define M_LONG_PRESS_ONCE (1)        	// 是否启用 key_long_press_once() 函数  		: 长按单次触发
#define M_LONG_PRESS_CONTINUOUS (1)  	// 是否启用 key_long_press_continuous() 函数	: 长按连续触发

class Button
{
public:
    enum class State : uint8_t
    {
        IDLE,                   // 空闲状态
        PRESS_DEBOUNCE,         // 按下消抖状态
        PRESSED,                // 成功按下状态
        LONG_PRESS_ONCE,        // 长按状态，单次触发
        LONG_PRESS_CONTINUOUS,  // 长按状态，连续触发
        RELEASE_DEBOUNCE,       // 释放消抖状态
        RELEASED                // 释放成功状态
    };

    /* 长按模式枚举定义 */
    enum class LongPressMode : uint8_t
    {
        ONCE,       // 单次触发模式
        CONTINUOUS  // 连续触发模式
    };

    enum class Id : uint8_t
    {
        EC11_Btn
    };

public:
    Button(gpio_type *port, uint16_t pin, LongPressMode long_press_mode, Id id);
    void readPinLevel(void);
	flag_status getPinLevel(void);
    void setCurrentState(State state);
    State getCurrentState(void);
    uint8_t getDebounceCount();
    void clearDebounceCount(void);
    void setDebounceCountIncrement(void);
    void setPressTime(uint32_t time);
    uint32_t getPressTime(void);
    void setLongPressMode(LongPressMode mode);
    LongPressMode getLongPressMode(void);
    Id getId(void);


private:
    gpio_type *m_port;  // 按键所在 GPIO 端口
    uint16_t m_pin;
    uint8_t m_debounceCount;        // 消抖次数
    uint32_t m_pressTime;           // 按下时间(ms)
    flag_status m_pinLevel;         // 获取按钮状态，按钮 IO 口的电平高低
    const Id m_id;          // 按键标识符 id
    State m_currentState;           // 按键状态机状态
    LongPressMode m_longPressMode;  // 长按模式
};

void key_scanf(Button *buttons);

#if M_RELEASED_PROCESS
void key_released_process(Button *button);
#endif

#if M_PRESSED_PROCESS
void key_pressed_process(Button *button);
#endif

#if M_LONG_PRESS_ONCE
void key_long_press_once(Button *button);
#endif

#if M_LONG_PRESS_CONTINUOUS
void key_long_press_continuous(Button *button);
#endif

extern Button buttons[];

#endif  // __KEY_H
