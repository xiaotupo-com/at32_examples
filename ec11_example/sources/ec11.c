/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-16 00:40:59
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-20 12:14:44
 * @FilePath: \MDK_V5d:\projects\at32_examples\ec11_example\sources\ec11.c
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
#include "ec11.h"

struct ec11_t ec11 = {
    .count = 0,
    .b_flag = 0,
    .dir_flag = ROTATION_NONE
};


