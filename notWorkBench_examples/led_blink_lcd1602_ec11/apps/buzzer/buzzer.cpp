/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-17 22:15:51
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-18 01:15:41
 * @FilePath: buzzer.cpp
 * @Description:
 *
 * Copyright (c) 2025 by 小土坡, All Rights Reserved.
 */
#include "buzzer.h"

Buzzer::Buzzer(gpio_type *gpio_x, uint16_t pins)
{
    m_port = gpio_x;
    m_pin = pins;
    m_count = 0;
    m_stopValue = 10; /* 响多少 ms */
    m_isActive = false;
    m_isDisabled = false; /* 默认启用 Buzzer */
}

/**
 * 调用位置: vApplicationTickHook(void)
 * 使用: 我们在需要响一下蜂鸣器时只要设置 m_isActive 为 true 即可
 * 蜂鸣器响过后自动会把 m_isActive 设置为 false
 * 蜂鸣器会发出响声，当声音长度达到 m_stopValue 时会自动关闭蜂鸣器，并且清除 m_onCount 和 m_isActive
 */
void Buzzer::run(void)
{
    /* m_isDisabled 判断 Buzzer 是否禁用 */
    if (m_isDisabled == false && m_isActive == true)
    {
        gpio_bits_write(m_port, m_pin, TRUE);
        m_count++;
        if (m_count >= m_stopValue)
        {
            gpio_bits_write(m_port, m_pin, FALSE);
            m_count = 0;
            m_isActive = false;
        }
    }
}

/**
 * @brief
 *
 * @param _isActive true: 蜂鸣器开始响，响完后自动设置为 false
 */
void Buzzer::setIsActive(bool _isActive) { m_isActive = _isActive; }

/**
 * @brief 设置是否禁用 Buzzer
 *
 * @param _isDisabled
 * 			true: 禁用 Buzzer
 * 			false: 启用 Buzzer
 */
void Buzzer::setIsDisabled(bool _isDisabled) { m_isDisabled = _isDisabled; }

/**
 * @brief 翻转 m_isDisabled 禁用状态
 * 
 */
void Buzzer::toggleDisabled(void)
{
    setIsDisabled(!m_isDisabled);
    if (m_isDisabled) {
        off();
    } else {
        setIsActive(true); /* 让蜂鸣器响一下 */
    }
}


void Buzzer::off(void)
{
    gpio_bits_write(m_port, m_pin, FALSE);
}