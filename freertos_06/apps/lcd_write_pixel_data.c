/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-07-23 19:45:20
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-07-26 00:40:31
 * @FilePath: \freertos_04d:\dev\at32_work\learn-examples\freertos_06\apps\lcd_write_pixel_data.c
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

#include "wk_dma.h"

/**
 * @brief DMA 发送像素数据到 LCD
 *
 * @param data
 * @param len
 */
void lcd_write_pixel_data(uint16_t *data, uint32_t len)
{

    /* 先关闭 DMA */
    dma_channel_enable(DMA1_CHANNEL1, FALSE);

    wk_dma_channel_config(
        DMA1_CHANNEL1, (uint32_t)&SPI1->dt, (uint32_t)data, len);


    /* 需要在 DMA 发送完成回调中关闭 SPI 的 DMA 使能 */
    spi_i2s_dma_transmitter_enable(SPI1, true);

    /* 使能 DMA */
    dma_channel_enable(DMA1_CHANNEL1, TRUE);  
}

