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
#include "st7789_c_bridge.h"
#include "freertos_app.h"

extern st7789_handle_t lcd;

void lcd_fill_demo(void)
{
    st7789_fill_color(lcd, 0xf800);
    vTaskDelay(pdMS_TO_TICKS(1000));
    st7789_fill_color(lcd, 0xFFE0);
    vTaskDelay(pdMS_TO_TICKS(1000));
    st7789_fill_color(lcd, 0XFC07);
    vTaskDelay(pdMS_TO_TICKS(1000));
    st7789_fill_color(lcd, 0XF81F);
    vTaskDelay(pdMS_TO_TICKS(1000));
    st7789_fill_color(lcd, 0XBC40);
    vTaskDelay(pdMS_TO_TICKS(1000));
    st7789_fill_color(lcd, 0X8430);
    vTaskDelay(pdMS_TO_TICKS(1000));
    st7789_fill_color(lcd, 0X07FF);
    vTaskDelay(pdMS_TO_TICKS(1000));
    st7789_fill_color(lcd, 0x07E0);
    vTaskDelay(pdMS_TO_TICKS(1000));
    st7789_fill_color(lcd, 0x001F);
    vTaskDelay(pdMS_TO_TICKS(1000));
    st7789_fill_color(lcd, 0x0000);
    vTaskDelay(pdMS_TO_TICKS(1000));
}