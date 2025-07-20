/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-07-18 21:34:52
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-07-19 20:43:54
 * @FilePath: \freertos_04\project\inc\lcd.h
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#ifndef __LCD_H
#define __LCD_H

#include "at32f435_437_gpio.h"
#include <stdint.h>

//颜色定义
#define WHITE   0xFFFF	//白色
#define YELLOW  0xFFE0	//黄色
#define BRRED   0XFC07  //棕红色
#define PINK    0XF81F	//粉色
#define RED     0xF800	//红色
#define BROWN   0XBC40  //棕色
#define GRAY    0X8430  //灰色
#define GBLUE   0X07FF	//兰色
#define GREEN   0x07E0	//绿色
#define BLUE    0x001F  //蓝色
#define BLACK   0x0000	//黑色

#define LCD_WIDTH   320
#define LCD_HEIGHT  240

#define LCD_CS_ENABLE()		gpio_bits_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, FALSE) 	/* 低电平有效 */
#define LCD_CS_DISABLE()	gpio_bits_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, TRUE)		/* 高电平失效 */

#define LCD_DC_CMD() 		gpio_bits_write(LCD_DC_GPIO_PORT, LCD_DC_PIN, FALSE)	/* 低电平写命令 */
#define LCD_DC_DATA()		gpio_bits_write(LCD_DC_GPIO_PORT, LCD_DC_PIN, TRUE)		/* 高电平写数据 */

#define LCD_BLK_ON()			gpio_bits_write(LCD_BLK_GPIO_PORT, LCD_BLK_PIN, TRUE)	/* 打开背光 */
#define LCD_BLK_OFF()			gpio_bits_write(LCD_BLK_GPIO_PORT, LCD_BLK_PIN, FALSE)	/* 关闭背光 */


void st7789_reset(void);
void lcd_init();
void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7789_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void st7789_write_command(uint8_t _cmd);
void displayOn();
void lcd_clear(uint16_t color);
#endif /* __LCD_H */
