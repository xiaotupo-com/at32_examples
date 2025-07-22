#include "led_wrapper.h"
#include "led.h"

extern "C" void led_run()
{
	xtp::led_run();
}