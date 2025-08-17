#include "us_delay.h"

/**
 * @brief us 延时函数,使用 DWT (Data Watchpoint and Trace) 计数器
 * * 该函数使用 DWT 的 CYCCNT 计数器来实现微秒级延时。
 * * 不要用该函数实现 ms 延时, 因为会降低系统性能。
 * * @note 该函数需要在系统启动时使能 DWT 计数器。
 * 
 * @param us 
 */
void delay_us(uint32_t us)
{
	/* 仅在首次调用时初始化DWT（判断计数器是否未使能）*/
    if (!(DWT->CTRL & DWT_CTRL_CYCCNTENA_Msk)) {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;  // 使能调试跟踪
        DWT->CYCCNT = 0;                                 // 清零计数器
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;             // 使能CYCCNT
    }
	
	uint32_t start = DWT->CYCCNT;
	uint32_t ticks = (SystemCoreClock / 1000000) * us;
	while((DWT->CYCCNT - start) < ticks);
}