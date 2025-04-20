/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-14 20:01:55
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-14 22:32:43
 * @FilePath: \MDK_V5d:\projects\at32_examples\led_blink\sources\key.c
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#include "key.h"
#include "at32f435_437_wk_config.h"

// 按键扫描，需要放到 main() 函数中的 while(1) 主循环中
// 按键硬件电路上已经用硬件的方法进行了消抖，不必用软件消抖
void key_scanf(void)
{	
	
}
