/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-13 20:19:26
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-22 19:42:29
 * @FilePath: led.cpp
 * @Description:
 *
 * Copyright (c) 2025 by 小土坡, All Rights Reserved.
 */
#include "led.h"

Led::Led(gpio_type *gpio_x, uint16_t pins)
{
	/* 初始化成员变量 */
	m_countValue = 0;
	m_stepValue = 10;
	m_countStopValue = 500;
	m_isRun = true;
    m_port = gpio_x;
    m_pin = pins;
}

// 该函数需要放到滴答定时器的中断函数中，进行 1ms 扫描一次
void Led::run()
{
    if (m_isRun) {
        m_countValue++;
        if (m_countValue >= m_countStopValue) {
            m_countValue = 0; // Clear
            m_port->odt ^= m_pin;
        }
    }
}

void Led::setIsRun(bool v)
{
    if (v == false)
    {
        gpio_bits_write(m_port, m_pin, TRUE);
        m_isRun = false;
    } else {
        m_isRun = true;
    }
}

void Led::toggle()
{
	m_port->odt ^= m_pin;
}

void Led::setStepValue(uint8_t value)
{
	m_stepValue = value;
}

void Led::setCountStopValue(uint32_t value)
{
	m_countStopValue = value;
}

uint32_t Led::getCountStopValue()
{
	return m_countStopValue;
}

uint8_t Led::getStepValue()
{
	return m_stepValue;
}

uint16_t Led::getCountValue()
{
	return m_countValue;
}