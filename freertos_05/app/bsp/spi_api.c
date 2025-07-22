#include "spi_api.h"
#include "freertos_app.h"

void spi_write_cmd(uint8_t cmd)
{
    gpio_bits_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, 0);
    gpio_bits_write(LCD_DC_GPIO_PORT, LCD_DC_PIN, 0);

    while (spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET) {}
    spi_i2s_data_transmit(SPI1, cmd);
    while (spi_i2s_flag_get(SPI1, SPI_I2S_BF_FLAG) == SET) {} // 等待发送完成

    gpio_bits_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, 1);
}
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

    gpio_bits_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, 1);
}
void lcd_reset(void)
{
    gpio_bits_write(LCD_REST_GPIO_PORT, LCD_REST_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(200));
    gpio_bits_write(LCD_REST_GPIO_PORT, LCD_REST_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(200));
}