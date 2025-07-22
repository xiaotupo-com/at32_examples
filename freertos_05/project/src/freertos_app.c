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
#include "at32f435_437_wk_config.h"
#include "lcd_blk.h"
#include "led_wrapper.h"
#include "spi_api.h"
#include "st7789_c_bridge.h"
#include "lcd_demo.h"
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
st7789_c_config_t cfg = {.writeCommand = spi_write_cmd,
                             .writeData = spi_write_data,
                             .reset = lcd_reset,
                             .width = 320,
                             .height = 240};

st7789_handle_t lcd = NULL;
/* add user code end 0 */

/* task handler */
TaskHandle_t my_task01_handle;

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

void vApplicationTickHook(void)
{
    /* This function will be called by each tick interrupt if
     configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
     added here, but the tick hook is called from an interrupt context, so
     code must not attempt to block, and only the interrupt safe FreeRTOS API
     functions can be used (those that end in FromISR()). */

    /* add user code begin vApplicationTickHook */

    /* add user code end vApplicationTickHook */
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
 * @brief  freertos init and begin run.
 * @param  none
 * @retval none
 */
void wk_freertos_init(void)
{
    /* enter critical */
    taskENTER_CRITICAL();

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
	lcd = st7789_create(&cfg);
    st7789_init(lcd);

    lcd_blk_on(); /* 开启背光 */

    /* add user code end my_task01_func 0 */

    /* add user code begin my_task01_func 2 */

    /* add user code end my_task01_func 2 */

    /* Infinite loop */
    while (1)
    {
        /* add user code begin my_task01_func 1 */
        led_run();
        lcd_fill_demo();

        /* add user code end my_task01_func 1 */
    }
}

/* add user code begin 2 */

/* add user code end 2 */
