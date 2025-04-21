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
#include "buzzer.h"
#include "ec11.h"
#include "key.h"
#include "led.h"
#include <stdio.h>

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
TaskHandle_t defaultTask_handle;
TaskHandle_t buttonTask_handle;
TaskHandle_t ec11Task_handle;

/* binary semaphore handler */
SemaphoreHandle_t xEC11SemaphoreBinary_handle;

/* Idle task control block and stack */
static StackType_t idle_task_stack[configMINIMAL_STACK_SIZE];

static StaticTask_t idle_task_tcb;

/* External Idle and Timer task static memory allocation functions */
extern void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/*
  vApplicationGetIdleTaskMemory gets called when configSUPPORT_STATIC_ALLOCATION
  equals to 1 and is required for static memory allocation support.
*/
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &idle_task_tcb;
    *ppxIdleTaskStackBuffer = &idle_task_stack[0];
    *pulIdleTaskStackSize = (uint32_t)configMINIMAL_STACK_SIZE;
}

void vApplicationTickHook(void) {
    /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */

    /* add user code begin vApplicationTickHook */

    if (led2.run_flag) {
        led_run(&led2, led2_toggle);
    }

    if (led3.run_flag) {
        led_run(&led3, led3_toggle);
    }

    if (buzzer.run_flag) {
        buzzer_run();
    }

    /* add user code end vApplicationTickHook */
}

/* add user code begin 1 */

/* add user code end 1 */

/**
  * @brief  initializes all task.
  * @param  none
  * @retval none
  */
void freertos_task_create(void) {
    /* create defaultTask task */
    xTaskCreate(default_task,
                "defaultTask",
                228,
                NULL,
                0,
                &defaultTask_handle);

    /* create buttonTask task */
    xTaskCreate(button_task,
                "buttonTask",
                228,
                NULL,
                0,
                &buttonTask_handle);

    /* create ec11Task task */
    xTaskCreate(ec11_task,
                "ec11Task",
                228,
                NULL,
                0,
                &ec11Task_handle);
}

/**
  * @brief  initializes all semaphore.
  * @param  none
  * @retval none
  */
void freertos_semaphore_create(void) {
    /* Create the xEC11SemaphoreBinary */
    xEC11SemaphoreBinary_handle = xSemaphoreCreateBinary();
}

/**
  * @brief  freertos init and begin run.
  * @param  none
  * @retval none
  */
void wk_freertos_init(void) {
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
  * @brief defaultTask function.
  * @param  none
  * @retval none
  */
void default_task(void *pvParameters) {
    /* add user code begin default_task 0 */
    /* add user code end default_task 0 */

    /* Infinite loop */
    while (1) {
        /* add user code begin default_task 1 */
        vTaskDelay(100);
        /* add user code end default_task 1 */
    }
}

/**
  * @brief buttonTask function.
  * @param  none
  * @retval none
  */
void button_task(void *pvParameters) {
    /* add user code begin button_task 0 */
    
    /* add user code end button_task 0 */

    /* Infinite loop */
    while (1) {
        /* add user code begin button_task 1 */
        key_scanf(buttons);
        vTaskDelay(pdMS_TO_TICKS(10));
        /* add user code end button_task 1 */
    }
}

/**
  * @brief ec11Task function.
  * @param  none
  * @retval none
  */
void ec11_task(void *pvParameters) {
    /* add user code begin ec11_task 0 */

    /* add user code end ec11_task 0 */

    /* Infinite loop */
    while (1) {
        /* add user code begin ec11_task 1 */
        if (xSemaphoreTake(xEC11SemaphoreBinary_handle, (TickType_t)2) == pdTRUE) {
            switch (ec11.dir_flag) {
            case ROTATION_CW:
                led2.count_stop_value += led2.step_value;

                break;
            case ROTATION_CCW:
                led2.count_stop_value -= led2.step_value;
                break;
            default:
                break;
            }
            printf("value: %d\r\n", led2.count_stop_value);
        }
        ec11.dir_flag = ROTATION_NONE;
        /* add user code end ec11_task 1 */
    }
}

/* add user code begin 2 */

/* add user code end 2 */
