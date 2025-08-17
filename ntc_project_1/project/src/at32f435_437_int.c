/* add user code begin Header */
/**
  **************************************************************************
  * @file     at32f435_437_int.c
  * @brief    main interrupt service routines.
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

/* includes ------------------------------------------------------------------*/
#include "at32f435_437_int.h"
/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */
#include "at32f435_437_wk_config.h"
#include "freertos_app.h"
#include "ec11.h"
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

/* external variables ---------------------------------------------------------*/
/* add user code begin external variables */

/* add user code end external variables */

/**
  * @brief  this function handles nmi exception.
  * @param  none
  * @retval none
  */
void NMI_Handler(void)
{
  /* add user code begin NonMaskableInt_IRQ 0 */

  /* add user code end NonMaskableInt_IRQ 0 */

  /* add user code begin NonMaskableInt_IRQ 1 */

  /* add user code end NonMaskableInt_IRQ 1 */
}

/**
  * @brief  this function handles hard fault exception.
  * @param  none
  * @retval none
  */
void HardFault_Handler(void)
{
  /* add user code begin HardFault_IRQ 0 */

  /* add user code end HardFault_IRQ 0 */
  /* go to infinite loop when hard fault exception occurs */
  while (1)
  {
    /* add user code begin W1_HardFault_IRQ 0 */

    /* add user code end W1_HardFault_IRQ 0 */
  }
}

/**
  * @brief  this function handles memory manage exception.
  * @param  none
  * @retval none
  */
void MemManage_Handler(void)
{
  /* add user code begin MemoryManagement_IRQ 0 */

  /* add user code end MemoryManagement_IRQ 0 */
  /* go to infinite loop when memory manage exception occurs */
  while (1)
  {
    /* add user code begin W1_MemoryManagement_IRQ 0 */

    /* add user code end W1_MemoryManagement_IRQ 0 */
  }
}

/**
  * @brief  this function handles bus fault exception.
  * @param  none
  * @retval none
  */
void BusFault_Handler(void)
{
  /* add user code begin BusFault_IRQ 0 */

  /* add user code end BusFault_IRQ 0 */
  /* go to infinite loop when bus fault exception occurs */
  while (1)
  {
    /* add user code begin W1_BusFault_IRQ 0 */

    /* add user code end W1_BusFault_IRQ 0 */
  }
}

/**
  * @brief  this function handles usage fault exception.
  * @param  none
  * @retval none
  */
void UsageFault_Handler(void)
{
  /* add user code begin UsageFault_IRQ 0 */

  /* add user code end UsageFault_IRQ 0 */
  /* go to infinite loop when usage fault exception occurs */
  while (1)
  {
    /* add user code begin W1_UsageFault_IRQ 0 */

    /* add user code end W1_UsageFault_IRQ 0 */
  }
}


/**
  * @brief  this function handles debug monitor exception.
  * @param  none
  * @retval none
  */
void DebugMon_Handler(void)
{
  /* add user code begin DebugMonitor_IRQ 0 */

  /* add user code end DebugMonitor_IRQ 0 */
  /* add user code begin DebugMonitor_IRQ 1 */

  /* add user code end DebugMonitor_IRQ 1 */
}

extern void xPortSysTickHandler(void);

/**
  * @brief  this function handles systick handler.
  * @param  none
  * @retval none
  */
void SysTick_Handler(void)
{
  /* add user code begin SysTick_IRQ 0 */

  /* add user code end SysTick_IRQ 0 */


#if (INCLUDE_xTaskGetSchedulerState == 1 )
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
#endif /* INCLUDE_xTaskGetSchedulerState */
  xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  }
#endif /* INCLUDE_xTaskGetSchedulerState */

  /* add user code begin SysTick_IRQ 1 */

  /* add user code end SysTick_IRQ 1 */
}

/**
  * @brief  this function handles EXINT Line [9:5] handler.
  * @param  none
  * @retval none
  */
void EXINT9_5_IRQHandler(void)
{
  /* add user code begin EXINT9_5_IRQ 0 */
BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    flag_status a_value = gpio_input_data_bit_read(EC11_A_EXINT6_GPIO_PORT, EC11_A_EXINT6_PIN);
    flag_status b_value = gpio_input_data_bit_read(EC11_B_GPIO_PORT, EC11_B_PIN);

    if (exint_flag_get(EXINT_LINE_6) != RESET) {

        if (a_value == RESET && ec11.count == 0) /* 判断A相是下降沿并且 count=0 */
        {
            ec11.b_flag = 0;  /* 给B相标志位赋值0 */
            if (b_value) /* 这里要判断B相的状态，如果是高电平则把B相标志位赋值1 */
                ec11.b_flag = 1;
            ec11.count = 1; /* 中断计数变量赋值1 */
        }

        if (a_value == SET && ec11.count == 1) /* 判断A相是上升沿并且 count=1  0 to 1 */
        {
            if (b_value == RESET && ec11.b_flag == 1) /* 判断旋转方向：B相波形为：1 to 0 */
            {
                ec11.action = EC11_ACTION_CCW;
				xSemaphoreGiveFromISR(xEC11SemaphoreBinary_handle, &xHigherPriorityTaskWoken);
            }
            if (b_value && ec11.b_flag == 0) /* 判断旋转方向：B相波形为：0 to 1 */
            {
                ec11.action = EC11_ACTION_CW;
				xSemaphoreGiveFromISR(xEC11SemaphoreBinary_handle, &xHigherPriorityTaskWoken);
            }
            ec11.count = 0;
        }

		if(xHigherPriorityTaskWoken == pdTRUE) {
			
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
        exint_flag_clear(EXINT_LINE_6);
    }
  /* add user code end EXINT9_5_IRQ 0 */
  /* add user code begin EXINT9_5_IRQ 1 */

  /* add user code end EXINT9_5_IRQ 1 */
}

/* add user code begin 1 */

/* add user code end 1 */
