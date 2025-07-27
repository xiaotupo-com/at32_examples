#include "lcd_blk.h"

#include "at32f435_437_wk_config.h"

void lcd_blk_on(void) { gpio_bits_write(LCD_BLK_GPIO_PORT, LCD_BLK_PIN, 1); }
void lcd_blk_off(void) { gpio_bits_write(LCD_BLK_GPIO_PORT, LCD_BLK_PIN, 0); }