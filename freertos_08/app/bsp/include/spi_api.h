/**
 * @file spi_api.h
 * @author xtp (xiaotupo@163.com)
 * @brief 
 * @version V0.1
 * @date 2025-07-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __SPI_API_H
#define __SPI_API_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "at32f435_437_wk_config.h"

void spi_write_cmd(uint8_t cmd);
void spi_write_data(const uint8_t *data, uint32_t len);
void lcd_reset(void);
void lcd_set_to_non_dma_mode(void);
void lcd_set_to_dma_mode(void);

#ifdef __cplusplus
}
#endif

#endif
