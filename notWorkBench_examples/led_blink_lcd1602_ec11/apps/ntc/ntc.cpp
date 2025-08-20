#include "ntc.h"
#include <stdio.h>

#include <math.h>
#include <stdint.h>

#define R_FIXED     10000.0f   // 固定电阻10k
#define NTC_R0      10000.0f   // 25℃时阻值10k
#define B_VALUE     3950.0f
#define T0          298.15f    // 25℃开尔文温度
#define ADC_MAX     4095.0f

/**
 * @brief 
 * 
 * @param adc_val 
 * @return float 
 */
float xtp::Ntc::get_temp(uint16_t adc_val)
{
    if (adc_val >= ADC_MAX) return -999.9f; // 避免除零

    // 1️⃣ 计算NTC阻值
    float r_ntc = R_FIXED * ((float)adc_val / (ADC_MAX - adc_val));

    // 2️⃣ Beta公式计算温度
    float tempK = 1.0f / (1.0f/T0 + (1.0f/B_VALUE) * logf(r_ntc / NTC_R0));

    // 3️⃣ 转摄氏度
    return tempK - 273.15f;
}

/**
 * @brief Construct a new xtp::Ntc::Ntc object
 * 
 * @param high 
 * @param low 
 */
xtp::Ntc::Ntc(float high, float low)
{
	m_highValue = high;
	m_lowValue = low;
}

void xtp::Ntc::setHighValue(float high)
{
	m_highValue = high;
}

float xtp::Ntc::getHighValue(void)
{
	return m_highValue;
}

void xtp::Ntc::setLowValue(float low)
{
	m_lowValue = low;
}

float xtp::Ntc::getLowValue(void)
{
	return m_lowValue;
}

void xtp::Ntc::setCurrentTemp(float temp){
	m_currentTemp = temp;
}
		float xtp::Ntc::getCurrentTemp(void)
		{
			return m_currentTemp;
		}