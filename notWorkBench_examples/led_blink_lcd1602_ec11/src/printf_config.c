#include "printf_config.h"

#include "at32f435_437.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include <stdarg.h>
#include <stdio.h>

/* support printf function, usemicrolib is unnecessary */
#if (__ARMCC_VERSION > 6000000)
  __asm (".global __use_no_semihosting\n\t");
  void _sys_exit(int x)
  {
    UNUSED(x);
  }
  /* __use_no_semihosting was requested, but _ttywrch was */
  void _ttywrch(int ch)
  {
    UNUSED(ch);
  }
  FILE __stdout;
#else
 #ifdef __CC_ARM
  #pragma import(__use_no_semihosting)
  struct __FILE
  {
    int handle;
  };
  FILE __stdout;
  void _sys_exit(int x)
  {
    UNUSED(x);
  }
  /* __use_no_semihosting was requested, but _ttywrch was */
  void _ttywrch(int ch)
  {
    UNUSED(ch);
  }
 #endif
#endif

#if defined (__GNUC__) && !defined (__clang__)
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/**
  * @brief  retargets the c library printf function to the usart.
  * @param  none
  * @retval none
  */
PUTCHAR_PROTOTYPE
{
#if !defined (__GNUC__) || defined (__clang__)
  UNUSED(f);
#endif
  while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
  usart_data_transmit(USART1, (uint16_t)ch);
  while(usart_flag_get(USART1, USART_TDC_FLAG) == RESET);
  return ch;
}

#if (defined (__GNUC__) && !defined (__clang__)) || (defined (__ICCARM__))
#if defined (__GNUC__) && !defined (__clang__)
int _write(int fd, char *pbuffer, int size)
#elif defined ( __ICCARM__ )
#pragma module_name = "?__write"
int __write(int fd, char *pbuffer, int size)
#endif
{
  UNUSED(fd);
  for(int i = 0; i < size; i ++)
  {
    while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
    usart_data_transmit(USART1, (uint16_t)(*pbuffer++));
    while(usart_flag_get(USART1, USART_TDC_FLAG) == RESET);
  }

  return size;
}
#endif

/* 定义全局互斥锁 */
SemaphoreHandle_t xPrintfMutex = NULL;

void v_printf_mutex_init(void)
{
	xPrintfMutex = xSemaphoreCreateMutex();
	configASSERT(xPrintfMutex != NULL); /* 确保互斥锁创建成功 */
}

int printf_safe(const char *format, ...)
{
	int ret = 0;
	va_list args;
	
	/* 检查互斥锁是否初始化 */
	if (xPrintfMutex == NULL)
	{
		return -1; /* 互斥锁未被初始化，返回错误 */
	}
	
	if(xSemaphoreTake(xPrintfMutex, 0) == pdTRUE)
	{
		/* 成功获取锁 */
		va_start(args, format);
		ret = vprintf(format, args);
		va_end(args);
		
		/* 释放互斥锁 */
		xSemaphoreGive(xPrintfMutex);
	} else {
		/* 获取锁超时 */
		ret = -2;
	}
	
	return ret;
}