/**
 * @file st7789_config.h
 * @author xtp (xiaotupo@163.com)
 * @brief 
 * @version V0.1
 * @date 2025-07-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __ST7789_CONFIG_H
#define __ST7789_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "at32f435_437_wk_config.h"

struct ST7789Config_t
{
	void (*write_command)(uint8_t cmd);
	void (*write_data)(const uint8_t *data, uint32_t len);
	void (*reset)();
	void (*lcd_set_to_non_dma_mode)(void);
	void (*lcd_set_to_dma_mode)(void);
	uint16_t width;
	uint16_t height;
};
	
#ifdef __cplusplus
}
#endif

#endif
