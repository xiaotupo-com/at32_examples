#include "freertos_app.h"

#include "FreeRTOS.h"
#include "gpio_init.h"
#include "led.h"
#include "task.h"
#include "printf_config.h"
#include "lcd1602.h"
#include "buzzer.h"
#include "key.h"
#include "ntc.h"

#include <stdio.h>


/* 创建一个 Led 实例 */
Led led3 {LED3_PORT, LED3_PIN};
extern Buzzer buzzer;

Lcd1602 lcd;
xtp::Ntc ntc {58.5f, 24.4f};


extern Led led2;

/* 任务句柄声明 */
TaskHandle_t defaultTaskHandle;
TaskHandle_t printTaskHandle;
TaskHandle_t lcd1602ShowTaskHandle;
TaskHandle_t keyTaskHandle;
TaskHandle_t ntcTaskHandle;

/* 函数声明 */
extern "C" void defaultTask(void *params);
extern "C" void printTask(void *params);
extern "C" void lcd1602ShowTask(void *params);
extern "C" void keyTask(void* params);
extern "C" void ntcTask(void* params);

// 打印单个任务的栈使用情况
void print_task_stack(TaskHandle_t task)
{
    UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(task);
	printf_safe("(%s)Task min free stack: %u words (%u bytes)\n",
		pcTaskGetName(task),
       (unsigned)uxHighWaterMark,
       (unsigned)(uxHighWaterMark * sizeof(StackType_t)));
}

/**
 * @brief 用于创建各种任务
 * 
 * @return * void 
 */
void freertos_create_task()
{
    /* create default_task task */
	BaseType_t result;
    result = xTaskCreate(defaultTask, "default_task", 128, NULL, 0, &defaultTaskHandle);
	if (result == pdPASS) {
		printf_safe("default_task 任务创建成功\n");
	} else {
        printf_safe("default_task 任务创建失败\n");
    }
	result = xTaskCreate(printTask, "print_task", 128, NULL, 0, &printTaskHandle);
    if (result == pdPASS) {
		printf_safe("print_task 任务创建成功\n");
	} else {
        printf_safe("print_task 任务创建失败\n");
    }
    
    result = xTaskCreate(lcd1602ShowTask, "lcdShowTask", 128, NULL, 0, &lcd1602ShowTaskHandle);
    if (result == pdPASS) {
		printf_safe("lcd1602ShowTask 任务创建成功\n");
	} else {
        printf_safe("lcd1602ShowTask 任务创建失败\n");
    }
	
	result = xTaskCreate(keyTask, "keyTask", 128, NULL, 0, &keyTaskHandle);
    if (result == pdPASS) {
		printf_safe("keyTask 任务创建成功\n");
	} else {
        printf_safe("keyTask 任务创建失败\n");
    }

    result = xTaskCreate(ntcTask, "ntcTask", 128, NULL, 0, &ntcTaskHandle);
    if (result == pdPASS) {
		printf_safe("ntcTask 任务创建成功\n");
	} else {
        printf_safe("ntcTask 任务创建失败\n");
    }
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
	print_task_stack(defaultTaskHandle);
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
	vTaskDelay(pdMS_TO_TICKS(10));
	print_task_stack(printTaskHandle);
    while (1)
    {
		printf_safe("led2 CountValue: %d\n", led2.getCountValue());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

extern "C" void lcd1602ShowTask(void *params)
{
	/* 创建一个 lcd1602 实例 */
	
    lcd.init();
    lcd.clear();
    lcd.setCursorPos(0,0);
    lcd.print("T:");
	lcd.setCursorPos(1,0);
	lcd.print("L:");
    lcd.setCursorMode(false, false);
	//print_task_stack(lcd1602ShowTaskHandle);
    float temp = 0.12f;
	float light = 1.12f;
	
    char L[5];
    while(1)
    {
		lcd.setCursorMode(false, false);
		// printf_safe("lcd1602ShowTask...\n");
        temp += 1.26f;
        lcd.setCursorPos(0, 3);
        sprintf(L, "%.2f", temp);
		lcd.print(L);
		light += 0.51f;
		lcd.setCursorPos(1, 3);
		sprintf(L, "%.2f", light);
		lcd.print(L);
		lcd.setCursorPos(1, 15);
		lcd.setCursorMode(true, false);
		vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

extern "C" void keyTask(void* params)
{
    while(1) {
		key_scanf(buttons);
		vTaskDelay(pdMS_TO_TICKS(10));
    }
}

extern "C" void ntcTask(void* params)
{
    char show[4];
    while(1) {
		 // 普通组（软件）触发使能
        adc_ordinary_software_trigger_enable(ADC3, TRUE);
        // ADC_OCCE_FLAG ：普通通道转换结束标志
        while (adc_flag_get(ADC3, ADC_OCCE_FLAG) == RESET) {}
		ntc.setCurrentTemp(ntc.get_temp(adc_ordinary_conversion_data_get(ADC3)));
        lcd.setCursorMode(false, false);
        lcd.setCursorPos(0, 12);
        sprintf(show, "%.1f", ntc.getCurrentTemp());
        lcd.print(show);
        lcd.setCursorPos(1, 15);
		lcd.setCursorMode(true, false);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}