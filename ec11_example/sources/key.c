/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-14 20:01:55
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-21 01:48:38
 * @FilePath: \MDK_V5d:\projects\at32_examples\ec11_example\sources\key.c
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#include "key.h"
#include "at32f435_437_wk_config.h"
#include "buzzer.h"
#include "led.h"

#define BUTTON_NUMBER 5 // 指定按键数量

// struct Button_t buttons[BUTTON_NUMBER] = {
//     {SW1_GPIO_PORT, SW1_PIN, STATE_IDLE, RESET, 0, 0},
//     {SW2_GPIO_PORT, SW2_PIN, STATE_IDLE, RESET, 0, 1},
//     {SW3_GPIO_PORT, SW3_PIN, STATE_IDLE, RESET, 0, 2},
//     {SW4_GPIO_PORT, SW4_PIN, STATE_IDLE, RESET, 0, 3},
//     {EC11_SW_GPIO_PORT, EC11_SW_PIN, STATE_IDLE, RESET, 0, 4},
// };
struct Button_t buttons[BUTTON_NUMBER] = {
    {.port = SW1_GPIO_PORT,
     .pin = SW1_PIN,
     .state = STATE_IDLE,
     .pin_state = RESET,
     .debounce_count = 0,
     .press_time = 0,
     .id = 0},
    {.port = SW2_GPIO_PORT,
     .pin = SW2_PIN,
     .state = STATE_IDLE,
     .pin_state = RESET,
     .debounce_count = 0,
     .press_time = 0,
     .id = 1},
    {
        .port = SW3_GPIO_PORT,
        .pin = SW3_PIN,
        .state = STATE_IDLE,
        .pin_state = RESET,
        .debounce_count = 0,
        .press_time = 0,
        .id = 2,
    },
    {
        .port = SW4_GPIO_PORT,
        .pin = SW4_PIN,
        .state = STATE_IDLE,
        .pin_state = RESET,
        .debounce_count = 0,
        .press_time = 0,
        .id = 3,
    },
    {
        .port = EC11_SW_GPIO_PORT,
        .pin = EC11_SW_PIN,
        .state = STATE_IDLE,
        .pin_state = RESET,
        .debounce_count = 0,
        .press_time = 0,
        .id = 4,
    }};

// 按键扫描，需要放到 FreeRTOS 的按键任务中
void key_scanf(struct Button_t *buttons) {
    // 消抖次数
    const uint8_t DEBOUNCE_COUNT = 2;
    // 定义长按时间（单位：ms）
    const uint16_t LONG_PRESS_TIME = 1000;

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
                    // 按键按下处理程序
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
            if (button->pin_state == TRUE) {
                button->state = STATE_RELEASE_DEBOUNCE;
                button->debounce_count = 0; // 清零消抖计数，以便在其他状态下使用
            }
            break;
        case STATE_RELEASE_DEBOUNCE: // 松开消抖状态
        {
            // if 判断按键为松开（高电平）
            if (button->pin_state == TRUE) {
                button->debounce_count++; // 将按键消抖计数变量++

                // 当debounce_count按键消抖计数变量大于指定的值后
                // 将按键的状态机状态设置为 STATE_RELEASED，代表成功松开
                if (button->debounce_count >= DEBOUNCE_COUNT) {
                    button->state = STATE_RELEASED;
                    // 按键松开处理程序
                    {
                        buzzer.run_flag = 0x01;
                        switch (button->id) {
                        case 0: // 按键 SW1
                            led2.run_flag = 0x01;
                            led2.count_stop_value += 10;
                            printf("SW1\n");
                            break;
                        case 1: // 按键 SW2
                            led2.run_flag = 0x01;
                            led2.count_stop_value -= 10;
                            printf("SW2\n");
                            break;
                        case 2: // 按键 SW3
                            led3.run_flag = 0x01;
                            led3.count_stop_value += 10;
                            printf("SW3\n");
                            break;
                        case 3: // 按键 SW4
                            led3.run_flag = 0x01;
                            led3.count_stop_value -= 10;
                            printf("SW4\n");
                            break;
                        case 4: // 按键 EC11_SW
                            led2.step_value++;
                            led_stop(0);
                            led_stop(1);
                            printf("EC11_SW\n");
                            break;
                        default:
                            break;
                        }
                    }
                }
            } else
            // 否则代表消抖计数变量没有达到设定的值或按键发生了抖动
            //将状态机的状态重新设定为STATE_PRESSED
            {
                button->state = STATE_PRESSED;
            }
        } break;
        case STATE_RELEASED: // 状态机为 STATE_RELEASED，代表处于松开状态

            // if 判断按键为按下了
            if (button->pin_state == FALSE) {
                // 再次将状态机的状态切换为 STATE_PRESS_DEBOUNCE
                button->state = STATE_PRESS_DEBOUNCE;
                button->debounce_count = 0; // 清零debounce_count，让 STATE_PRESS_DEBOUNCE 使用
            }
            break;
        }
    }
}
