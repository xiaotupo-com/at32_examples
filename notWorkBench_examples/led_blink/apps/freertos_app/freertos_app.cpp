#include "freertos_app.h"

#include "FreeRTOS.h"
#include "gpio_init.h"
#include "led.h"
#include "task.h"

/* 创建一个 Led 实例 */
Led led3 = {LED3_PORT, LED3_PIN};

TaskHandle_t defaultTaskHandle;

/* 函数声明 */
extern "C" void defaultTask(void *params);

/**
 * @brief 用于创建各种任务
 * 
 * @return * void 
 */
void freertos_create_task()
{
    /* create default_task task */
    xTaskCreate(defaultTask, "default_task", 512, NULL, 0, &defaultTaskHandle);
}

/**
 * @brief 初始化工作，创建任务，创建信号量等工作
 * 
 */
void freertos_app_init(void)
{
    /* enter critical */
    taskENTER_CRITICAL();

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
    while (1)
    {
        led3.toggle();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}