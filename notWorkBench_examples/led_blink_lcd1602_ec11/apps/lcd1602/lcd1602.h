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

#include "at32f435_437.h"
#include "at32f435_437_gpio.h"
#include "gpio_init.h"

#define LCD_RS(x) gpio_bits_write(LCD1602_RS_PORT, LCD1602_RS_PIN, static_cast<confirm_state>(x))
#define LCD_RW(x) gpio_bits_write(LCD1602_RW_PORT, LCD1602_RW_PIN, static_cast<confirm_state>(x))
#define LCD_EN(x) gpio_bits_write(LCD1602_EN_PORT, LCD1602_EN_PIN, static_cast<confirm_state>(x))
#define LCD_D4(x) gpio_bits_write(LCD1602_D4_PORT, LCD1602_D4_PIN, static_cast<confirm_state>(x))
#define LCD_D5(x) gpio_bits_write(LCD1602_D5_PORT, LCD1602_D5_PIN, static_cast<confirm_state>(x))
#define LCD_D6(x) gpio_bits_write(LCD1602_D6_PORT, LCD1602_D6_PIN, static_cast<confirm_state>(x))
#define LCD_D7(x) gpio_bits_write(LCD1602_D7_PORT, LCD1602_D7_PIN, static_cast<confirm_state>(x))

#define LCD_ROWS 2
#define LCD_COLS 16

class Lcd1602
{
public:
	Lcd1602();
    void init(void);
	void setCursorMode(bool isShow, bool isBlink);
	void setInputMode(uint8_t cursor_dir = 1, uint8_t display_shift = 0);
	void clear(void);
	void setCursorPos(uint8_t row, uint8_t col);
	void print(const char* str);

private:
    void write4(uint8_t data);
    void writeCmd(uint8_t cmd);
	void writeData(uint8_t data);

	uint8_t edit_mode; /* 0=编辑电压，1=编辑电流 */
	uint8_t voltage_index; /* 三位整数，一位小数 */
	uint8_t current_index; /* 三位整数，一位小数 */

	const uint8_t voltage_digit_cols[4] = {7, 8, 9, 11};
	const uint8_t current_digit_cols[4] = {7, 8, 9, 11};

};

#endif /* __LCD1602_H */