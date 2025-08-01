# 项目介绍

硬件及软件：AT32F437 + AT32 WorkBench + MDK5

## 功能

- 按键长按短按
- 蜂鸣器启用状态改变（是否启用蜂鸣器）

## sf_system.h

```c
#ifndef _SF_SYSTEM_H
#define _SF_SYSTEM_H

#include "at32f435_437.h"

enum buzzer_t { BUZZER_FLAG_OFF, BUZZER_FLAG_ON };
enum key_state_bit_t { KEY_COUNT_BIT = 12, KEY_LONG_DOWN_BIT = 13, KEY_INT_BIT = 14 };

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
};

extern struct sf_system_t sf_sys;

#endif
```

## at32f435_437_int.c

```c
void SysTick_Handler(void)
{
  /* add user code begin SysTick_IRQ 0 */

  /* add user code end SysTick_IRQ 0 */

  wk_timebase_handler();

  /* add user code begin SysTick_IRQ 1 */
	/* 判断 key_state 的 按键计数位是否为 1 */
  if (GET_BIT(sf_sys.key_state, KEY_COUNT_BIT)) {
    sf_sys.long_down_count++;
  } else {
    sf_sys.long_down_count = 0;
  }
  
  /* add user code end SysTick_IRQ 1 */
}

void EXINT15_10_IRQHandler(void)
{
  /* add user code begin EXINT15_10_IRQ 0 */
	if (exint_interrupt_flag_get(EXINT_LINE_13) != RESET){
		sf_sys.key_state = SET_BIT(sf_sys.key_state, KEY_INT_BIT); // 置位中断标志位
		exint_flag_clear(EXINT_LINE_13);
	}
  /* add user code end EXINT15_10_IRQ 0 */
  /* add user code begin EXINT15_10_IRQ 1 */

  /* add user code end EXINT15_10_IRQ 1 */
}
```

## sf_utils.h

```c
#ifndef __UTILS_H
#define __UTILS_H

#define GetArrLen(array)    sizeof(array) / sizeof(array[0])    // 获取数组的长度
#define SET_BIT(num, n)     ((num) | (1 << (n)))				// 设置 num 中的某一位
#define CLEAR_BIT(num, n)   ((num) & ~(1<<(n)))					// 清除 num 中的某一位
#define SELF_LOGICAL_NOT(num) (num = (!(num)))					// 让自身等于自身的逻辑非
#define GET_BIT(num, bit_pos) ((num >> bit_pos) & 1)			// 获取 num 中的某一位

#endif
```

## main.c

```c
while (1) {
	/* add user code begin 3 */
	// 按键长按判断
	while (GET_BIT(sf_sys.key_state, KEY_INT_BIT) &&
		   (gpio_input_data_bit_read(SW1_GPIO_PORT, SW1_PIN) == SET)) {
		sf_sys.key_state = SET_BIT(sf_sys.key_state, KEY_COUNT_BIT); // 置位计数标志位

		// 判断按键按下超过 500ms
		if (sf_sys.long_down_count >= 1000) {
			printf("long_down_count>=500\n");
			sf_sys.key_state = CLEAR_BIT(sf_sys.key_state, KEY_COUNT_BIT);
			// 按键长按成功
			sf_sys.key_state = CLEAR_BIT(sf_sys.key_state, KEY_INT_BIT);
			SELF_LOGICAL_NOT(sf_sys.buzzer_flag); // 反转蜂鸣器的开关状态
			BUZZER_ON();
			wk_delay_ms(5);
			BUZZER_OFF();
			wk_delay_ms(5);
			// 判断蜂鸣器标志位，向串口打印蜂鸣器开启状态
			switch (sf_sys.buzzer_flag) {
			case BUZZER_FLAG_ON:
				printf("蜂鸣器已打开\n");
				break;
			case BUZZER_FLAG_OFF:
				printf("蜂鸣器已关闭\n");
				break;
			default:
				break;
			}
		}
	}
	sf_sys.key_state = CLEAR_BIT(sf_sys.key_state, KEY_COUNT_BIT); // 清除计数标志位

	// 按键单击操作判断
	if (GET_BIT(sf_sys.key_state, KEY_INT_BIT) &&
		(gpio_input_data_bit_read(SW1_GPIO_PORT, SW1_PIN) == RESET)) {
		// 判断蜂鸣器标志位
		if (sf_sys.buzzer_flag == BUZZER_FLAG_ON) { 
			BUZZER_ON();
			wk_delay_ms(10);
			BUZZER_OFF();
			wk_delay_ms(10);
		}

		SELF_LOGICAL_NOT(sf_sys.led2_flag); // 自身逻辑取反
		gpio_bits_write(LED2_GPIO_PORT, LED2_PIN, sf_sys.led2_flag);
		sf_sys.key_state = CLEAR_BIT(sf_sys.key_state, KEY_INT_BIT);
	}
	/* add user code end 3 */
}
```