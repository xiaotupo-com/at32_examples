#ifndef __NTC_H
#define __NTC_H

#include "at32f435_437.h"

namespace xtp
{
    // Note Ntc 温度探头类
    class Ntc
    {
    public:
        Ntc(float high, float low);
        void setHighValue(float high);
        float getHighValue(void);
        void setLowValue(float low);
        float getLowValue(void);
		float get_temp(uint16_t adc_val);
		void setCurrentTemp(float temp);
		float getCurrentTemp(void);

    private:
        float m_currentTemp; /* 当前温度 */
        float m_highValue;   /* 高温报警值 */
        float m_lowValue;    /* 低温报警值*/
    };
}  // namespace xtp

#endif
