/********************************************************************************
 * @file sf_utils.h
 * @author xiaotupo (xiaotupo@163.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-01
 * 
 * @copyright Copyright (c) 2024
 * 
 ********************************************************************************/
#ifndef __UTILS_H
#define __UTILS_H

#define GetArrLen(array)    sizeof(array) / sizeof(array[0])    // 获取数组的长度
#define SET_BIT(num, n)     ((num) | (1 << (n)))				// 设置 num 中的某一位
#define CLEAR_BIT(num, n)   ((num) & ~(1<<(n)))					// 清除 num 中的某一位
#define SELF_LOGICAL_NOT(num) (num = (!(num)))					// 让自身等于自身的逻辑非
#define GET_BIT(num, bit_pos) ((num >> bit_pos) & 1)			// 获取 num 中的某一位

#endif