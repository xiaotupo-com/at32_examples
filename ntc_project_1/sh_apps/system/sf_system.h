#ifndef _SF_SYSTEM_H
#define _SF_SYSTEM_H

#include "at32f435_437.h"
#include "ntc.h"
#include "ec11.h"

enum buzzer_t { BUZZER_FLAG_OFF, BUZZER_FLAG_ON };
enum key_state_bit_t { KEY_COUNT_BIT = 12, KEY_LONG_DOWN_BIT = 13, KEY_INT_BIT = 14 };

/* app 消息队列类型枚举 */
enum app_msg_type_t {
	MSG_TYPE_TEMP_UPDATE, 		/* 温度更新消息 */
	MSG_TYPE_HL_UPDATE,			/* H/L值更新消息 */
	MSG_TYPE_ENCODER_ACTION, 	/* 编码器操作消息 */
};

struct app_msg_t {
	enum app_msg_type_t type;
	union {
		float temp_value; /* 温度 */
		struct {
			float l_value;
			float h_value;
		} hl_values;
		enum ec11_action_t ec11_action;
	} data;
};



// 系统参数结构体
// 1. 蜂鸣器开关标志位 buzzer_flag 0: 关闭蜂鸣器 1: 开启蜂鸣器
// key_state:
// bit[15] 未使用
// bit[14] 按键中断触发标志位，中断触发时置位该位
// bit[13] 长按标志位：1代表长按，0 清除长按标志位
// bit[12] 是否计数标志位：1 代表开始计数，0 代表停止计数
struct sf_system_t {
    enum buzzer_t buzzer_flag;
    uint16_t key_state;
    uint16_t long_down_count; // 长按计数
    confirm_state led2_flag;
	struct ntc_t *ntc1;
};

void sf_system_init();

extern struct sf_system_t sf_sys;

#endif
