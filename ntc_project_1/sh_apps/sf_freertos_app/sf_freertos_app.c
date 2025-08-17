#include "sf_freertos_app.h"

#include "freertos_app.h"
#include "sf_system.h"

QueueHandle_t xSysQueue; /* 创建一个队列句柄 */

void sf_freertos_init(void)
{
    xSysQueue = xQueueCreate(10, sizeof(struct app_msg_t));

    /* enter critical */
    taskENTER_CRITICAL();
	if (xSysQueue != NULL) {
		/* 消息队列创建成功 */
		
	}
    /* exit critical */
    taskEXIT_CRITICAL();
}