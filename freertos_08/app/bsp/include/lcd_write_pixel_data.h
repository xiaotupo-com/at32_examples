/**
 * @file lcd_write_pixel_data.h
 * @author xtp (xiaotupo@163.com)
 * @brief 
 * @version V0.1
 * @date 2025-07-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __LCD_WRITE_PIXEL_DATA_H
#define __LCD_WRITE_PIXEL_DATA_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "at32f435_437_wk_config.h"
#include "freertos_app.h"


void lcd_write_pixel_data(uint16_t *data, uint32_t total_len);

	
#ifdef __cplusplus
}
#endif

#endif
