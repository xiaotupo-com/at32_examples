/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-07-22 00:11:59
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-07-22 00:16:42
 * @FilePath:
 * \freertos_04d:\dev\at32_work\learn-examples\freertos_05\app\bsp\lcd_demo.c
 * @Description:
 *
 * Copyright (c) 2025 by 小土坡, All Rights Reserved.
 */

#include "lcd_demo.h"
#include "freertos_app.h"
#include "st7789.h"

static uint16_t screen_up_time = 100;

void lcd_fill_demo(void)
{
    st7789.fill_color(0xf800);
    vTaskDelay(pdMS_TO_TICKS(screen_up_time));
    st7789.fill_color(0xFFE0);
    vTaskDelay(pdMS_TO_TICKS(screen_up_time));
    st7789.fill_color(0XFC07);
    vTaskDelay(pdMS_TO_TICKS(screen_up_time));
    st7789.fill_color(0XF81F);
    vTaskDelay(pdMS_TO_TICKS(screen_up_time));
    st7789.fill_color(0XBC40);
    vTaskDelay(pdMS_TO_TICKS(screen_up_time));
    st7789.fill_color(0X8430);
    vTaskDelay(pdMS_TO_TICKS(screen_up_time));
    st7789.fill_color(0X07FF);
    vTaskDelay(pdMS_TO_TICKS(screen_up_time));
    st7789.fill_color(0x07E0);
    vTaskDelay(pdMS_TO_TICKS(screen_up_time));
    st7789.fill_color(0x001F);
    vTaskDelay(pdMS_TO_TICKS(screen_up_time));
    st7789.fill_color(0x0000);
    vTaskDelay(pdMS_TO_TICKS(screen_up_time));
}