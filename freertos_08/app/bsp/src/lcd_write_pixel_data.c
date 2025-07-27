/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-07-23 19:45:20
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-07-26 00:40:31
 * @FilePath:
 * \freertos_04d:\dev\at32_work\learn-examples\freertos_06\apps\lcd_write_pixel_data.c
 * \freertos_04d:\dev\at32_work\learn-examples\freertos_06\apps\lcd_write_pixel_data.c
 * \freertos_04d:\dev\at32_work\learn-examples\freertos_06\apps\lcd_write_pixel_data.c
 * \freertos_04d:\dev\at32_work\learn-examples\freertos_06\apps\lcd_write_pixel_data.c
 * \freertos_04d:\dev\at32_work\learn-examples\freertos_06\apps\lcd_write_pixel_data.c
 * \freertos_04d:\dev\at32_work\learn-examples\freertos_06\apps\lcd_write_pixel_data.c
 * \freertos_04d:\dev\at32_work\learn-examples\freertos_06\apps\lcd_write_pixel_data.c
 * @Description:
 *
 * Copyright (c) 2025 by 小土坡, All Rights Reserved.
 */
#include "lcd_write_pixel_data.h"

#include <stdbool.h>
#include "debug.h"
#include "freertos_app.h"
#include "wk_dma.h"


extern SemaphoreHandle_t lcd_dma_semaphore_handle;

/* DMA最大单次传输长度 */
#define DMA_MAX_TRANSFER_LEN 65535

/**
 * @brief 启动 DMA 传输
 *
 * @param data 要发送的数据缓冲区
 * @param len 数据长度（单位：像素个数）
 */
void dma_start_transfer(const uint16_t *data, uint32_t len)
{
    /* 先关闭 DMA */
    dma_channel_enable(DMA1_CHANNEL1, FALSE);

	dma_interrupt_enable(DMA1_CHANNEL1, DMA_FDT_INT, TRUE); /* 使能 DMA 中断 */
	
    wk_dma_channel_config(
        DMA1_CHANNEL1, (uint32_t)&SPI1->dt, (uint32_t)data, len);

    /* 需要在 DMA 发送完成回调中关闭 SPI 的 DMA 使能 */
    spi_i2s_dma_transmitter_enable(SPI1, true);

    /* 使能 DMA */
    dma_channel_enable(DMA1_CHANNEL1, TRUE);
}

/**
 * @brief LCD 写入像素数据
 *
 * @param data 像素数据缓冲区
 * @param total_len 总像素个数
 */
void lcd_write_pixel_data(uint16_t *data, uint32_t total_len)
{   
    gpio_bits_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, 0);
    gpio_bits_write(LCD_DC_GPIO_PORT, LCD_DC_PIN, 1);

    if (total_len <= DMA_MAX_TRANSFER_LEN)
    {
        // 单次传输即可完成
        dma_start_transfer(data, total_len);
        // 等待传输完成
        if (xSemaphoreTake(lcd_dma_semaphore_handle, pdMS_TO_TICKS(1000)) ==
            pdTRUE)
        {
            LOG("DMA 发送完成\n");
        }
        else
        {
            LOG("DMA 发送超时\n");
        }
    }
    else
    {
        // 第一次传输：最大长度
        uint32_t first_len = DMA_MAX_TRANSFER_LEN;
        dma_start_transfer(data, first_len);
        // 等待第一次传输完成
        if (xSemaphoreTake(lcd_dma_semaphore_handle, pdMS_TO_TICKS(1000)) ==
            pdTRUE)
        {
            LOG("DMA 第一次发送完成\n");
        }
        else
        {
            LOG("DMA 第一次发送超时\n");
        }

        // 第二次传输：剩余数据
        uint32_t second_len = total_len - first_len;
        const uint16_t *second_buf = data + first_len;
        dma_start_transfer(second_buf, second_len);
        // 等待第二次传输完成
        if (xSemaphoreTake(lcd_dma_semaphore_handle, pdMS_TO_TICKS(1000)) ==
            pdTRUE)
        {
            LOG("DMA 第二次发送完成\n");
        }
        else
        {
            LOG("DMA 第二次发送超时\n");
        }
    }

    gpio_bits_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, 1);
}
