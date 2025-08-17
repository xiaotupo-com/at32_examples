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
#include "ec11.h"
#include "key.h"
#include "lcd1602.h"
#include "led.h"
#include "ntc.h"
#include "sf_system.h"
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
TaskHandle_t default_task_handle;
TaskHandle_t ec11_task_handle;
TaskHandle_t key_task_handle;
TaskHandle_t get_temp_task_handle;

/* binary semaphore handler */
SemaphoreHandle_t xEC11SemaphoreBinary_handle;

/* mutex handler */
SemaphoreHandle_t lcdMutex_handle;

/* Idle task control block and stack */
static StackType_t idle_task_stack[configMINIMAL_STACK_SIZE];
static StackType_t timer_task_stack[configTIMER_TASK_STACK_DEPTH];

static StaticTask_t idle_task_tcb;
static StaticTask_t timer_task_tcb;

/* External Idle and Timer task static memory allocation functions */
extern void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer, StackType_t ** ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );
extern void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer, StackType_t ** ppxTimerTaskStackBuffer, uint32_t * pulTimerTaskStackSize );

/*
  vApplicationGetIdleTaskMemory gets called when configSUPPORT_STATIC_ALLOCATION
  equals to 1 and is required for static memory allocation support.
*/
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer, StackType_t ** ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &idle_task_tcb;
  *ppxIdleTaskStackBuffer = &idle_task_stack[0];
  *pulIdleTaskStackSize = (uint32_t)configMINIMAL_STACK_SIZE;
}
/*
  vApplicationGetTimerTaskMemory gets called when configSUPPORT_STATIC_ALLOCATION
  equals to 1 and is required for static memory allocation support.
*/
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer, StackType_t ** ppxTimerTaskStackBuffer, uint32_t * pulTimerTaskStackSize )
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
  /* create default_task task */
  xTaskCreate(default_task_func,
              "default_task",
              512,
              NULL,
              0,
              &default_task_handle);

  /* create ec11_task task */
  xTaskCreate(ec11_task_func,
              "ec11_task",
              512,
              NULL,
              1,
              &ec11_task_handle);

  /* create key_task task */
  xTaskCreate(key_task_func,
              "key_task",
              512,
              NULL,
              0,
              &key_task_handle);

  /* create get_temp_task task */
  xTaskCreate(get_temp_task_func,
              "get_temp_task",
              512,
              NULL,
              0,
              &get_temp_task_handle);
}

/**
  * @brief  initializes all semaphore.
  * @param  none
  * @retval none
  */
void freertos_semaphore_create(void)
{
  /* Create the xEC11SemaphoreBinary */
  xEC11SemaphoreBinary_handle = xSemaphoreCreateBinary();

  /* Create the lcdMutex */
  lcdMutex_handle = xSemaphoreCreateMutex();
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
  * @brief default_task function.
  * @param  none
  * @retval none
  */
void default_task_func(void *pvParameters)
{
  /* add user code begin default_task_func 0 */
    lcd.init();
    lcd.clear();
    lcd.set_cursor(0, 0);
    lcd.print("T:");
    lcd.set_cursor(0, 11);
    lcd.print("H");
    lcd.set_cursor(1, 11);
    lcd.print("L");
    lcd.set_cursor_mode(1, 0);

    /* add user code end default_task_func 0 */

  /* add user code begin default_task_func 2 */
    char h[4];
    char l[4];
    char value[4];
    /* add user code end default_task_func 2 */

  /* Infinite loop */
  while(1)
  {
  /* add user code begin default_task_func 1 */

        lcd.set_cursor(0, 3);
        sprintf(value, "%.1f", sf_sys.ntc1->value);
        lcd.print(value);
        lcd.set_cursor(0, 12);
        sprintf(h, "%.1f", sf_sys.ntc1->h_value);
        lcd.print(h);

        lcd.set_cursor(1, 12);
        sprintf(l, "%.1f", sf_sys.ntc1->l_value);
        lcd.print(l);
        lcd.set_cursor(0, 12);

        vTaskDelay(pdMS_TO_TICKS(100));  // Delay for 1 second

        /* add user code end default_task_func 1 */
  }
}


/**
  * @brief ec11_task function.
  * @param  none
  * @retval none
  */
void ec11_task_func(void *pvParameters)
{
  /* add user code begin ec11_task_func 0 */

    /* add user code end ec11_task_func 0 */

  /* add user code begin ec11_task_func 2 */

    /* add user code end ec11_task_func 2 */

  /* Infinite loop */
  while(1)
  {
  /* add user code begin ec11_task_func 1 */

        if (xSemaphoreTake(xEC11SemaphoreBinary_handle, (TickType_t)2) == pdTRUE)
        {
            switch (ec11.action)
            {
                case EC11_ACTION_CW:
                    led2.count_stop_value += led2.step_value;
                    sf_sys.ntc1->set_h(sf_sys.ntc1,
                                       sf_sys.ntc1->h_value + 0.14f);

                    break;
                case EC11_ACTION_CCW:
                    led2.count_stop_value -= led2.step_value;
                    sf_sys.ntc1->set_h(sf_sys.ntc1,
                                       sf_sys.ntc1->h_value - 0.14f);
                    break;
                default:
                    break;
            }
            printf("value: %d\r\n", led2.count_stop_value);
        }
        ec11.action = EC11_ACTION_NONE;

        /* add user code end ec11_task_func 1 */
  }
}


/**
  * @brief key_task function.
  * @param  none
  * @retval none
  */
void key_task_func(void *pvParameters)
{
  /* add user code begin key_task_func 0 */

    /* add user code end key_task_func 0 */

  /* add user code begin key_task_func 2 */

    /* add user code end key_task_func 2 */

  /* Infinite loop */
  while(1)
  {
  /* add user code begin key_task_func 1 */

        key_scanf(buttons);
        vTaskDelay(pdMS_TO_TICKS(10));

        /* add user code end key_task_func 1 */
  }
}


/**
  * @brief get_temp_task function.
  * @param  none
  * @retval none
  */
void get_temp_task_func(void *pvParameters)
{
  /* add user code begin get_temp_task_func 0 */

    /* add user code end get_temp_task_func 0 */

  /* add user code begin get_temp_task_func 2 */

    /* add user code end get_temp_task_func 2 */

  /* Infinite loop */
  while(1)
  {
  /* add user code begin get_temp_task_func 1 */
        // 普通组（软件）触发使能
        adc_ordinary_software_trigger_enable(ADC3, TRUE);
        // ADC_OCCE_FLAG ：普通通道转换结束标志
        while (adc_flag_get(ADC3, ADC_OCCE_FLAG) == RESET) {}

        sf_sys.ntc1->value =
            ntc1.get_temp(adc_ordinary_conversion_data_get(ADC3));

        vTaskDelay(pdMS_TO_TICKS(1000));

        /* add user code end get_temp_task_func 1 */
  }
}


/* add user code begin 2 */

/* add user code end 2 */

