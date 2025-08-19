#include "v_application_tick_hook.h"

#include "led.h"

#include "gpio_init.h"
#include "buzzer.h"

Led led2 {LED2_PORT, LED2_PIN};
Buzzer buzzer { BUZZER_PORT, BUZZER_PIN};

void vApplicationTickHook( void )
{
	led2.run();
	buzzer.run();	
}