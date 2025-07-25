/**
 * @file debug.h
 * @author xtp (xiaotupo@163.com)
 * @brief 用于控制条件编译，是否打印调试输出（需要配置好 printf）
 * @version V0.1
 * @date 2025-07-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __DEBUG_H
#define __DEBUG_H

#define DEBUG 0 /* 1: 启用调试；0: 禁用调试 */

#if DEBUG
	#include <stdio.h>
	
	#define LOG(...) printf(__VA_ARGS__)
	#define LOG_INFO(s)	printf("[INFO] %s\n", s)
#else
	#define LOG(...)
	#define LOG_INFO(s)
#endif /* DEBUG */

#endif
