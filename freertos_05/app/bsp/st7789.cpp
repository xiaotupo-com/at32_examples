#include "st7789.h"
#include "freertos_app.h"
#include "lcd_blk.h"

using namespace xtp;

/* 构造函数定义 */
ST7789::ST7789(const Config &config) : cfg(config) {}

/**
 * @brief ST7789 初始化
 *
 */
void ST7789::init()
{
    uint8_t _data[2]; /* 0: 命令 1: 数据 */

    /* 先判断 cfg.reset 是否为 NULL */
    if (cfg.reset)
        cfg.reset();
    vTaskDelay(pdMS_TO_TICKS(200));

    _data[0] = 0x01;
    cfg.write_command(_data[0]); /* 软件复位 */
    vTaskDelay(pdMS_TO_TICKS(200));

    _data[0] = 0x11;
    cfg.write_command(_data[0]); /* 关闭睡眠模式 */
    vTaskDelay(pdMS_TO_TICKS(200));

    _data[0] = 0x3A;
    _data[1] = 0x05;
    cfg.write_command(_data[0]);  /* 设置像素格式 */
    cfg.write_data(&_data[1], 1); /* 16位色彩模式 RGB-565 */

    _data[0] = 0x36;
    _data[1] = 0x60;             /* 16位色彩模式 RGB-565 */
                                 /**
                                  * @brief 具体说明看 st7789 数据手册的 0x36 指令
                                  * 0x60: 屏幕横屏显示，左上角为原点
                                  * 0x00: 屏幕竖屏显示，左上角为原点
                                  */
    cfg.write_command(_data[0]); /* 设置像素格式 */
    cfg.write_data(&_data[1], 1);

    _data[0] = 0xB2;
    _data[1] = 0x0C;
    cfg.write_command(_data[0]); /* 设置VBP、VFP、VCP */
    cfg.write_data(&_data[1], 1);
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x00;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x33;
    cfg.write_data(&_data[1], 1);
    cfg.write_data(&_data[1], 1);

    _data[0] = 0xB7;
    cfg.write_command(_data[0]);
    _data[1] = 0x72;
    cfg.write_data(&_data[1], 1);

    _data[0] = 0xBB; // 设置电源控制
    cfg.write_command(_data[0]);
    _data[1] = 0x3D; /* VCOM = 参数 × 0.02V */
    cfg.write_data(&_data[1], 1);

    _data[0] = 0xC0; // 设置VCOM控制
    cfg.write_command(_data[0]);
    _data[1] = 0x2C; /* VCOM = 参数 × 0.02V */
    cfg.write_data(&_data[1], 1);

    _data[0] = 0xC2; // 设置VCOM电压
    cfg.write_command(_data[0]);
    _data[1] = 0x01;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0xff;
    cfg.write_data(&_data[1], 1);

    _data[0] = 0xC3; /* 设置VCOMH电压 */
    cfg.write_command(_data[0]);
    _data[1] = 0x19;
    cfg.write_data(&_data[1], 1);

    _data[0] = 0xC4; /* 设置VCOML电压 */
    cfg.write_command(_data[0]);
    _data[1] = 0x20;
    cfg.write_data(&_data[1], 1);

    _data[0] = 0xC6; /* 设置帧率 */
    cfg.write_command(_data[0]);
    _data[1] = 0x0F; /* 60Hz */
    cfg.write_data(&_data[1], 1);

    _data[0] = 0xD0; /* 设置功率控制 */
    cfg.write_command(_data[0]);
    _data[1] = 0xA4;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0xA1;
    cfg.write_data(&_data[1], 1);

    _data[0] = 0xE0; /* 设置伽马校正 */
    cfg.write_command(_data[0]);
    _data[1] = 0xD0;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x04;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x0D;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x11;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x13;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x2B;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x3F;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x54;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x4C;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x18;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x0D;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x0B;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x1F;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x23;
    cfg.write_data(&_data[1], 1);

    _data[0] = 0xE1; /* 设置伽马校正 */
    cfg.write_command(_data[0]);
    _data[1] = 0xE1;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0xD0;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x04;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x0C;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x11;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x13;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x2C;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x3F;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x44;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x51;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x2F;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x1F;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x1F;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x20;
    cfg.write_data(&_data[1], 1);
    _data[1] = 0x23;
    cfg.write_data(&_data[1], 1);

    displayOn();
}

/**
 * @brief 设置窗口
 *
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 */
void ST7789::setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    uint8_t _data[4];

    cfg.write_command(0x2A); /* Column */
    _data[0] = x0 >> 8;
    _data[1] = x0;
    _data[2] = x1 >> 8;
    _data[3] = x1;
    cfg.write_data(_data, 4);

    cfg.write_command(0x2B); /* Row */
    _data[0] = y0 >> 8;
    _data[1] = y0;
    _data[2] = y1 >> 8;
    _data[3] = y1;
    cfg.write_data(_data, 4);

    cfg.write_command(0x2C); /* RAM write */
}

void ST7789::drawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    setWindow(x, y, x, y);

    uint8_t buf[2] = {static_cast<uint8_t>(color >> 8),
                      static_cast<uint8_t>(color)};
    cfg.write_data(buf, 2);
}

/**
 * @brief 全屏填充
 *
 * @param color
 */
void ST7789::fillColor(uint16_t color)
{
    setWindow(0, 0, cfg.width - 1, cfg.height - 1);
    uint8_t high = color >> 8;
    uint8_t low = color;

    for (uint32_t i = 0; i < cfg.width * cfg.height; ++i)
    {
        uint8_t buf[2] = {high, low};
        cfg.write_data(buf, 2);
    }
}

/**
 * @brief 关闭显示
 *
 */
void ST7789::displayOff(void) { cfg.write_command(0x28); }

/**
 * @brief 开启显示
 *
 */
void ST7789::displayOn(void) { cfg.write_command(0x29); }

/**
 * @brief 退出睡眠模式
 * 
 */
void ST7789::exitSleep(void) {
    cfg.write_command(0x11);
    vTaskDelay(pdMS_TO_TICKS(120));

    displayOn(); /* 开启显示 */
    
    lcd_blk_on(); /* 开启背光 */
}

/**
 * @brief 进入睡眠模式 
 * 
 */
void ST7789::enterSleep(void) {
    displayOff(); /* 关闭显示 */
    cfg.write_command(0x10);
    vTaskDelay(pdMS_TO_TICKS(120));

    lcd_blk_off();  /* 关闭背光 */
}