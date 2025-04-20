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
#include "led.h"
#include "ec11.h"
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

struct Button_t buttons[NUM_BUTTONS] = {
    {SW1_GPIO_PORT, SW1_PIN, STATE_IDLE, RESET, 0, 0},
    {SW2_GPIO_PORT, SW2_PIN, STATE_IDLE, RESET, 0, 1},
    {SW3_GPIO_PORT, SW3_PIN, STATE_IDLE, RESET, 0, 2},
    {SW4_GPIO_PORT, SW4_PIN, STATE_IDLE, RESET, 0, 3},
    {EC11_SW_GPIO_PORT, EC11_SW_PIN, STATE_IDLE, RESET, 0, 4},
};

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
    const uint8_t DEBOUNCE_COUNT = 2;
    /* add user code end button_task 0 */

    /* Infinite loop */
    while (1) {
        /* add user code begin button_task 1 */

        // For 循环
        for (int i = 0; i < NUM_BUTTONS; i++) {
            struct Button_t *button = &buttons[i];
            // 读取按键状态
            button->button_state = gpio_input_data_bit_read(button->port, button->pin);

            // Switch
            switch (button->state) {
            case STATE_IDLE:
                if (button->button_state == RESET) {
                    button->state = STATE_PRESS_DEBOUNCE;
                    button->debounce_count = 0;
                }
                break;
            case STATE_PRESS_DEBOUNCE:
                if (button->button_state == RESET) {
                    button->debounce_count++;
                    if (button->debounce_count >= DEBOUNCE_COUNT) {
                        button->state = STATE_PRESSED;
                        // 按键按下处理程序
                    }
                } else {
                    button->state = STATE_IDLE;
                }
                break;
            case STATE_PRESSED:
                if (button->button_state == TRUE) {
                    button->state = STATE_RELEASE_DEBOUNCE;
                    button->debounce_count = 0;
                }
                break;
            case STATE_RELEASE_DEBOUNCE: {
                if (button->button_state == TRUE) {
                    button->debounce_count++;
                    if (button->debounce_count >= DEBOUNCE_COUNT) {
                        button->state = STATE_RELEASED;
                        // 按键松开处理程序
                        {
                            buzzer.run_flag = 0x01;
                            switch (button->id) {
                            case 0: // 按键 SW1
                                led2.run_flag = 0x01;
                                led2.count_stop_value += 10;
                                printf("SW1\n");
                                break;
                            case 1: // 按键 SW2
                                led2.run_flag = 0x01;
                                led2.count_stop_value -= 10;
                                printf("SW2\n");
                                break;
                            case 2: // 按键 SW3
                                led3.run_flag = 0x01;
                                led3.count_stop_value += 10;
                                printf("SW3\n");
                                break;
                            case 3: // 按键 SW4
                                led3.run_flag = 0x01;
                                led3.count_stop_value -= 10;
                                printf("SW4\n");
                                break;
                            case 4: // 按键 EC11_SW
								led2.step_value++;
                                led_stop(0);
                                led_stop(1);
                                printf("EC11_SW\n");
                                break;
                            default:
                                break;
                            }
                        }
                    }
                } else {
                    button->state = STATE_PRESSED;
                }
            } break;
            case STATE_RELEASED:
                if (button->button_state == FALSE) {
                    button->state = STATE_PRESS_DEBOUNCE;
                    button->debounce_count = 0;
                }
                break;
            }
        }

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
        if (xSemaphoreTake(xEC11SemaphoreBinary_handle, ( TickType_t ) 2) == pdTRUE) {
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
		//vTaskDelay(pdMS_TO_TICKS(10));
        /* add user code end ec11_task 1 */
    }
}

/* add user code begin 2 */

/* add user code end 2 */
