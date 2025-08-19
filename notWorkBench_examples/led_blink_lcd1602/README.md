# 介绍

该项目为 AT32 + MDK5(AC6) + FreeRTOS 的移植项目，已完成移植。

用到的工具是 `AT32_New_Clock_Configuration` AT32 官方的时钟配置可视化软件。

该项目适合作为一个 FreeRTOS AT32 的模板。

libraries 目录和 middlewares 目录被 git 忽略了，所以在克隆完项目后需要手动复制这两个目录到项目根目录。

## 新增功能

- 添加 printf() 打印功能，使用互斥锁版本的 printf_safe()。
- 添加 lcd1602 显示
