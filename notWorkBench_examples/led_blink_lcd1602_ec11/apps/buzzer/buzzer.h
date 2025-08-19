#ifndef __BUZZER_H
#define __BUZZER_H
#include "at32f435_437.h"

class Buzzer
{
public:
    Buzzer(gpio_type *gpio_x, uint16_t pins);
	void run(void);
	void setIsActive(bool _isActive);
	void setIsDisabled(bool _isDisabled);
	void toggleDisabled(void);
	void off(void);

private:
	uint8_t m_count;
	uint8_t m_stopValue;
	bool m_isActive;
	bool m_isDisabled;
	gpio_type *m_port;
	uint16_t m_pin;
};

#endif  // __BUZZER_H
