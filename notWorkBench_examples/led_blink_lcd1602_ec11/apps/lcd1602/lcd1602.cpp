#include "lcd1602.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "us_delay.h"
#include "printf_config.h"

SemaphoreHandle_t lcdMutex_handle = NULL;


Lcd1602::Lcd1602()
{
	
}


/**
 * @brief 写入 4 位数据到 LCD
 * * 该函数将 4 位数据写入 LCD 的数据端口。
 *
 *
 * @param data
 */
void Lcd1602::write4(uint8_t data)
{
    LCD_D4((data >> 0) & 1);
    LCD_D5((data >> 1) & 1);
    LCD_D6((data >> 2) & 1);
    LCD_D7((data >> 3) & 1);

    LCD_EN(1);
    delay_us(1);
    LCD_EN(0);
    delay_us(30); /* 通过调整选择合适的延时 100 50 40 */
}

/**
 * @brief 写命令
 *
 * @param cmd
 */
void Lcd1602::writeCmd(uint8_t cmd)
{
    LCD_RS(0);
    LCD_RW(0);
    write4(cmd >> 4);
    write4(cmd & 0x0F);
    vTaskDelay(pdMS_TO_TICKS(2));
}

void Lcd1602::writeData(uint8_t data)
{
    LCD_RS(1);
    LCD_RW(0);
    write4(data >> 4);
    write4(data & 0x0F);
    vTaskDelay(pdMS_TO_TICKS(2));
}

/**
 * @brief
 *
 * @param show 	true: 显示光标
 * 				false: 隐藏光标
 * @param blink true: 光标闪烁
 * 				false: 光标不闪烁
 */
void Lcd1602::setCursorMode(bool isShow, bool isBlink)
{
    xSemaphoreTake(lcdMutex_handle, portMAX_DELAY);
    uint8_t cmd = 0x0C; /* 0x08 | 0x04 (显示开，光标默认隐藏) */

    if (isShow)
    {
        cmd |= 0x02; /* 显示光标 */
        if (isBlink) { cmd |= 0x01; /* 光标闪烁 */ }
    }
    writeCmd(cmd);
    xSemaphoreGive(lcdMutex_handle);
}

/**
 * @brief
 *
 * @param cursor_dir 光标移动方向设置
 * 					0 - 光标左移（写入新字符后，光标向左移动）
 * 					1 - 光标右移（写入新字符后，光标向右移动，默认）
 * @param display_shift 屏幕滚动设置
 * 					0 - 屏幕不滚动（仅光标移动，默认）
 * 					1 - 屏幕滚动（写入字符时，整个屏幕随光标移动方向滚动）
 */
void Lcd1602::setInputMode(uint8_t cursor_dir, uint8_t display_shift)
{
    xSemaphoreTake(lcdMutex_handle, portMAX_DELAY);

    // 基础命令：0x04（进入模式设置）
    uint8_t cmd = 0x04;

    // 设置光标方向（D1位）
    if (cursor_dir)
    {
        cmd |= 0x02;  // 光标右移
    }
    else
    {
        cmd &= ~0x02;  // 光标左移
    }

    // 设置屏幕滚动（D0位）
    if (display_shift)
    {
        cmd |= 0x01;  // 屏幕滚动
    }
    else
    {
        cmd &= ~0x01;  // 屏幕不滚动
    }

    writeCmd(cmd);
    xSemaphoreGive(lcdMutex_handle);
}

void Lcd1602::init(void)
{
	lcdMutex_handle = xSemaphoreCreateMutex();
	configASSERT(lcdMutex_handle != NULL); /* 确保互斥锁创建成功 */
	
    vTaskDelay(pdMS_TO_TICKS(20)); /* 上电延时 */
    LCD_RS(0);
    LCD_RW(0);
    LCD_EN(0);

    // 初始化为 8 位模式
    write4(0x03);
    vTaskDelay(pdMS_TO_TICKS(5));
    write4(0x03);
    vTaskDelay(pdMS_TO_TICKS(1));
    write4(0x03);

    // 切换到 4 位模式
    write4(0x02);

    // 配置 4 位, 2 行, 5x8
    writeCmd(0x28);

    setCursorMode(true, false);  // 默认光标隐藏，不闪烁
    // 清屏
    writeCmd(0x01);
    vTaskDelay(pdMS_TO_TICKS(2));
    // 输入模式

    setInputMode();  // 默认光标右移，屏幕不滚动
}

void Lcd1602::clear(void)
{
	xSemaphoreTake(lcdMutex_handle, portMAX_DELAY);
    writeCmd(0x01);
    vTaskDelay(pdMS_TO_TICKS(2));
    xSemaphoreGive(lcdMutex_handle);
}

void Lcd1602::setCursorPos(uint8_t row, uint8_t col)
{
	xSemaphoreTake(lcdMutex_handle, portMAX_DELAY);
    uint8_t addr = (row == 0) ? 0x00 : 0x40;
    writeCmd(0x80 | (addr + col));
    xSemaphoreGive(lcdMutex_handle);
}

void Lcd1602::print(const char* str)
{
	xSemaphoreTake(lcdMutex_handle, portMAX_DELAY);
    while (*str)
    {
        writeData(*str++);
    }
    xSemaphoreGive(lcdMutex_handle);
}

