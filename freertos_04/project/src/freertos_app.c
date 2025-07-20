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
#include "lcd.h"
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
    uint8_t led_state = 0;
    /* add user code end my_task01_func 0 */

    /* add user code begin my_task01_func 2 */
    lcd_init();
    vTaskDelay(pdMS_TO_TICKS(1000));

    ST7789_DrawPixel(30, 30, RED);
    ST7789_DrawPixel(30, 31, RED);
    ST7789_DrawPixel(30, 32, RED);
	vTaskDelay(pdMS_TO_TICKS(1000));
    LCD_BLK_ON();

    /* add user code end my_task01_func 2 */

    /* Infinite loop */
    while (1)
    {
        /* add user code begin my_task01_func 1 */

        printf("Hello,AT32!\n");
		
        lcd_clear(RED);
        vTaskDelay(pdMS_TO_TICKS(1000));
        lcd_clear(GREEN);
		vTaskDelay(pdMS_TO_TICKS(1000));
        lcd_clear(BLUE);
		vTaskDelay(pdMS_TO_TICKS(1000));
        lcd_clear(YELLOW);
		vTaskDelay(pdMS_TO_TICKS(1000));
        lcd_clear(PINK);
		vTaskDelay(pdMS_TO_TICKS(1000));
        lcd_clear(BROWN);
		vTaskDelay(pdMS_TO_TICKS(1000));
        lcd_clear(GRAY);
		vTaskDelay(pdMS_TO_TICKS(1000));
        lcd_clear(GBLUE);
		vTaskDelay(pdMS_TO_TICKS(1000));
        lcd_clear(BLACK);
		
        gpio_bits_write(LED3_GPIO_PORT, LED3_PIN, led_state = !led_state);
        vTaskDelay(pdMS_TO_TICKS(1000));
        /* add user code end my_task01_func 1 */
    }
}

/* add user code begin 2 */

/* add user code end 2 */
