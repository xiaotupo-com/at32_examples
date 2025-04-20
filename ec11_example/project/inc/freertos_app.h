/*
 * @Author: 小土坡 xiaotupo@163.com
 * @Date: 2025-04-15 23:36:43
 * @LastEditors: 小土坡 xiaotupo@163.com
 * @LastEditTime: 2025-04-20 12:15:59
 * @FilePath: \MDK_V5d:\projects\at32_examples\ec11_example\project\inc\freertos_app.h
 * @Description: 
 * 
 * Copyright (c) 2025 by 小土坡, All Rights Reserved. 
 */
/* add user code begin Header */
/**
  ******************************************************************************
  * File Name          : freertos_app.h
  * Description        : Code for freertos applications
  */
/* add user code end Header */
  
#ifndef FREERTOS_APP_H
#define FREERTOS_APP_H

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"
#include "wk_system.h"

/* private includes -------------------------------------------------------------*/
/* add user code begin private includes */
#include "at32f435_437_wk_config.h"
/* add user code end private includes */

/* exported types -------------------------------------------------------------*/
/* add user code begin exported types */
#define NUM_BUTTONS 5
#define DEBOUNCE_DELAY 15 // ms

enum ButtonState_t { STATE_IDLE,
                     STATE_PRESS_DEBOUNCE,
                     STATE_PRESSED,
                     STATE_RELEASE_DEBOUNCE,
                     STATE_RELEASED };

struct Button_t {
    gpio_type *port;
    uint16_t pin;
    enum ButtonState_t state; // 状态机枚举
    flag_status button_state; // 获取按钮状态
    uint8_t debounce_count;   // 消抖次数
    uint8_t id;               // 按键标识符 id
};


/* add user code end exported types */

/* exported constants --------------------------------------------------------*/
/* add user code begin exported constants */

/* add user code end exported constants */

/* exported macro ------------------------------------------------------------*/
/* add user code begin exported macro */

/* add user code end exported macro */

/* task handler */
extern TaskHandle_t defaultTask_handle;
extern TaskHandle_t buttonTask_handle;
extern TaskHandle_t ec11Task_handle;
/* declaration for task function */
void default_task(void *pvParameters);
void button_task(void *pvParameters);
void ec11_task(void *pvParameters);

/* binary semaphore handler */
extern SemaphoreHandle_t xEC11SemaphoreBinary_handle;

/* add user code begin 0 */

/* add user code end 0 */

void freertos_task_create(void);
void freertos_semaphore_create(void);
void wk_freertos_init(void);

/* add user code begin 1 */

/* add user code end 1 */

#endif /* FREERTOS_APP_H */
