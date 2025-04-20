/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-16 00:40:49
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-20 12:15:40
 * @FilePath: \MDK_V5d:\projects\at32_examples\ec11_example\sources\ec11.h
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#ifndef __EC11_H
#define __EC11_H

#include "at32f435_437.h"

// 定义旋转方向枚举类型
enum RotationDir_t {
    ROTATION_NONE,
    ROTATION_CW,  // 顺时针的英文是 clockwise
    ROTATION_CCW, // 逆时针的英文是 counter - clockwise
};

struct ec11_t {
    uint8_t count;    /* 中断触发计数变量 */
    uint8_t b_flag;   /* B相标志变量*/
    enum RotationDir_t dir_flag; /* 方向标志 0: 顺时针 1: 逆时针 2: 未动状态 */
};

extern struct ec11_t ec11;
#endif // __EC11_H
