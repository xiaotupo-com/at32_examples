/**
 * @file lcd1602.h
 * @author 小土坡 (xiaotupo@163.com)
 * @brief 
 * @version 0.1
 * @date 2025-08-01 定义 lcd1602_t 结构体
 * 
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __LCD1602_H
#define __LCD1602_H

#include "at32f435_437_wk_config.h"

#define LCD_RS(x) gpio_bits_write(LCD1602_RS_GPIO_PORT, LCD1602_RS_PIN, (x))
#define LCD_RW(x) gpio_bits_write(LCD1602_RW_GPIO_PORT, LCD1602_RW_PIN, (x))
#define LCD_EN(x) gpio_bits_write(LCD1602_EN_GPIO_PORT, LCD1602_EN_PIN, (x))
#define LCD_D4(x) gpio_bits_write(LCD1602_D4_GPIO_PORT, LCD1602_D4_PIN, (x))
#define LCD_D5(x) gpio_bits_write(LCD1602_D5_GPIO_PORT, LCD1602_D5_PIN, (x))
#define LCD_D6(x) gpio_bits_write(LCD1602_D6_GPIO_PORT, LCD1602_D6_PIN, (x))
#define LCD_D7(x) gpio_bits_write(LCD1602_D7_GPIO_PORT, LCD1602_D7_PIN, (x))

#define LCD_ROWS 2
#define LCD_COLS 16

struct lcd1602_t {
    void (*init)(void);
    void (*clear)(void);
    void (*set_cursor)(uint8_t row, uint8_t col);
    void (*print)(const char *str);
    void (*set_input_mode)(uint8_t cursor_dir, uint8_t display_shift);
    void (*set_cursor_mode)(uint8_t show, uint8_t blink);
	
	uint8_t cursor_col;
	uint8_t cursor_row;
	
	/* 当前在编辑的对象，下划线光标所在位置 */
	/* 把系统中需要编辑的对象列出来：*/
	/* H(0): 高温报警值 */
	/* L(1): 低温报警值 */
	uint8_t current_edit;
	
	/* H/L Width: 4 */
	uint8_t current_h_index; 	/* 光标在 H 处的第几位，共4位包括小数点 */
	uint8_t current_l_index;	/* 光标在 L 处的第几位，共4位包括小数点 */

};

extern struct lcd1602_t lcd;

#endif /* __LCD1602_H */