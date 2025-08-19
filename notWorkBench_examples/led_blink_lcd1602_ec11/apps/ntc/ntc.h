#ifndef __NTC_H
#define __NTC_H

#include "at32f435_437.h"

struct ntc_t {
	float h_value;
	float l_value;
	float value;
	float (*get_temp)(uint16_t adc_val);
	void (*set_h)(struct ntc_t *, float value);
	void (*set_l)(struct ntc_t *, float value);
};

extern struct ntc_t ntc1;
#endif
