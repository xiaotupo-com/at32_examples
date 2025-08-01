#include "lcd1602.h"

#include "freertos_app.h"

/**
 * @brief us 延时函数,使用 DWT (Data Watchpoint and Trace) 计数器
 * * 该函数使用 DWT 的 CYCCNT 计数器来实现微秒级延时。
 * * 不要用该函数实现 ms 延时, 因为会降低系统性能。
 * * @note 该函数需要在系统启动时使能 DWT 计数器。
 * 
 * @param us 
 */
static void lcd_delay_us(uint32_t us)
{
	/* 仅在首次调用时初始化DWT（判断计数器是否未使能）*/
    if (!(DWT->CTRL & DWT_CTRL_CYCCNTENA_Msk)) {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;  // 使能调试跟踪
        DWT->CYCCNT = 0;                                 // 清零计数器
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;             // 使能CYCCNT
    }
	
	uint32_t start = DWT->CYCCNT;
	uint32_t ticks = (SystemCoreClock / 1000000) * us;
	while((DWT->CYCCNT - start) < ticks);
}

/**
 * @brief 写入 4 位数据到 LCD
 * * 该函数将 4 位数据写入 LCD 的数据端口。
 * 
 * 
 * @param data 
 */
static void lcd_write4(uint8_t data)
{
	LCD_D4((data >> 0) & 1);
	LCD_D5((data >> 1) & 1);
	LCD_D6((data >> 2) & 1);
	LCD_D7((data >> 3) & 1);
	
	LCD_EN(1);
	lcd_delay_us(1);
	LCD_EN(0);
	lcd_delay_us(30); /* 通过调整选择合适的延时 100 50 40 */
}

/**
 * @brief 写入命令到 LCD
 * 
 * @param cmd 
 */
static void lcd_write_cmd(uint8_t cmd)
{
	LCD_RS(0);
	LCD_RW(0);
	lcd_write4(cmd >> 4);
	lcd_write4(cmd & 0x0F);
	vTaskDelay(pdMS_TO_TICKS(2));
}

/**
 * @brief 写入数据到 LCD
 * 
 * @param data 
 */
static void lcd_write_data(uint8_t data)
{
	LCD_RS(1);
	LCD_RW(0);
	lcd_write4(data >> 4);
	lcd_write4(data & 0x0F);
	vTaskDelay(pdMS_TO_TICKS(2));
}

void lcd_set_cursor_mode(uint8_t show, uint8_t blink)
{
    xSemaphoreTake(lcdMutex_handle, portMAX_DELAY);
    uint8_t cmd = 0x0C; /* 0x08 | 0x04 (显示开，光标默认隐藏) */

    if (show) {
        cmd |= 0x02; /* 显示光标 */
        if (blink) {
            cmd |= 0x01; /* 光标闪烁 */
        }
    }
    lcd_write_cmd(cmd);
    xSemaphoreGive(lcdMutex_handle);
}

/**
 * @brief 配置LCD1602的输入模式（光标方向和屏幕滚动）
 * @param cursor_dir: 光标移动方向
 *                    0 - 光标左移（写入新字符后，光标向左移动）
 *                    1 - 光标右移（写入新字符后，光标向右移动，默认）
 * @param display_shift: 屏幕滚动控制
 *                       0 - 屏幕不滚动（仅光标移动，默认）
 *                       1 - 屏幕滚动（写入字符时，整个屏幕随光标移动方向滚动）
 */
void lcd_set_input_mode(uint8_t cursor_dir, uint8_t display_shift) {
    xSemaphoreTake(lcdMutex_handle, portMAX_DELAY);
    
    // 基础命令：0x04（进入模式设置）
    uint8_t cmd = 0x04;
    
    // 设置光标方向（D1位）
    if (cursor_dir) {
        cmd |= 0x02;  // 光标右移
    } else {
        cmd &= ~0x02; // 光标左移
    }
    
    // 设置屏幕滚动（D0位）
    if (display_shift) {
        cmd |= 0x01;  // 屏幕滚动
    } else {
        cmd &= ~0x01; // 屏幕不滚动
    }
    
    lcd_write_cmd(cmd);
    xSemaphoreGive(lcdMutex_handle);
}

/**
 * @brief 初始化 LCD1602
 * * 该函数初始化 LCD1602 显示器为 4 位模式, 2 行, 5x8 点阵。
 * * 包括清屏和设置输入模式。
 */
void lcd1602_init(void)
{
	vTaskDelay(pdMS_TO_TICKS(20)); /* 上电延时 */
	
	LCD_RS(0);
	LCD_RW(0);
	LCD_EN(0);
	
	// 初始化为 8 位模式
    lcd_write4(0x03);
    vTaskDelay(pdMS_TO_TICKS(5));
    lcd_write4(0x03);
    vTaskDelay(pdMS_TO_TICKS(1));
    lcd_write4(0x03);
	

    // 切换到 4 位模式
    lcd_write4(0x02);

    // 配置 4 位, 2 行, 5x8
    lcd_write_cmd(0x28);
    // 显示开, 光标关
    // lcd_write_cmd(0x0C);
    lcd_set_cursor_mode(0, 0); // 默认光标隐藏，不闪烁
    // 清屏
    lcd_write_cmd(0x01);
    vTaskDelay(pdMS_TO_TICKS(2));
    // 输入模式
    // lcd_write_cmd(0x06);
    lcd_set_input_mode(1, 0); // 默认光标右移，屏幕不滚动
}

/**
 * @brief 清除 LCD 显示内容
 * * 该函数清除 LCD 上的所有内容并将光标移动到起始位置。
 */
void lcd_clear(void)
{
    xSemaphoreTake(lcdMutex_handle, portMAX_DELAY);
    lcd_write_cmd(0x01);
    vTaskDelay(pdMS_TO_TICKS(2));
    xSemaphoreGive(lcdMutex_handle);
}

/**
 * @brief 设置 LCD 光标位置
 * * 该函数设置 LCD 上的光标位置。
 * 
 * @param row 行号 (0 或 1)
 * @param col 列号 (0 到 15)
 */
void lcd_set_cursor(uint8_t row, uint8_t col)
{
    xSemaphoreTake(lcdMutex_handle, portMAX_DELAY);
    uint8_t addr = (row == 0) ? 0x00 : 0x40;
    lcd_write_cmd(0x80 | (addr + col));
    xSemaphoreGive(lcdMutex_handle);
}

/**
 * @brief 在 LCD 上打印字符串
 * * 该函数将字符串逐字符写入 LCD。
 * 
 * @param str 要打印的字符串
 */
void lcd_print(const char *str)
{
    xSemaphoreTake(lcdMutex_handle, portMAX_DELAY);
    while (*str)
    {
        lcd_write_data(*str++);
    }
    xSemaphoreGive(lcdMutex_handle);
}