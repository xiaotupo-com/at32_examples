/* add user code begin Header */
/**
 ******************************************************************************
 * File Name          : freertos_app.c
 * Description        : Code for freertos applications
 */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "freertos_app.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
#include <stdbool.h>

#include "at32f435_437_wk_config.h"
#include "debug.h"
#include "lcd_write_pixel_data.h"

/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */

/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */

/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */

uint16_t data[110] = {
    0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009,
    0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F, 0x0010, 0x0011, 0x0012,
    0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x001B,
    0x001C, 0x001D, 0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0023, 0x0024,
    0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D,
    0x002E, 0x002F, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036,
    0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
    0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048,
    0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F, 0x0050, 0x0051,
    0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A,
    0x005B, 0x005C, 0x005D, 0x005E, 0x005F, 0x0060, 0x0061, 0x0062, 0x0063,
    0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C,
    0x006D, 0x006E};

uint16_t data1[10] = {0x0001,
                      0x0002,
                      0x0003,
                      0x0004,
                      0x0005,
                      0x0006,
                      0x0007,
                      0x0008,
                      0x0009,
                      0x006E};

/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */

/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */

/* add user code end 0 */

/* task handler */
TaskHandle_t my_task01_handle;

/* binary semaphore handler */
SemaphoreHandle_t lcd_dma_semaphore_handle;
SemaphoreHandle_t user_trigger_semaphore_handle;

/* Idle task control block and stack */
static StackType_t idle_task_stack[configMINIMAL_STACK_SIZE];
static StackType_t timer_task_stack[configTIMER_TASK_STACK_DEPTH];

static StaticTask_t idle_task_tcb;
static StaticTask_t timer_task_tcb;

/* External Idle and Timer task static memory allocation functions */
extern void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                          StackType_t **ppxIdleTaskStackBuffer,
                                          uint32_t *pulIdleTaskStackSize);
extern void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                           StackType_t **ppxTimerTaskStackBuffer,
                                           uint32_t *pulTimerTaskStackSize);

/*
  vApplicationGetIdleTaskMemory gets called when configSUPPORT_STATIC_ALLOCATION
  equals to 1 and is required for static memory allocation support.
*/
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &idle_task_tcb;
    *ppxIdleTaskStackBuffer = &idle_task_stack[0];
    *pulIdleTaskStackSize = (uint32_t)configMINIMAL_STACK_SIZE;
}
/*
  vApplicationGetTimerTaskMemory gets called when configSUPPORT_STATIC_ALLOCATION
  equals to 1 and is required for static memory allocation support.
*/
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize)
{
    *ppxTimerTaskTCBBuffer = &timer_task_tcb;
    *ppxTimerTaskStackBuffer = &timer_task_stack[0];
    *pulTimerTaskStackSize = (uint32_t)configTIMER_TASK_STACK_DEPTH;
}

/* add user code begin 1 */

/* add user code end 1 */

/**
 * @brief  initializes all task.
 * @param  none
 * @retval none
 */
void freertos_task_create(void)
{
    /* create my_task01 task */
    xTaskCreate(my_task01_func, "my_task01", 128, NULL, 0, &my_task01_handle);
}

/**
 * @brief  initializes all semaphore.
 * @param  none
 * @retval none
 */
void freertos_semaphore_create(void)
{
    /* Create the lcd_dma_semaphore */
    lcd_dma_semaphore_handle = xSemaphoreCreateBinary();

    /* Create the user_trigger_semaphore */
    user_trigger_semaphore_handle = xSemaphoreCreateBinary();
}

/**
 * @brief  freertos init and begin run.
 * @param  none
 * @retval none
 */
void wk_freertos_init(void)
{
    /* enter critical */
    taskENTER_CRITICAL();

    freertos_semaphore_create();
    freertos_task_create();

    /* exit critical */
    taskEXIT_CRITICAL();

    /* start scheduler */
    vTaskStartScheduler();
}

/**
 * @brief my_task01 function.
 * @param  none
 * @retval none
 */
void my_task01_func(void *pvParameters)
{
    /* add user code begin my_task01_func 0 */

    /* add user code end my_task01_func 0 */

    /* add user code begin my_task01_func 2 */

    /* add user code end my_task01_func 2 */

    /* Infinite loop */
    while (1)
    {
        /* add user code begin my_task01_func 1 */

        /* 等待用户触发发送 */
        if (xSemaphoreTake(user_trigger_semaphore_handle, portMAX_DELAY) ==
            pdTRUE)
        {
            /* 发送像素数据 */
            lcd_write_pixel_data(data, sizeof(data) / sizeof(data[0]));

            if (xSemaphoreTake(lcd_dma_semaphore_handle, pdMS_TO_TICKS(1000)) ==
                pdTRUE)
            {
                /* DMA 发送完成 */
                LOG("DMA 发送完成\n");
            }
            else
            {
                /* 超时未完成 */
                LOG("DMA 发送超时\n");
            }
        }

        /* add user code end my_task01_func 1 */
    }
}

/* add user code begin 2 */

/* add user code end 2 */
