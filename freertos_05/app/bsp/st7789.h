/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-07-21 01:57:06
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-07-21 22:47:21
 * @FilePath: \freertos_04d:\dev\at32_work\learn-examples\freertos_05\app\bsp\st7789.h
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#pragma once
#include "at32f435_437_wk_config.h"

namespace xtp
{
    class ST7789
    {
    public:
        struct Config
        {
			void (*write_command)(uint8_t cmd);
			void (*write_data)(const uint8_t *data, uint32_t len);
			void (*reset)();
			uint16_t width;
			uint16_t height;
        };

        ST7789(const Config &config);
        void init();
        void fillColor(uint16_t color);
        void drawPixel(uint16_t x, uint16_t y, uint16_t color);
        void displayOff(void);
        void displayOn(void);
        void exitSleep(void);
        void enterSleep(void);

    private:
        Config cfg;
        void setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    };
} // namespace xtp
