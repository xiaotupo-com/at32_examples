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

#include "freertos_app.h"
#include "debug.h"
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
  * @brief  this function handles EXINT Line [15:10] handler.
  * @param  none
  * @retval none
  */
void EXINT15_10_IRQHandler(void)
{
  /* add user code begin EXINT15_10_IRQ 0 */
	if(exint_flag_get(EXINT_LINE_13))
	{
		exint_flag_clear(EXINT_LINE_13);
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(user_trigger_semaphore_handle, &xHigherPriorityTaskWoken);

        portYIELD_FROM_ISR(xHigherPriorityTaskWoken); // 如果需要，触发上下文切换
	}
  /* add user code end EXINT15_10_IRQ 0 */
  /* add user code begin EXINT15_10_IRQ 1 */

  /* add user code end EXINT15_10_IRQ 1 */
}

/**
  * @brief  this function handles DMA1 Channel 1 handler.
  * @param  none
  * @retval none
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* add user code begin DMA1_Channel1_IRQ 0 */
    if (dma_interrupt_flag_get(DMA1_FDT1_FLAG)) /* 发送完成 */
    {
        /* 清除 DMA 传输完成标志 */
        dma_flag_clear(DMA1_FDT1_FLAG);

        /* 关闭 SPI 的 DMA 使能 */
        dma_channel_enable(DMA1_CHANNEL1, FALSE); /* 关闭 DMA 使能 */
        spi_i2s_dma_transmitter_enable(SPI1, FALSE);

        /* 在发送完成处理中，额外检测并清除其他可能的标志 */
        if (dma_interrupt_flag_get(DMA1_HDT1_FLAG))
        {
            dma_flag_clear(DMA1_HDT1_FLAG);
            LOG("意外触发半传输标志\n");  // 用于调试异常
        }

        if (dma_interrupt_flag_get(DMA1_DTERR1_FLAG))
        {
            dma_flag_clear(DMA1_DTERR1_FLAG);
            LOG("检测到传输错误！\n");  // 用于错误排查
        }

		/* 下面3行是信号量发送代码 */
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(lcd_dma_semaphore_handle, &xHigherPriorityTaskWoken);

        portYIELD_FROM_ISR(xHigherPriorityTaskWoken); // 如果需要，触发上下文切换
    }

    /* add user code end DMA1_Channel1_IRQ 0 */
  /* add user code begin DMA1_Channel1_IRQ 1 */

    /* add user code end DMA1_Channel1_IRQ 1 */
}

/* add user code begin 1 */

/* add user code end 1 */
