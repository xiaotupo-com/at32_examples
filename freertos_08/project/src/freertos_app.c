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
#include "array_length.h"
#include "st7789.h"

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

/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */

/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */

/* add user code end 0 */

/* task handler */
TaskHandle_t lcd_send_task_handle;

/* binary semaphore handler */
SemaphoreHandle_t lcd_dma_semaphore_handle;

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
    /* create lcd_send_task task */
    xTaskCreate(lcd_send_task_func, "lcd_send_task", 128, NULL, 0,
                &lcd_send_task_handle);
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
 * @brief lcd_send_task function.
 * @param  none
 * @retval none
 */
void lcd_send_task_func(void *pvParameters)
{
    /* add user code begin lcd_send_task_func 0 */
    st7789.init(&st7789);
    uint16_t color[] = {
        0xFFFF, /* 白色 */
        0x0000, /* 黑色 */
        0xF800, /* 红色 */
        0x07E0, /* 绿色 */
        0x001F, /* 蓝色 */
        0XF81F, /* 品红色/紫红色 = BLUE + RED */
        0XFFE0, /* 黄色 = GREEN + RED */
        0X07FF, /* 青色 = GREEN + BLUE */
        0XBC40, /* 棕色 */
        0XFC07, /* 棕红色 */
        0X8430, /* 灰色 */
        0X01CF, /* 深蓝色 */
        0X7D7C, /* 浅蓝色 */
        0X5458, /* 灰蓝色 */
        0X841F, /* 浅绿色 */
        0XC618, /* 浅灰色(PANNEL),窗体背景色 */
        0XA651, /* 浅灰蓝色(中间层颜色) */
        0X2B12, /* 浅棕蓝色(选择条目的反色) */
    };
    uint8_t color_index = 0;
    st7789.set_window(0, 0, st7789.cfg.width - 1, st7789.cfg.height - 1);
    /* add user code end lcd_send_task_func 0 */

    /* add user code begin lcd_send_task_func 2 */

    /* add user code end lcd_send_task_func 2 */

    /* Infinite loop */
    while (1)
    {
        /* add user code begin lcd_send_task_func 1 */
        st7789.fill_color(color[color_index]);
        vTaskDelay(pdMS_TO_TICKS(3000)); /* 每隔 1 秒切换一次颜色 */
        color_index++;
        if (color_index >= ARRAY_LENGTH(color))
        {
            color_index = 0; /* 重置颜色索引 */
        }
        /* add user code end lcd_send_task_func 1 */
    }
}

/* add user code begin 2 */

/* add user code end 2 */
