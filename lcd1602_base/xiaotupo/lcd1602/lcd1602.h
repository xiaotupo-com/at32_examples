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

void lcd1602_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *str);
void lcd_set_input_mode(uint8_t cursor_dir, uint8_t display_shift);
void lcd_set_cursor_mode(uint8_t show, uint8_t blink);

#endif /* __LCD1602_H */