/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-07-23 19:44:37
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-07-26 01:08:56
 * @FilePath: \freertos_04d:\dev\at32_work\learn-examples\freertos_06\apps\lcd_write_pixel_data.h
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#ifndef __LCD_WRITE_PIXEL_DATA_H
#define __LCD_WRITE_PIXEL_DATA_H

#include "at32f435_437_wk_config.h"
#include "freertos_app.h"


void lcd_write_pixel_data(uint16_t *data, uint32_t len);

#endif
