#ifndef __PRINTF_CONFIG_H
#define __PRINTF_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
	
int printf_safe(const char *format, ...);
void v_printf_mutex_init(void);

#ifdef __cplusplus
}
#endif

#endif
