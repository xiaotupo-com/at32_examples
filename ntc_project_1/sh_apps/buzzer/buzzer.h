#ifndef __BUZZER_H
#define __BUZZER_H
#include "at32f435_437.h"

// 当执行 buzzer_run() 时,会先打开蜂鸣器，并且让 on_count++
// 当 on_count 等于指定值时关闭蜂鸣器
struct buzzer_t {
	uint8_t on_count;
	uint8_t stop_value;
	uint8_t run_flag;
};

void buzzer_run(void);
extern struct buzzer_t buzzer;

#endif // __BUZZER_H
