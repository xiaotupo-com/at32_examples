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
#include "FreeRTOS.h"
#include "at32f435_437_wk_config.h"
#include "buzzer.h"
#include "led.h"
#include "task.h"

#define BUTTON_NUMBER 5 // 指定按键数量

struct Button_t buttons[BUTTON_NUMBER] = {
    {.port = SW1_GPIO_PORT,
     .pin = SW1_PIN,
     .state = STATE_IDLE,
     .pin_state = RESET,
     .debounce_count = 0,
     .press_time = 0,
     .long_press_mode = LONG_PRESS_MODE_ONCE,
     .id = 0},
    {.port = SW2_GPIO_PORT,
     .pin = SW2_PIN,
     .state = STATE_IDLE,
     .pin_state = RESET,
     .debounce_count = 0,
     .press_time = 0,
     .long_press_mode = LONG_PRESS_MODE_ONCE,
     .id = 1},
    {
        .port = SW3_GPIO_PORT,
        .pin = SW3_PIN,
        .state = STATE_IDLE,
        .pin_state = RESET,
        .debounce_count = 0,
        .press_time = 0,
        .long_press_mode = LONG_PRESS_MODE_ONCE,
        .id = 2,
    },
    {
        .port = SW4_GPIO_PORT,
        .pin = SW4_PIN,
        .state = STATE_IDLE,
        .pin_state = RESET,
        .debounce_count = 0,
        .press_time = 0,
        .long_press_mode = LONG_PRESS_MODE_ONCE,
        .id = 3,
    },
    {
        .port = EC11_SW_GPIO_PORT,
        .pin = EC11_SW_PIN,
        .state = STATE_IDLE,
        .pin_state = RESET,
        .debounce_count = 0,
        .press_time = 0,
        .long_press_mode = LONG_PRESS_MODE_CONTINUOUS,
        .id = 4,
    }};

/**
 * 按键扫描，需要放到 FreeRTOS 的按键任务中
 */
void key_scanf(struct Button_t *buttons) {
    // 消抖次数
    const uint8_t DEBOUNCE_COUNT = 2;
    // 定义长按时间（单位：ms）
    const uint16_t LONG_PRESS_TIME = 1000;
    // 定义连续触发间隔时间（单位：ms）
    const uint8_t CONTINUOUS_TRIGGER_INTERVAL = 200;

    // For 循环，依次处理所有按键
    for (int i = 0; i < BUTTON_NUMBER; i++) {
        struct Button_t *button = &buttons[i];
        // 读取按键状态
        button->pin_state = gpio_input_data_bit_read(button->port, button->pin);

        // 根据当前状态机的状态执行不同的分支
        switch (button->state) {
        case STATE_IDLE: // 空闲状态
            // if 语句判断按键低电平（被按下）
            if (button->pin_state == RESET) {
                button->state = STATE_PRESS_DEBOUNCE; // 转换状态机的状态为“按下消抖状态”
                button->debounce_count = 0;           // 清零消抖计数，以便在其他状态下使用
            }
            break;
        case STATE_PRESS_DEBOUNCE: // 按下消抖状态，该状态下会有抖动现象，所以需要一直判断按键的状态
            // 判断按键的状态为按下
            if (button->pin_state == RESET) {
                button->debounce_count++; // 将按键消抖计数变量++

                // 当debounce_count按键消抖计数变量大于指定的值后
                // 将按键的状态机状态设置为 STATE_PRESSED，代表成功按下
                // 我们可以在这里执行成功按下需要处理的程序
                if (button->debounce_count >= DEBOUNCE_COUNT) {
                    button->state = STATE_PRESSED;
                    button->press_time = xTaskGetTickCount(); // 记录按下时间
                }
            } else {
                // 这里代表在STATE_PRESS_DEBOUNCE状态下按键有抖动或松开了按键
                // 将状态机恢复到空闲状态 STATE_IDLE
                button->state = STATE_IDLE;
            }
            break;
        case STATE_PRESSED: // 状态机的状态为按键成功按下
            // if 语句判断按键为高电平（松开），但还没有判断松开抖动
            // 所以下一步需要将状态机切换为松开抖动状态 STATE_RELEASE_DEBOUNCE
            if (button->pin_state == SET) {
                button->state = STATE_RELEASE_DEBOUNCE;
                button->debounce_count = 0; // 清零消抖计数，以便在其他状态下使用

#if PRESSED_PROCESS // 1️⃣ 短按处理程序
                /********************************************************************************/
                key_pressed_process(button);
                /********************************************************************************/
#endif
            } else {
                if ((xTaskGetTickCount() - (button->press_time)) >= pdMS_TO_TICKS(LONG_PRESS_TIME)) {
                    if (button->long_press_mode == LONG_PRESS_MODE_ONCE) {
                        button->state = STATE_LONG_PRESS_ONCE;

#if LONG_PRESS_ONCE // 2️⃣ 长按单次触发处理
                        /********************************************************************************/
                        key_long_press_once(button);
                        /********************************************************************************/
#endif
                    } else {
                        button->state = STATE_LONG_PRESS_CONTINUOUS;
                        button->press_time = xTaskGetTickCount(); // 重置时间用于连续触发计时
                        printf("长按连续触发第一次处理\n");
#if LONG_PRESS_CONTINUOUS // 3️⃣ 长按连续触发第一次处理
                        /********************************************************************************/
                        key_long_press_continuous(button);
                        /********************************************************************************/
#endif
                    }
                }
            }
            break;
        case STATE_LONG_PRESS_ONCE:
            // 如果按键松开了，则将状态机转为松开消抖状态
            if (button->pin_state == SET) {
                button->state = STATE_RELEASE_DEBOUNCE;
                button->debounce_count = 0;
            }
            break;
        case STATE_LONG_PRESS_CONTINUOUS:
            if (button->pin_state == SET) {
                button->state = STATE_RELEASE_DEBOUNCE;
                button->debounce_count = 0;
            } else {
                if ((xTaskGetTickCount() - (button->press_time) >= pdMS_TO_TICKS(CONTINUOUS_TRIGGER_INTERVAL))) {
                    button->press_time = xTaskGetTickCount(); // 重置时间

#if LONG_PRESS_CONTINUOUS // 4️⃣ 长按连续触发
                    /********************************************************************************/
                    key_long_press_continuous(button);
                    /********************************************************************************/
#endif
                }
            }
            break;
        case STATE_RELEASE_DEBOUNCE: // 松开消抖状态
        {
            // if 判断按键为松开（高电平）
            if (button->pin_state == SET) {
                button->debounce_count++; // 将按键消抖计数变量++

                // 当debounce_count按键消抖计数变量大于指定的值后
                // 将按键的状态机状态设置为 STATE_RELEASED，代表成功松开
                if (button->debounce_count >= DEBOUNCE_COUNT) {
                    button->state = STATE_RELEASED;

#if RELEASED_PROCESS // 5️⃣ 按键松开处理程序
                    /********************************************************************************/
                    key_released_process(button);
                    /********************************************************************************/
#endif
                }
            } else
            // 否则代表消抖计数变量没有达到设定的值或按键发生了抖动
            //将状态机的状态重新设定为STATE_PRESSED
            {
                if (button->state == STATE_LONG_PRESS_ONCE) {
                    button->state = STATE_LONG_PRESS_ONCE;
                } else if (button->state == STATE_LONG_PRESS_CONTINUOUS) {
                    button->state = STATE_LONG_PRESS_CONTINUOUS;
                } else {
                    button->state = STATE_PRESSED;
                }
            }
        } break;
        case STATE_RELEASED: // 状态机为 STATE_RELEASED，代表处于松开状态

            // if 判断按键为按下了
            if (button->pin_state == RESET) {
                // 再次将状态机的状态切换为 STATE_PRESS_DEBOUNCE
                button->state = STATE_PRESS_DEBOUNCE;
                button->debounce_count = 0; // 清零debounce_count，让 STATE_PRESS_DEBOUNCE 使用
            }
            break;
        }
    }
}

#if RELEASED_PROCESS
/**
 * 松开处理程序，默认不适用该函数
 * 通过宏定义 RELEASED_PROCESS 为 1 来启用该函数
 */
void key_released_process(struct Button_t *button) {

    buzzer.run_flag = 0x01;
    switch (button->id) {
    case 0: // 按键 SW1

        printf("released: SW1\n");
        break;
    case 1: // 按键 SW2

        printf("released: SW2\n");
        break;
    case 2: // 按键 SW3

        printf("released: SW3\n");
        break;
    case 3: // 按键 SW4

        printf("released: SW4\n");
        break;
    case 4: // 按键 EC11_SW

        printf("released: EC11_SW\n");
        break;
    default:
        break;
    }
}
#endif

#if PRESSED_PROCESS
/**
 * 按键成功按下处理程序（单击处理）
 * 默认启用该函数
 */
void key_pressed_process(struct Button_t *button) {
    buzzer.run_flag = 0x01; // 启动蜂鸣器响一下
    switch (button->id) {
    case 0: // 按键 SW1
        
        printf("pressed: SW1\n");
        break;
    case 1: // 按键 SW2
        
        printf("pressed: SW2\n");
        break;
    case 2: // 按键 SW3
        
        printf("pressed: SW3\n");
        break;
    case 3: // 按键 SW4
        
        printf("pressed: SW4\n");
        break;
    case 4: // 按键 EC11_SW
        
        printf("pressed: EC11_SW\n");
        break;
    default:
        break;
    }
}
#endif

#if LONG_PRESS_ONCE
/**
 * 按键长按单次触发处理程序，根据按键的长按模式来确定该按键是否为单次触发
 */
void key_long_press_once(struct Button_t *button) {
    buzzer.run_flag = 0x01;
    switch (button->id) {
    case 0: // 按键 SW1
        led2.run_flag = !led2.run_flag;
        printf("long_press_once: SW1\n");
        break;
    case 1: // 按键 SW2

        printf("long_press_once: SW2\n");
        break;
    case 2: // 按键 SW3
        led3.run_flag = !led3.run_flag;
        printf("long_press_once: SW3\n");
        break;
    case 3: // 按键 SW4

        printf("long_press_once: SW4\n");
        break;
    case 4: // 按键 EC11_SW
        printf("long_press_once: EC11_SW\n");
        break;
    default:
        break;
    }
}
#endif

#if LONG_PRESS_CONTINUOUS
/**
 * 长按连续触发，根据按键的长按模式来处理连续触发
 */
void key_long_press_continuous(struct Button_t *button) {
    buzzer.run_flag = 0x01;
    switch (button->id) {
    case 0: // 按键 SW1

        printf("long_press_continuous: SW1\n");
        break;
    case 1: // 按键 SW2

        printf("long_press_continuous: SW2\n");
        break;
    case 2: // 按键 SW3
        printf("long_press_continuous: SW3\n");
        break;
    case 3: // 按键 SW4

        printf("long_press_continuous: SW4\n");
        break;
    case 4: // 按键 EC11_SW
        printf("long_press_continuous: EC11_SW\n");
        break;
    default:
        break;
    }
}
#endif
