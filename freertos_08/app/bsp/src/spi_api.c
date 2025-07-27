#include "spi_api.h"
#include "freertos_app.h"
#include "debug.h"


/**
 * @brief 配置为非 DMA 模式，SPI 传输 8-bit 数据
 * 调用位置：
 * 1. st7789.c -> init() 函数中
 * 2. st7780.c -> set_window() 函数中
 */
void lcd_set_to_non_dma_mode()
{
    dma_channel_enable(DMA1_CHANNEL1, FALSE);               // 关闭 DMA 通道
    spi_i2s_dma_transmitter_enable(SPI1, FALSE);            // 关闭 SPI DMA 功能
    spi_frame_bit_num_set(SPI1, SPI_FRAME_8BIT);            // SPI 切换为 8bit 模式
}

/**
 * @brief 配置为 DMA 模式，SPI 传输 16-bit 数据
 * 调用位置：
 * 1. ST7789.c -> fill_color() 函数中
 */
void lcd_set_to_dma_mode()
{
    spi_frame_bit_num_set(SPI1, SPI_FRAME_16BIT);           // SPI 切换为 16bit 模式
    spi_i2s_dma_transmitter_enable(SPI1, TRUE);             // 开启 SPI DMA 功能
}

/**
 * @brief spi 写命令
 * 
 * @param cmd 
 */
void spi_write_cmd(uint8_t cmd)
{
    gpio_bits_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, 0);
    gpio_bits_write(LCD_DC_GPIO_PORT, LCD_DC_PIN, 0);

   while (spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET) {}
   spi_i2s_data_transmit(SPI1, cmd);
   while (spi_i2s_flag_get(SPI1, SPI_I2S_BF_FLAG) == SET) {} // 等待发送完成
	LOG("spi cmd 发送完成\n");
	
    gpio_bits_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, 1);
}

/**
 * @brief spi 写数据(非 DMA 模式)
 * 
 * @param data 
 * @param len 
 */
void spi_write_data(const uint8_t *data, uint32_t len)
{
    gpio_bits_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, 0);
    gpio_bits_write(LCD_DC_GPIO_PORT, LCD_DC_PIN, 1);

    for (uint32_t i = 0; i < len; i++)
    {
        while (spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET) {}
        spi_i2s_data_transmit(SPI1, data[i]);
    }
	while (spi_i2s_flag_get(SPI1, SPI_I2S_BF_FLAG) == SET) {} // 等待发送完成

		LOG("spi data 发送完成\n");
    gpio_bits_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, 1);
}



void lcd_reset(void)
{
    gpio_bits_write(LCD_REST_GPIO_PORT, LCD_REST_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(200));
    gpio_bits_write(LCD_REST_GPIO_PORT, LCD_REST_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(200));
}