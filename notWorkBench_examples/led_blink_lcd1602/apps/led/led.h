/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-15 23:39:20
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-22 19:43:48
 * @FilePath: \MDK_V5d:\projects\at32_examples\ec11_example\sources\led.h
 * @Description:
 *
 * Copyright (c) 2025 by 小土坡, All Rights Reserved.
 */
#ifndef __LED_H
#define __LED_H

#include "at32f435_437.h"

class Led
{
private:
	uint16_t m_countValue;
	uint8_t m_stepValue;
	uint32_t m_countStopValue;
	bool m_isRun;
	gpio_type *m_port;
	uint16_t m_pin;
	
public:
	Led(gpio_type *gpio_x, uint16_t pins);
	void run();
	void setIsRun(bool v);
	void setStepValue(uint8_t value);
	uint8_t getStepValue();
	void setCountStopValue(uint32_t value);
	uint32_t getCountStopValue();
	uint16_t getCountValue();
	void toggle();
};

#endif  // __LED_H
