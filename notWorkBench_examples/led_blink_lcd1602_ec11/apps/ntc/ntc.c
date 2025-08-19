#include "ntc.h"
#include <stdio.h>

#include <math.h>
#include <stdint.h>

#define R_FIXED     10000.0f   // 固定电阻10k
#define NTC_R0      10000.0f   // 25℃时阻值10k
#define B_VALUE     3950.0f
#define T0          298.15f    // 25℃开尔文温度
#define ADC_MAX     4095.0f

static float get_temp(uint16_t adc_val);
static void set_h(struct ntc_t *, float value);
static void set_l(struct ntc_t *, float value);

struct ntc_t ntc1 = {
	.h_value = 85.0f,
	.l_value = 32.0f,
	.get_temp = get_temp,
	.set_h = set_h,
	.set_l = set_l
};


static void set_h(struct ntc_t *ntc, float value)
{
	if (ntc != NULL) {
		ntc->h_value = value;
	}
}

static void set_l(struct ntc_t *ntc, float value)
{
	if (ntc != NULL) {
		ntc->l_value = value;
	}
}




static float get_temp(uint16_t adc_val)
{
    if (adc_val >= ADC_MAX) return -999.9f; // 避免除零

    // 1️⃣ 计算NTC阻值
    float r_ntc = R_FIXED * ((float)adc_val / (ADC_MAX - adc_val));

    // 2️⃣ Beta公式计算温度
    float tempK = 1.0f / (1.0f/T0 + (1.0f/B_VALUE) * logf(r_ntc / NTC_R0));

    // 3️⃣ 转摄氏度
    return tempK - 273.15f;
}
