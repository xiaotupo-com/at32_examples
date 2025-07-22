/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-07-21 01:41:41
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-07-22 21:35:04
 * @FilePath: \freertos_04d:\dev\at32_work\learn-examples\freertos_05\app\bsp\st7789_c_bridge.cpp
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#include "st7789.h"
#include "st7789_c_bridge.h"

struct Wrapper {
    xtp::ST7789 *driver;
};

st7789_handle_t st7789_create(const st7789_c_config_t* cfg) {
    auto *w = new Wrapper;
    xtp::ST7789::Config cpp_cfg = {
        cfg->writeCommand,
        cfg->writeData,
        cfg->reset,
        cfg->width,
        cfg->height
    };
    w->driver = new xtp::ST7789(cpp_cfg);
    return (st7789_handle_t)w; /* 将 包含 ST7789 的 Wrapper 强转为 void* */
}

/**
 * @brief 调用 C++ 中的 init 接口 
 * 
 * @param handle 
 */
void st7789_init(st7789_handle_t handle) {
    ((Wrapper*)handle)->driver->init();
}

/**
 * @brief 调用 C++ 中的 fillColor 接口
 * 
 * @param handle 
 * @param color 
 */
void st7789_fill_color(st7789_handle_t handle, uint16_t color) {
    ((Wrapper*)handle)->driver->fillColor(color);
}

/**
 * @brief 调用 C++ 中的 drawPixel 接口
 * 
 * @param handle 
 * @param x 
 * @param y 
 * @param color 
 */
void st7789_draw_pixel(st7789_handle_t handle, uint16_t x, uint16_t y, uint16_t color) {
    ((Wrapper*)handle)->driver->drawPixel(x, y, color);
}
