#include "lcd.h"
#include "FreeRTOS.h"
#include "at32f435_437_spi.h"
#include "freertos_app.h"

#include "at32f435_437_wk_config.h"

void lcd_res_pin_set(uint8_t level)
{
    gpio_bits_write(LCD_RES_GPIO_PORT, LCD_RES_PIN, level);
}

/**
 * @brief 向 ST7789 芯片写命令
 *
 * @param _cmd
 */
void st7789_write_command(uint8_t _cmd)
{
    LCD_CS_ENABLE();
    LCD_DC_CMD();

    while (spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET) {}
    spi_i2s_data_transmit(SPI1, _cmd);
    while (spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET) {}
    LCD_CS_DISABLE();
}

/**
 * @brief 向 ST7789 芯片写数据
 *
 * @param _data
 */
static void st7789_write_data(uint8_t _data)
{
    LCD_CS_ENABLE();
    LCD_DC_DATA();

    while (spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET) {}
    spi_i2s_data_transmit(SPI1, _data);
    while (spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET) {}
    LCD_CS_DISABLE();
}

/**
 * @brief LCD 初始化
 *
 */
void lcd_init()
{
    LCD_CS_ENABLE();
    st7789_reset();
    st7789_write_command(0x01); /* 软件复位 */
    vTaskDelay(pdMS_TO_TICKS(200));

    st7789_write_command(0x11); /* 关闭睡眠模式 */
    vTaskDelay(pdMS_TO_TICKS(200));

    st7789_write_command(0x3A); // 设置像素格式
    st7789_write_data(0x05);    // 16位色彩模式

    st7789_write_command(0x36); // 设置内存数据访问控制（MADCTL）
    /**
     * @brief 具体说明看 st7789 数据手册的 0x36 指令
     * 0x60: 屏幕横屏显示，左上角为原点
     * 0x00: 屏幕竖屏显示，左上角为原点
     */
    st7789_write_data(0x60); // 根据需要设置显示方向等参数

    st7789_write_command(0xB2); // 设置VBP、VFP、VCP
    st7789_write_data(0x0C);
    st7789_write_data(0x0C);
    st7789_write_data(0x00);
    st7789_write_data(0x33);
    st7789_write_data(0x33);
    /* 设置显示模式：决定屏幕接受颜色数据的顺序，是 RGB 还是 BGR*/
    st7789_write_command(0xB7);
    st7789_write_data(0x72);

    st7789_write_command(0xBB); // 设置电源控制
    st7789_write_data(0x3D);    /* VCOM = 参数 × 0.02V */

    st7789_write_command(0xC0); // 设置VCOM控制
    st7789_write_data(0x2C);

    st7789_write_command(0xC2); // 设置VCOM电压
    st7789_write_data(0x01);
    st7789_write_data(0xff);

    st7789_write_command(0xC3); // 设置VCOMH电压
    st7789_write_data(0x19);

    st7789_write_command(0xC4); // 设置VCOML电压
    st7789_write_data(0x20);

    st7789_write_command(0xC6); // 设置帧率
    st7789_write_data(0x0F);    /* 60Hz */

    st7789_write_command(0xD0); // 设置功率控制
    st7789_write_data(0xA4);
    st7789_write_data(0xA1);

    st7789_write_command(0xE0); // 设置伽马校正
    st7789_write_data(0xD0);
    st7789_write_data(0x04);
    st7789_write_data(0x0D);
    st7789_write_data(0x11);
    st7789_write_data(0x13);
    st7789_write_data(0x2B);
    st7789_write_data(0x3F);
    st7789_write_data(0x54);
    st7789_write_data(0x4C);
    st7789_write_data(0x18);
    st7789_write_data(0x0D);
    st7789_write_data(0x0B);
    st7789_write_data(0x1F);
    st7789_write_data(0x23);

    st7789_write_command(0xE1); // 设置伽马校正
    st7789_write_data(0xE1);
    st7789_write_data(0xD0);
    st7789_write_data(0x04);
    st7789_write_data(0x0C);
    st7789_write_data(0x11);
    st7789_write_data(0x13);
    st7789_write_data(0x2C);
    st7789_write_data(0x3F);
    st7789_write_data(0x44);
    st7789_write_data(0x51);
    st7789_write_data(0x2F);
    st7789_write_data(0x1F);
    st7789_write_data(0x1F);
    st7789_write_data(0x20);
    st7789_write_data(0x23);

    // st7789_write_command(0x21); // 反显模式
    st7789_write_command(0x29); // 显示开启
}

/**
 * @brief 设置显示窗口
 *
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 */
void ST7789_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    st7789_write_command(0x2A); /* 列地址设置 */
    st7789_write_data(x1 >> 8);
    st7789_write_data(x1);
    st7789_write_data(x2 >> 8);
    st7789_write_data(x2);

    st7789_write_command(0x2B); /* 行地址设置 */
    st7789_write_data(y1 >> 8);
    st7789_write_data(y1);
    st7789_write_data(y2 >> 8);
    st7789_write_data(y2);

    st7789_write_command(0x2C); /* 内存写 */
}

/**
 * @brief 在指定位置画一个点
 *
 * @param x
 * @param y
 * @param color
 */
void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    ST7789_SetWindow(x, y, x, y);
    st7789_write_data(color >> 8); // 写高位
    st7789_write_data(color);      // 写低位
    displayOn();
}

/**
 * @brief ST7789 硬件复位
 *
 */
void st7789_reset(void)
{
    lcd_res_pin_set(0);
    vTaskDelay(pdMS_TO_TICKS(200));
    lcd_res_pin_set(1);
    vTaskDelay(pdMS_TO_TICKS(200));
}

void displayOn()
{
    st7789_write_command(0x11);
    st7789_write_command(0x29);
}

void lcd_clear(uint16_t color)
{
    ST7789_SetWindow(0, 0, LCD_WIDTH, LCD_HEIGHT);
    for (int i = 0; i < 320 * 240; i++)
    {
        st7789_write_data(color >> 8);
        st7789_write_data(color);
    }
    displayOn();
}