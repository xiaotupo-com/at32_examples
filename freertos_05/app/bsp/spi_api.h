#ifndef __SPI_API_H
#define __SPI_API_H
#include "at32f435_437_wk_config.h"

void spi_write_cmd(uint8_t cmd);
void spi_write_data(const uint8_t *data, uint32_t len);
void lcd_reset(void);

#endif
