#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "mgos_sys_config.h"

#ifdef __cplusplus
extern "C" {
#endif

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// << mgos lib specific
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef struct Adafruit_EPD Adafruit_EPD;

Adafruit_EPD *mgos_aepd_create(const struct mgos_config_aepd *cfg);

Adafruit_EPD *mgos_aepd_get_global(void);

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// << Adafruit_EDP
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

bool mgos_aepd_begin(Adafruit_EPD *epd, bool reset);

void mgos_aepd_draw_pixel(Adafruit_EPD *epd, int16_t x, int16_t y, uint16_t color);

void mgos_aepd_clear_buffer(Adafruit_EPD *epd);

void mgos_aepd_clear_display(Adafruit_EPD *epd);

void mgos_aepd_set_black_buffer(Adafruit_EPD *epd, int8_t index, bool inverted);

void mgos_aepd_set_color_buffer(Adafruit_EPD *epd, int8_t index, bool inverted);

void mgos_aepd_display(Adafruit_EPD *epd);

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// << Adafruit_GFX
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void mgos_aepd_start_write(Adafruit_EPD *epd);

void mgos_aepd_write_pixel(Adafruit_EPD *epd, int16_t x, int16_t y, uint16_t color);

void mgos_aepd_write_fill_rect(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void mgos_aepd_write_fast_v_line(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t h, uint16_t color);

void mgos_aepd_write_fast_h_line(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t w, uint16_t color);

void mgos_aepd_write_line(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

void mgos_aepd_end_write(Adafruit_EPD *epd);

void mgos_aepd_set_rotation(Adafruit_EPD *epd, uint8_t r);

void mgos_aepd_invert_display(Adafruit_EPD *epd, bool i);

void mgos_aepd_draw_fast_h_line(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t h, uint16_t color);

void mgos_aepd_draw_fast_v_line(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t h, uint16_t color);

void mgos_aepd_fill_rect(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void mgos_aepd_fill_screen(Adafruit_EPD *epd, uint16_t color);

void mgos_aepd_draw_line(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

void mgos_aepd_draw_rect(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void mgos_aepd_draw_circle(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t r, uint16_t color);

void mgos_aepd_draw_circle_helper(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);

void mgos_aepd_fill_circle(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t r, uint16_t color);

void mgos_aepd_fill_circle_helper(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

void mgos_aepd_draw_triangle(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

void mgos_aepd_fill_triangle(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

void mgos_aepd_draw_round_rect(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);

void mgos_aepd_fill_round_rect(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);

void mgos_aepd_draw_bitmap(Adafruit_EPD *epd, int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);

void mgos_aepd_draw_bitmap_bg(Adafruit_EPD *epd, int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);

void mgos_aepd_draw_x_bitmap(Adafruit_EPD *epd, int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);

void mgos_aepd_draw_grayscale_bitmap(Adafruit_EPD *epd, int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h);

void mgos_aepd_draw_grayscale_bitmap_masked(Adafruit_EPD *epd, int16_t x, int16_t y, uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h);

void mgos_aepd_draw_rgb_bitmap(Adafruit_EPD *epd, int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);

void mgos_aepd_draw_rgb_bitmap_masked(Adafruit_EPD *epd, int16_t x, int16_t y, uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h);

void mgos_aepd_draw_char(Adafruit_EPD *epd, int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);

void mgos_aepd_set_cursor(Adafruit_EPD *epd, int16_t x, int16_t y);

void mgos_aepd_set_text_color(Adafruit_EPD *epd, uint16_t c);

void mgos_aepd_set_text_color_bg(Adafruit_EPD *epd, uint16_t c, uint16_t bg);

void mgos_aepd_set_text_size(Adafruit_EPD *epd, uint8_t s);

void mgos_aepd_set_text_wrap(Adafruit_EPD *epd, bool w);

void mgos_aepd_cp437(Adafruit_EPD *epd, bool x);

// TODO
// void mgos_aepd_set_font(const GFXfont *f);

// note: changed width&height type from uint16_t to int16_t
void mgos_aepd_get_text_bounds(Adafruit_EPD *epd, char *string, int16_t x, int16_t y, int16_t *x1, int16_t *y1, int16_t *w, int16_t *h);

int16_t mgos_aepd_height(Adafruit_EPD *epd);

int16_t mgos_aepd_width(Adafruit_EPD *epd);

uint8_t mgos_aepd_get_rotation(Adafruit_EPD *epd);

int16_t mgos_aepd_get_cursor_x(Adafruit_EPD *epd);

int16_t mgos_aepd_get_cursor_y(Adafruit_EPD *epd);

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// << Print
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// TODO add all/more

size_t mgos_aepd_printf(Adafruit_EPD *epd, const char *format, ...);

size_t mgos_aepd_print(Adafruit_EPD *epd, const char s[]);

size_t mgos_aepd_println(Adafruit_EPD *epd, const char s[]);

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#ifdef __cplusplus
}
#endif
