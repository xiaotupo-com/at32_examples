#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
    void (*writeCommand)(uint8_t cmd);
    void (*writeData)(const uint8_t *data, uint32_t len);
    void (*reset)(void);
    uint16_t width;
    uint16_t height;
} st7789_c_config_t;

typedef void* st7789_handle_t;

st7789_handle_t st7789_create(const st7789_c_config_t* cfg);
void st7789_init(st7789_handle_t handle);
void st7789_fill_color(st7789_handle_t handle, uint16_t color);
void st7789_draw_pixel(st7789_handle_t handle, uint16_t x, uint16_t y, uint16_t color);

#ifdef __cplusplus
}
#endif
