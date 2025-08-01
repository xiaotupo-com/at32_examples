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
#include "lcd1602.h"
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
              128,
              NULL,
              0,
              &default_task_handle);
}

/**
  * @brief  initializes all semaphore.
  * @param  none
  * @retval none
  */
void freertos_semaphore_create(void)
{
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
	lcd1602_init();
	printf("初始化完成！\n");
	
  /* add user code end default_task_func 0 */

  /* add user code begin default_task_func 2 */
	float num = 0.01f;
	lcd_clear();
	  lcd_set_cursor(0,0);
	  lcd_print("FreeRTOS LCD1602");
	  
	  lcd_set_cursor(1,0);
	  lcd_print("Tick: ");
  /* add user code end default_task_func 2 */

  /* Infinite loop */
  while(1)
  {
  /* add user code begin default_task_func 1 */

      
	  char buf[8];
	  num += 0.23f;
	  sprintf(buf, "%.2f", num);
	  lcd_set_cursor(1, 6);
	  lcd_print(buf);
	  vTaskDelay(pdMS_TO_TICKS(1000));

  /* add user code end default_task_func 1 */
  }
}


/* add user code begin 2 */

/* add user code end 2 */

