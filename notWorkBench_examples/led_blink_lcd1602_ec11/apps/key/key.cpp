/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-14 20:01:55
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-22 19:49:23
 * @FilePath: \MDK_V5d:\projects\at32_examples\ec11_example\sources\key.c
 * @Description:
 *
 * Copyright (c) 2025 by 小土坡, All Rights Reserved.
 */
#include "key.h"

#include <cstring>

#include "FreeRTOS.h"
#include "buzzer.h"
#include "gpio_init.h"
#include "led.h"
#include "printf_config.h"
#include "task.h"


extern Buzzer buzzer;

#define BUTTON_NUMBER 1  // 指定按键数量

Button buttons[BUTTON_NUMBER]{{EC11_SW_GPIO_PORT, EC11_SW_PIN, Button::LongPressMode::ONCE, Button::Id::EC11_Btn}};

Button::Button(gpio_type *port, uint16_t pin, LongPressMode long_press_mode, Button::Id id) : m_id(id)
{
    m_port = port;
    m_pin = pin;
    m_debounceCount = 0;
    m_pressTime = 0;
    m_pinLevel = RESET;
    m_currentState = State::IDLE;
    m_longPressMode = long_press_mode;
}

/**
 * 按键扫描，需要放到 FreeRTOS 的按键任务中
 */
void key_scanf(Button *buttons)
{
    // 消抖次数
    const uint8_t DEBOUNCE_COUNT = 2;
    // 定义长按时间（单位：ms）
    const uint16_t LONG_PRESS_TIME = 1000;
    // 定义连续触发间隔时间（单位：ms）
    const uint8_t CONTINUOUS_TRIGGER_INTERVAL = 200;

    // For 循环，依次处理所有按键
    for (int i = 0; i < BUTTON_NUMBER; i++)
    {
        Button *button = &buttons[i];
        // 读取按键状态
        button->readPinLevel(); /* 读取按钮电平 */

        // 根据当前状态机的状态执行不同的分支
        switch (button->getCurrentState())
        {
            case Button::State::IDLE:  // 空闲状态
                // if 语句判断按键低电平（被按下）
                if (button->getPinLevel() == RESET)
                {
                    button->setCurrentState(Button::State::PRESS_DEBOUNCE);  // 转换状态机的状态为“按下消抖状态”
                    button->clearDebounceCount();  // 清零消抖计数，以便在其他状态下使用
                }
                break;
            case Button::State::PRESS_DEBOUNCE:  // 按下消抖状态，该状态下会有抖动现象，所以需要一直判断按键的状态
                // 判断按键的状态为按下
                if (button->getPinLevel() == RESET)
                {
                    button->setDebounceCountIncrement();  // 将按键消抖计数变量++

                    // 当debounce_count按键消抖计数变量大于指定的值后
                    // 将按键的状态机状态设置为 STATE_PRESSED，代表成功按下
                    // 我们可以在这里执行成功按下需要处理的程序
                    if (button->getDebounceCount() >= DEBOUNCE_COUNT)
                    {
                        button->setCurrentState(Button::State::PRESSED);
                        button->setPressTime(xTaskGetTickCount()); /* 记录按下时间 */
                    }
                }
                else
                {
                    // 这里代表在STATE_PRESS_DEBOUNCE状态下按键有抖动或松开了按键
                    // 将状态机恢复到空闲状态 STATE_IDLE
                    button->setCurrentState(Button::State::IDLE);
                }
                break;
            case Button::State::PRESSED: /* 状态机的状态为按键成功按下 */
                // if 语句判断按键为高电平（松开），但还没有判断松开抖动
                // 所以下一步需要将状态机切换为松开抖动状态 STATE_RELEASE_DEBOUNCE
                if (button->getPinLevel() == SET)
                {
                    button->setCurrentState(Button::State::RELEASE_DEBOUNCE);
                    button->clearDebounceCount();  // 清零消抖计数，以便在其他状态下使用

#if M_PRESSED_PROCESS  // 1️⃣ 短按处理程序
                    /********************************************************************************/
                    key_pressed_process(button);
                    /********************************************************************************/
#endif
                }
                else
                {
                    if ((xTaskGetTickCount() - (button->getPressTime())) >= pdMS_TO_TICKS(LONG_PRESS_TIME))
                    {
                        if (button->getLongPressMode() == Button::LongPressMode::ONCE)
                        {
                            button->setCurrentState(Button::State::LONG_PRESS_ONCE);

#if M_LONG_PRESS_ONCE  // 2️⃣ 长按单次触发处理
                            /********************************************************************************/
                            key_long_press_once(button);
                            /********************************************************************************/
#endif
                        }
                        else
                        {
                            button->setCurrentState(Button::State::LONG_PRESS_CONTINUOUS);
                            button->setPressTime(xTaskGetTickCount());  // 重置时间用于连续触发计时
                            printf_safe("长按连续触发第一次处理\n");
#if M_LONG_PRESS_CONTINUOUS  // 3️⃣ 长按连续触发第一次处理
                            /********************************************************************************/
                            key_long_press_continuous(button);
                            /********************************************************************************/
#endif
                        }
                    }
                }
                break;
            case Button::State::LONG_PRESS_ONCE:
                // 如果按键松开了，则将状态机转为松开消抖状态
                if (button->getPinLevel() == SET)
                {
                    button->setCurrentState(Button::State::RELEASE_DEBOUNCE);
                    button->clearDebounceCount();
                }
                break;
            case Button::State::LONG_PRESS_CONTINUOUS:
                if (button->getPinLevel() == SET)
                {
                    button->setCurrentState(Button::State::RELEASE_DEBOUNCE);
                    button->clearDebounceCount();
                }
                else
                {
                    if ((xTaskGetTickCount() - (button->getPressTime()) >= pdMS_TO_TICKS(CONTINUOUS_TRIGGER_INTERVAL)))
                    {
                        button->setPressTime(xTaskGetTickCount());  // 重置时间

#if M_LONG_PRESS_CONTINUOUS  // 4️⃣ 长按连续触发
                        /********************************************************************************/
                        key_long_press_continuous(button);
                        /********************************************************************************/
#endif
                    }
                }
                break;
            case Button::State::RELEASE_DEBOUNCE:  // 松开消抖状态
            {
                // if 判断按键为松开（高电平）
                if (button->getPinLevel() == SET)
                {
                    button->setDebounceCountIncrement();  // 将按键消抖计数变量++

                    // 当debounce_count按键消抖计数变量大于指定的值后
                    // 将按键的状态机状态设置为 STATE_RELEASED，代表成功松开
                    if (button->getDebounceCount() >= DEBOUNCE_COUNT)
                    {
                        button->setCurrentState(Button::State::RELEASED);

#if M_RELEASED_PROCESS  // 5️⃣ 按键松开处理程序
                        /********************************************************************************/
                        key_released_process(button);
                        /********************************************************************************/
#endif
                    }
                }
                else
                // 否则代表消抖计数变量没有达到设定的值或按键发生了抖动
                //将状态机的状态重新设定为STATE_PRESSED
                {
                    if (button->getCurrentState() == Button::State::LONG_PRESS_ONCE)
                    {
                        button->setCurrentState(Button::State::LONG_PRESS_ONCE);
                    }
                    else if (button->getCurrentState() == Button::State::LONG_PRESS_CONTINUOUS)
                    {
                        button->setCurrentState(Button::State::LONG_PRESS_CONTINUOUS);
                    }
                    else
                    {
                        button->setCurrentState(Button::State::PRESSED);
                    }
                }
            }
            break;
            case Button::State::RELEASED:  // 状态机为 STATE_RELEASED，代表处于松开状态

                // if 判断按键为按下了
                if (button->getPinLevel() == RESET)
                {
                    // 再次将状态机的状态切换为 STATE_PRESS_DEBOUNCE
                    button->setCurrentState(Button::State::PRESS_DEBOUNCE);
                    button->clearDebounceCount();  // 清零debounce_count，让 STATE_PRESS_DEBOUNCE 使用
                }
                break;
        }
    }
}

#if M_RELEASED_PROCESS
/**
 * 松开处理程序，默认不适用该函数
 * 通过宏定义 RELEASED_PROCESS 为 1 来启用该函数
 */
void key_released_process(Button *button)
{
    buzzer.setIsActive(true);  // 启动蜂鸣器响一下
    switch (button->getId())
    {
        case Button::Id::EC11_Btn:  // 按键 SW1

            printf_safe("released: Ec11\n");
            break;
        default:
            break;
    }
}
#endif

#if M_PRESSED_PROCESS
/**
 * 按键成功按下处理程序（单击处理）
 * 默认启用该函数
 */
void key_pressed_process(Button *button)
{
    buzzer.setIsActive(true);  // 启动蜂鸣器响一下

    switch (button->getId())
    {
        case Button::Id::EC11_Btn:
            printf_safe("pressed: Ec11\n");
            break;
        default:
            break;
    }
}
#endif

#if M_LONG_PRESS_ONCE
/**
 * 按键长按单次触发处理程序，根据按键的长按模式来确定该按键是否为单次触发
 */
void key_long_press_once(Button *button)
{
    buzzer.setIsActive(true);  // 启动蜂鸣器响一下
    switch (button->getId())
    {
        case Button::Id::EC11_Btn:
            printf_safe("long_press: Ec11\n");
            buzzer.toggleDisabled();
            break;
        default:
            break;
    }
}
#endif

#if M_LONG_PRESS_CONTINUOUS
/**
 * 长按连续触发，根据按键的长按模式来处理连续触发
 */
void key_long_press_continuous(Button *button)
{
    buzzer.setIsActive(true);  // 启动蜂鸣器响一下
}
#endif

/**
 * @brief 设置按钮的状态机状态
 *
 * @param state
 */
void Button::setCurrentState(State state) { m_currentState = state; }

/**
 * @brief 获取按钮的状态机状态
 *
 * @return Button::ButtonState
 */
Button::State Button::getCurrentState(void) { return m_currentState; }

/**
 * @brief 从 m_pinLevel 获取当前按钮对象存储的电平状态高低
 *
 * @return flag_status
 */
flag_status Button::getPinLevel(void) { return m_pinLevel; }

/**
 * @brief 从 IO 口读取电平
 *
 */
void Button::readPinLevel(void) { m_pinLevel = gpio_input_data_bit_read(m_port, m_pin); }

/**
 * @brief 获取消抖
 *
 * @return uint8_t
 */
uint8_t Button::getDebounceCount() { return m_debounceCount; }

/**
 * @brief 清零消抖计数器
 *
 */
void Button::clearDebounceCount(void) { m_debounceCount = 0; }

/**
 * @brief 消抖计数自增 m_debounceCount += 1;
 *
 */
void Button::setDebounceCountIncrement(void) { m_debounceCount += 1; }

/**
 * @brief 设置按下时间
 *
 * @param time
 */
void Button::setPressTime(uint32_t time) { m_pressTime = time; }

/**
 * @brief 返回按下时间
 *
 * @return uint32_t
 */
uint32_t Button::getPressTime(void) { return m_pressTime; }

/**
 * @brief 设置长按模式
 *
 * @param mode
 */
void Button::setLongPressMode(LongPressMode mode) { m_longPressMode = mode; }

/**
 * @brief 获取长按模式
 *
 * @return LongPressMode
 */
Button::LongPressMode Button::getLongPressMode(void) { return m_longPressMode; }

/**
 * @brief 获取按键 ID
 *
 * @return uint8_t
 */
Button::Id Button::getId(void) { return m_id; }