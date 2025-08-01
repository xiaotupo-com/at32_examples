#include "sf_system.h"

struct sf_system_t sf_sys = {
    .buzzer_flag = BUZZER_FLAG_OFF, // 默认关闭蜂鸣器
    .key_state = 0x0000,            // 默认按键所有位清零
    .long_down_count = 0            //
};
