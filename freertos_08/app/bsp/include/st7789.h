/**
 * @file st7789.h
 * @author xtp (xiaotupo@163.com)
 * @brief 
 * @version V0.1
 * @date 2025-07-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __ST7789_H
#define __ST7789_H

#include "at32f435_437_wk_config.h"
#include "st7789_config.h"

#define LCD_WIDTH	320
#define LCD_HEIGHT	240

struct ST7789
{
	void (*init)();
	void (*fill_color)(uint16_t color);
	void (*draw_pixel)(uint16_t x, uint16_t y, uint16_t color);
	void (*display_off)(void);
	void (*display_on)(void);
	void (*exit_sleep)(void);
	void (*enter_sleep)(void);
	void (*fill_demo)(uint16_t color);
	void (*set_window)(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
	struct ST7789Config_t cfg;
};

extern struct ST7789 st7789;

#endif /* __ST7789_H */
