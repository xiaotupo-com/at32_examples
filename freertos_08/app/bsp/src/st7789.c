/**
 * @file st7789.cpp
 * @author xtp (xiaotupo@163.com)
 * @brief st7789 驱动
 * @version V0.1
 * @date 2025-07-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "st7789.h"
#include "freertos_app.h"
#include "lcd_blk.h"
#include "lcd_write_pixel_data.h"
#include "spi_api.h"

/* 全局变量 */
uint16_t color_buf[LCD_WIDTH * LCD_HEIGHT];

/**
 * @brief static 函数声明
 *
 */
static void init();
static void enter_sleep(void);
static void exit_sleep(void);
static void set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
static void draw_pixel(uint16_t x, uint16_t y, uint16_t color);
static void fill_color(uint16_t color);
static void display_off(void);
static void display_on(void);
static void fill_demo(uint16_t color);

/* 创建 ST7789Config 对象 */

struct ST7789 st7789 = {
    .init = init,
    .fill_color = fill_color,
    .enter_sleep = enter_sleep,
    .exit_sleep = exit_sleep,
    .set_window = set_window,
    .draw_pixel = draw_pixel,
    .display_off = display_off,
    .display_on = display_on,
    .fill_demo = fill_demo,
    .cfg = {.write_command = spi_write_cmd,
            .write_data = spi_write_data,
            .reset = lcd_reset,
            .lcd_set_to_non_dma_mode = lcd_set_to_non_dma_mode,
            .lcd_set_to_dma_mode = lcd_set_to_dma_mode,
            .width = 320,
            .height = 240}};

/**
 * @brief ST7789 初始化
 *
 */
static void init()
{
    if (st7789.cfg.lcd_set_to_non_dma_mode)
    {
        st7789.cfg.lcd_set_to_non_dma_mode();
    }

    uint8_t _data[2]; /* 0: 命令 1: 数据 */

    /* 先判断 cfg.reset 是否为 NULL */
    if (st7789.cfg.reset)
        st7789.cfg.reset();
    vTaskDelay(pdMS_TO_TICKS(200));

    _data[0] = 0x01;
    st7789.cfg.write_command(_data[0]); /* 软件复位 */
    vTaskDelay(pdMS_TO_TICKS(200));

    _data[0] = 0x11;
    st7789.cfg.write_command(_data[0]); /* 关闭睡眠模式 */
    vTaskDelay(pdMS_TO_TICKS(200));

    _data[0] = 0x3A;
    _data[1] = 0x05;
    st7789.cfg.write_command(_data[0]);  /* 设置像素格式 */
    st7789.cfg.write_data(&_data[1], 1); /* 16位色彩模式 RGB-565 */

    _data[0] = 0x36;
    _data[1] = 0x60;                    /* 16位色彩模式 RGB-565 */
                                        /**
                                         * @brief 具体说明看 st7789 数据手册的 0x36 指令
                                         * 0x60: 屏幕横屏显示，左上角为原点
                                         * 0x00: 屏幕竖屏显示，左上角为原点
                                         */
    st7789.cfg.write_command(_data[0]); /* 设置像素格式 */
    st7789.cfg.write_data(&_data[1], 1);

    _data[0] = 0xB2;
    _data[1] = 0x0C;
    st7789.cfg.write_command(_data[0]); /* 设置VBP、VFP、VCP */
    st7789.cfg.write_data(&_data[1], 1);
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x00;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x33;
    st7789.cfg.write_data(&_data[1], 1);
    st7789.cfg.write_data(&_data[1], 1);

    _data[0] = 0xB7;
    st7789.cfg.write_command(_data[0]);
    _data[1] = 0x72;
    st7789.cfg.write_data(&_data[1], 1);

    _data[0] = 0xBB; // 设置电源控制
    st7789.cfg.write_command(_data[0]);
    _data[1] = 0x3D; /* VCOM = 参数 × 0.02V */
    st7789.cfg.write_data(&_data[1], 1);

    _data[0] = 0xC0; // 设置VCOM控制
    st7789.cfg.write_command(_data[0]);
    _data[1] = 0x2C; /* VCOM = 参数 × 0.02V */
    st7789.cfg.write_data(&_data[1], 1);

    _data[0] = 0xC2; // 设置VCOM电压
    st7789.cfg.write_command(_data[0]);
    _data[1] = 0x01;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0xff;
    st7789.cfg.write_data(&_data[1], 1);

    _data[0] = 0xC3; /* 设置VCOMH电压 */
    st7789.cfg.write_command(_data[0]);
    _data[1] = 0x19;
    st7789.cfg.write_data(&_data[1], 1);

    _data[0] = 0xC4; /* 设置VCOML电压 */
    st7789.cfg.write_command(_data[0]);
    _data[1] = 0x20;
    st7789.cfg.write_data(&_data[1], 1);

    _data[0] = 0xC6; /* 设置帧率 */
    st7789.cfg.write_command(_data[0]);
    _data[1] = 0x0F; /* 60Hz */
    st7789.cfg.write_data(&_data[1], 1);

    _data[0] = 0xD0; /* 设置功率控制 */
    st7789.cfg.write_command(_data[0]);
    _data[1] = 0xA4;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0xA1;
    st7789.cfg.write_data(&_data[1], 1);

    _data[0] = 0xE0; /* 设置伽马校正 */
    st7789.cfg.write_command(_data[0]);
    _data[1] = 0xD0;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x04;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x0D;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x11;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x13;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x2B;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x3F;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x54;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x4C;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x18;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x0D;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x0B;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x1F;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x23;
    st7789.cfg.write_data(&_data[1], 1);

    _data[0] = 0xE1; /* 设置伽马校正 */
    st7789.cfg.write_command(_data[0]);
    _data[1] = 0xE1;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0xD0;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x04;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x0C;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x11;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x13;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x2C;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x3F;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x44;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x51;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x2F;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x1F;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x1F;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x20;
    st7789.cfg.write_data(&_data[1], 1);
    _data[1] = 0x23;
    st7789.cfg.write_data(&_data[1], 1);

    display_on();
    lcd_blk_on(); /* 开启背光 */
}

/**
 * @brief 设置窗口
 *
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 */
static void set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    if (st7789.cfg.lcd_set_to_non_dma_mode)
    {
        st7789.cfg.lcd_set_to_non_dma_mode();
    }

    uint8_t _data[4];

    st7789.cfg.write_command(0x2A); /* Column */
    _data[0] = x0 >> 8;
    _data[1] = x0;
    _data[2] = x1 >> 8;
    _data[3] = x1;
    st7789.cfg.write_data(_data, 4);

    st7789.cfg.write_command(0x2B); /* Row */
    _data[0] = y0 >> 8;
    _data[1] = y0;
    _data[2] = y1 >> 8;
    _data[3] = y1;
    st7789.cfg.write_data(_data, 4);

    st7789.cfg.write_command(0x2C); /* RAM write */
}

static void draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    set_window(x, y, x, y);

    uint8_t buf[2] = {(uint8_t)(color >> 8), (uint8_t)(color)};
    st7789.cfg.write_data(buf, 2);
}

/**
 * @brief 用指定颜色全屏填充，调用前需提前设置好 setWindow
 *
 * @param color
 */
static void fill_color(uint16_t color)
{
    for (uint32_t i = 0; i < st7789.cfg.width * st7789.cfg.height; ++i)
    {
        color_buf[i] = color;
    }
    st7789.cfg.lcd_set_to_dma_mode(); /* 进入到 DMA 模式，开发发送像素数据 */
    lcd_write_pixel_data(color_buf, st7789.cfg.width * st7789.cfg.height);
}

/**
 * @brief 关闭显示
 *
 */
static void display_off(void) { st7789.cfg.write_command(0x28); }

/**
 * @brief 开启显示
 *
 */
static void display_on(void) { st7789.cfg.write_command(0x29); }

/**
 * @brief 退出睡眠模式
 *
 */
static void exit_sleep(void)
{
    st7789.cfg.write_command(0x11);
    vTaskDelay(pdMS_TO_TICKS(120));

    display_on(); /* 开启显示 */
    lcd_blk_on(); /* 开启背光 */
}

/**
 * @brief 进入睡眠模式
 *
 */
static void enter_sleep(void)
{
    display_off(); /* 关闭显示 */
    st7789.cfg.write_command(0x10);
    vTaskDelay(pdMS_TO_TICKS(120));

    lcd_blk_off(); /* 关闭背光 */
}

static void fill_demo(uint16_t color) { fill_color(color); }