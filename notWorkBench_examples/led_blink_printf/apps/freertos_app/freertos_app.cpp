#include "freertos_app.h"

#include "FreeRTOS.h"
#include "gpio_init.h"
#include "led.h"
#include "task.h"
#include "printf_config.h"


/* 创建一个 Led 实例 */
Led led3 = {LED3_PORT, LED3_PIN};

extern Led led2;

TaskHandle_t defaultTaskHandle;
TaskHandle_t printTaskHandle;

/* 函数声明 */
extern "C" void defaultTask(void *params);
extern "C" void printTask(void *params);

/**
 * @brief 用于创建各种任务
 * 
 * @return * void 
 */
void freertos_create_task()
{
    /* create default_task task */
    xTaskCreate(defaultTask, "default_task", 1024, NULL, 0, &defaultTaskHandle);
	xTaskCreate(printTask, "print_task", 1024, NULL, 0, &printTaskHandle);
}

/**
 * @brief 初始化工作，创建任务，创建信号量等工作
 * 
 */
void freertos_app_init(void)
{
    /* enter critical */
    taskENTER_CRITICAL();
	v_printf_mutex_init(); /* 初始化 printf 互斥锁 */
    freertos_create_task();

    /* exit critical */
    taskEXIT_CRITICAL();

    /* start scheduler */
    vTaskStartScheduler();
}


/**
 * @brief 默认任务
 * 
 */
extern "C" void defaultTask(void *params)
{
	uint32_t count = 0;
    while (1)
    {
        led3.toggle();
		printf_safe("count: %d\n", count++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief print任务
 * 
 */
extern "C" void printTask(void *params)
{
    while (1)
    {
		printf_safe("led2 CountValue: %d\n", led2.getCountValue());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}