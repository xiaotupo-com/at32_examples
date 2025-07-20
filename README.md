# 代码仓库说明

该仓库是我的 AT32 练习仓库，里面是我的一些测试项目。

## 项目列表

- freertos_04 : 基于 `AT32 Workbench` 生成工具 + `FreeRTOS` 的 `ST7789` 移植例子，实现了点亮全屏的功能
- led_blink : 用到或实现了一下功能，实现的功能偏多了，并不是像 led_blink 名字代表的意思一样只是 LED 闪烁，但是也不想改名了 
	- 按键 ：电路上有硬件消掉，所以这里没有用软件消抖
	- `LED` 驱动：实现了`LED` 闪烁功能，相比简单的 `LED` 闪烁要复杂些，具体看 `state_led.h` 和 `state_led.c` 文件
	- PWM 功能：实现了PWM 占空比和频率调整的功能，用到了几个文件：`set_pwm_frequency.c`、`set_pwm_duty_cycle.c`、`pwm_app.c`这里只列出了源文件
- ec11_example ：实现了 EC11 编码器的驱动，用到了 `AT32 Workbench` 生成工具 + `FreeRTOS`，该项目实现了以下功能
	- 蜂鸣器
	- 多个 FreeRTOS 任务
	- FreeRTOS 信号量
	- 外部中断，在中断中消掉让后发送信号量到 EC11 任务，处理旋转逻辑
	
	

	
	
	