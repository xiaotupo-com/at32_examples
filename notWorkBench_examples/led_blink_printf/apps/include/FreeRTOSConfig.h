/*
    FreeRTOS V10.4.3 - Copyright (C) 2020 Real Time Engineers Ltd.
    All rights reserved
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
#include <stdint.h>

#include "at32f435_437.h"

#endif

#define configUSE_PREEMPTION 1 /* 1: 使用抢占式调度器，1: 使用合作式调度器 */
#define configUSE_TIME_SLICING 1 /* 时间片轮转调度，默认值为 1，可不定义该行 */
#define configSUPPORT_STATIC_ALLOCATION 0 /* 0: 禁用静态内存分配，1: 使能静态内存分配（需实现相关函数） */
#define configSUPPORT_DYNAMIC_ALLOCATION 1 /* 动态内存分配 */
#define configUSE_IDLE_HOOK 0 /* IDLE 空闲钩子 */
#define configUSE_TICK_HOOK 1 /* TICK 钩子 */
#define configCPU_CLOCK_HZ ((unsigned long)SystemCoreClock)
#define configTICK_RATE_HZ ((TickType_t)1000)
#define configMAX_PRIORITIES (16)
#define configMINIMAL_STACK_SIZE ((unsigned short)128)
#define configTOTAL_HEAP_SIZE ((size_t)(10240))
#define configMAX_TASK_NAME_LEN (16)
#define configUSE_16_BIT_TICKS 0

#define configUSE_MUTEXES 1 /* 配置是否启用互斥锁（Mutex） */
#define configUSE_RECURSIVE_MUTEXES 1 /* 配置是否启用递归互斥锁（Recursive Mutex） */
#define configQUEUE_REGISTRY_SIZE 8 /* 配置队列注册表（Queue Registry）大小，调试辅助配置 */
#define configUSE_COUNTING_SEMAPHORES 1 /* 配置是否启用计数信号量（Counting Semaphore） */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0 /* 配置是否启用端口优化的任务选择算法，一般为 0 即可 */
#define configIDLE_SHOULD_YIELD 1 /* 控制空闲任务（Idle Task）是否主动让出 CPU 给同优先级就绪任务 */

#define configUSE_TRACE_FACILITY 1 /* 用于启用跟踪调试功能 */

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 0 /* 是否启用协程 */
#define configMAX_CO_ROUTINE_PRIORITIES (2) /* 配置协程（Co-routines）最大优先级数量 */

/* Software timer definitions. */
#define configUSE_TIMERS 0 /* 是否启用软件定时器（Software Timers）*/
#define configTIMER_TASK_PRIORITY (2) /* 设定定时器服务任务的优先级 */
#define configTIMER_QUEUE_LENGTH 10 /* 设定定时器命令队列的长度 */
#define configTIMER_TASK_STACK_DEPTH 256 /* 设定定时器服务任务的堆栈大小（单位：字） */

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet 1
#define INCLUDE_uxTaskPriorityGet 1
#define INCLUDE_vTaskDelete 1
#define INCLUDE_vTaskCleanUpResources 0 /* 该函数用于在任务被删除时清理资源 */
#define INCLUDE_vTaskSuspend 1
#define INCLUDE_vTaskDelayUntil 1
#define INCLUDE_vTaskDelay 1
#define INCLUDE_xTaskGetSchedulerState 1 /* 该函数用于获取当前调度器的运行状态 */
#define INCLUDE_xTimerPendFunctionCall 1 /* xTimerPendFunctionCall() 和 xTimerPendFunctionCallFromISR() 函数包含 */
#define INCLUDE_xQueueGetMutexHolder 1 /* 用于查询当前持有互斥锁（Mutex）的任务句柄 */

/* uxTaskGetStackHighWaterMark() 用于查询任务堆栈的
 * “高水位线”（即任务运行过程中堆栈的最大使用量），是评估和优化任务堆栈大小的关键工具 */
#define INCLUDE_uxTaskGetStackHighWaterMark 1
#define INCLUDE_xTaskGetCurrentTaskHandle 1 /* xTaskGetCurrentTaskHandle() 用于获取正在运行的任务句柄 */
#define INCLUDE_eTaskGetState 1 /* 查询指定任务的当前运行状态 */

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
#define configPRIO_BITS __NVIC_PRIO_BITS
#else
#define configPRIO_BITS 4 /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 15

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT(x)           \
    if ((x) == 0)                 \
    {                             \
        taskDISABLE_INTERRUPTS(); \
        for (;;)                  \
            ;                     \
    }

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#ifdef __cplusplus
}
#endif

#endif /* FREERTOS_CONFIG_H */
