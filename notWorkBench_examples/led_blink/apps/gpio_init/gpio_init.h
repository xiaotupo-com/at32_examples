#ifndef __GPIO_INIT_H
#define __GPIO_INIT_H

#include "at32f435_437.h"

#define LED2_PORT  GPIOG
#define LED2_PIN   GPIO_PINS_3
#define LED3_PORT  GPIOG
#define LED3_PIN   GPIO_PINS_2

namespace xtp::gpio
{
    void init(void);
}

#endif
