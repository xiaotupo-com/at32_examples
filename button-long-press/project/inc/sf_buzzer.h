#ifndef _SF_BUZZER_H
#define _SF_BUZZER_H

#include "at32f435_437.h"

#define BUZZER_ON()	gpio_bits_write(BUZZER_GPIO_PORT, BUZZER_PIN, TRUE);

#define BUZZER_OFF()	gpio_bits_write(BUZZER_GPIO_PORT, BUZZER_PIN, FALSE);

#endif
