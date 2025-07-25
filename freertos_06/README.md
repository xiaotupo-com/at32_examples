# 项目简介

硬件平台：**AT32F437ZGT7** + **AT32 Work Bench**(图形化配置工具) + **MDK5**

该项目涉及到的内容：

- FreeRTOS 相关
  - 二值信号量 （定义了两个二值信号量）
- DMA + SPI (使能 DMA 发送完成中断)
- 自定义 DMA 版本的 SPI 发送函数 `lcd_write_pixel_data()`
- 按键中断 （在中断中发送信号量给任务，让任务开始发送数据）

除了图形化生成的文件外，自定义的文件有3个：

- `debug.h`
- `lcd_write_pixel_data.h`
- `lcd_write_pixel_data.c`

一共有这几个地方有自己写的代码，其余都是图形化生成的：

- 中断文件 `at32f435_437_int.c` 中有自己的代码
- `freertos_app.c` 文件中

**AT32 Work Bench** 中要做的：

- 启用 FreeRTOS
  - 创建2个信号量 `lcd_dma_semaphore` 和 `user_trigger_semaphore`
  - 启用 USART1
  - `SYSTEM` 配置中的串口打印选择 `USART1`
  - 启动 `SPI1` (主机单线双向只发模式)
  - 开启 `DMA` 添加 `SPI1_TX` 请求
    - 模式选择普通模式（单次）
    - 外设地址递增设置为：外设地址递增关闭
    - 内存地址递增设置为：内存地址递增开启
    - 外设数据宽度设置为：半字（16位）
    - 内存数据宽度设置为：半字（16位）
  - 配置按键中断，并开启中断

目前实现的功能：

- 按键按一下发送一次数据（调用 `lcd_write_pixel_data()` 一次）

该项目大概就这样了，用于练习和保存代码，方便以后查阅。
