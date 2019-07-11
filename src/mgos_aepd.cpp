#include "mgos_aepd.h"

#include "Adafruit_EPD.h"
#include "mgos.h"
#include "mgos_config.h"

extern "C" {

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// << private
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

static bool mgos_aepd_check_init(Adafruit_EPD *epd) {
  if (epd != nullptr) {
    return true;
  }
  LOG(LL_ERROR, ("[check epd set]"));
  return false;
}

static int mgos_aepd_get_spi_cs_gpio_by_index(int index) {
  switch (index) {
    case -1:
      return -1;
    case 0:
      return mgos_sys_config_get_spi_cs0_gpio();
    case 1:
      return mgos_sys_config_get_spi_cs1_gpio();
    case 2:
      return mgos_sys_config_get_spi_cs2_gpio();
    default:
      LOG(LL_WARN, ("[check cs gpio index valid] expected: one of [0, 1, 2, -1] but was: %d", index));
      return -1;
  }
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ## public
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// << mgos lib specific
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Adafruit_EPD *mgos_aepd_create(const struct mgos_config_aepd *cfg) {
  if (cfg == nullptr) {
    LOG(LL_ERROR, ("[check config not null]"));
    return nullptr;
  }
  const int width = cfg->width;
  if (width <= 0) {
    LOG(LL_ERROR, ("[check aepd.width valid] expected: >0 but was: %d", width));
    return nullptr;
  }
  const int height = cfg->height;
  if (height <= 0) {
    LOG(LL_ERROR, ("[check aepd.height valid] expected: >0 but was: %d", height));
    return nullptr;
  }
  const int epd_busy_gpio = cfg->epd_busy_gpio;
  const int epd_reset_gpio = cfg->epd_reset_gpio;
  const int epd_dc_gpio = cfg->epd_dc_gpio;
  if (epd_dc_gpio < 0) {
    LOG(LL_ERROR, ("[check aepd.epd_busy_gpio valid] expected: >=0 but was: %d", epd_dc_gpio));
    return nullptr;
  }
  const int sram_spi_cs_gpio = mgos_aepd_get_spi_cs_gpio_by_index(mgos_sys_config_get_aepd_sram_spi_cs_index());
  if (sram_spi_cs_gpio < 0) {
    LOG(LL_INFO, ("SRAM disabled"));
  }
  const int epd_spi_cs_gpio = mgos_aepd_get_spi_cs_gpio_by_index(mgos_sys_config_get_aepd_epd_spi_cs_index());
  if (epd_spi_cs_gpio < 0) {
    LOG(LL_ERROR, ("[check aepd.epd_spi_cs_index->spi.csX_gpio valid] expected: >=0 but was %d", epd_spi_cs_gpio));
    return nullptr;
  }
  if (sram_spi_cs_gpio == epd_spi_cs_gpio) {
    LOG(LL_ERROR, ("[check aepd.epd_spi_cs_index != aepd.sram_spi_cs_index] but was: sram=%d, edp=%d", sram_spi_cs_gpio, epd_spi_cs_gpio));
    return nullptr;
  }
  const char *driver = cfg->driver;
  Adafruit_EPD *epd = nullptr;
  if (driver == nullptr) {
    LOG(LL_ERROR, ("[check aepd.driver not null]"));
    return nullptr;
  } else if (strcmp(driver, "IL0373") == 0) {
    epd = new Adafruit_IL0373(width, height, epd_dc_gpio, epd_reset_gpio, epd_spi_cs_gpio, sram_spi_cs_gpio, epd_busy_gpio);
  } else if (strcmp(driver, "IL0398") == 0) {
    epd = new Adafruit_IL0398(width, height, epd_dc_gpio, epd_reset_gpio, epd_spi_cs_gpio, sram_spi_cs_gpio, epd_busy_gpio);
  } else if (strcmp(driver, "IL91874") == 0) {
    epd = new Adafruit_IL91874(width, height, epd_dc_gpio, epd_reset_gpio, epd_spi_cs_gpio, sram_spi_cs_gpio, epd_busy_gpio);
  } else if (strcmp(driver, "SSD1608") == 0) {
    epd = new Adafruit_SSD1608(width, height, epd_dc_gpio, epd_reset_gpio, epd_spi_cs_gpio, sram_spi_cs_gpio, epd_busy_gpio);
  } else if (strcmp(driver, "SSD1675") == 0) {
    epd = new Adafruit_SSD1675(width, height, epd_dc_gpio, epd_reset_gpio, epd_spi_cs_gpio, sram_spi_cs_gpio, epd_busy_gpio);
  } else {
    LOG(LL_ERROR, ("[check aepd.driver valid] expected: one of [\"IL0373\", \"IL0398\", \"IL91874\", \"SSD1608\" or \"SSD1675\") but was %s", driver));
    return nullptr;
  }

  if (cfg->begin) {
    mgos_aepd_begin(epd, true);
  }
  return epd;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// << Adafruit_EDP
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

bool mgos_aepd_begin(Adafruit_EPD *epd, bool reset) {
  if (!mgos_aepd_check_init(epd)) {
    return false;
  }
  epd->begin(reset);
  return true;
}

void mgos_aepd_draw_pixel(Adafruit_EPD *epd, int16_t x, int16_t y, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawPixel(x, y, color);
}

void mgos_aepd_clear_buffer(Adafruit_EPD *epd) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->clearBuffer();
}

void mgos_aepd_clear_display(Adafruit_EPD *epd) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->clearDisplay();
}

void mgos_aepd_set_black_buffer(Adafruit_EPD *epd, int8_t index, bool inverted) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->setBlackBuffer(index, inverted);
}

void mgos_aepd_set_color_buffer(Adafruit_EPD *epd, int8_t index, bool inverted) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->setColorBuffer(index, inverted);
}

void mgos_aepd_display(Adafruit_EPD *epd) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->display();
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// << Adafruit_GFX
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void mgos_aepd_start_write(Adafruit_EPD *epd) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->startWrite();
}

void mgos_aepd_write_pixel(Adafruit_EPD *epd, int16_t x, int16_t y, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->writePixel(x, y, color);
}

void mgos_aepd_write_fill_rect(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->writeFillRect(x, y, w, h, color);
}

void mgos_aepd_write_fast_v_line(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t h, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->writeFastVLine(x, y, h, color);
}

void mgos_aepd_write_fast_h_line(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t w, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->writeFastHLine(x, y, w, color);
}

void mgos_aepd_write_line(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->writeLine(x0, y0, x1, y1, color);
}

void mgos_aepd_end_write(Adafruit_EPD *epd) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->endWrite();
}

void mgos_aepd_set_rotation(Adafruit_EPD *epd, uint8_t r) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->setRotation(r);
}

void mgos_aepd_invert_display(Adafruit_EPD *epd, bool i) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->invertDisplay(i);
}

void mgos_aepd_draw_fast_h_line(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t h, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawFastHLine(x, y, h, color);
}

void mgos_aepd_draw_fast_v_line(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t h, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawFastVLine(x, y, h, color);
}

void mgos_aepd_fill_rect(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->fillRect(x, y, w, h, color);
}

void mgos_aepd_fill_screen(Adafruit_EPD *epd, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->fillScreen(color);
}

void mgos_aepd_draw_line(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawLine(x0, y0, x1, y1, color);
}

void mgos_aepd_draw_rect(Adafruit_EPD *epd, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawRect(x, y, w, h, color);
}

void mgos_aepd_draw_circle(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawCircle(x0, y0, r, color);
}

void mgos_aepd_draw_circle_helper(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawCircleHelper(x0, y0, r, cornername, color);
}

void mgos_aepd_fill_circle(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->fillCircle(x0, y0, r, color);
}

void mgos_aepd_fill_circle_helper(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->fillCircleHelper(x0, y0, r, cornername, delta, color);
}

void mgos_aepd_draw_triangle(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

void mgos_aepd_fill_triangle(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

void mgos_aepd_draw_round_rect(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawRoundRect(x0, y0, w, h, radius, color);
}

void mgos_aepd_fill_round_rect(Adafruit_EPD *epd, int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->fillRoundRect(x0, y0, w, h, radius, color);
}

void mgos_aepd_draw_bitmap_a(Adafruit_EPD *epd, int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawBitmap(x, y, bitmap, w, h, color);
}

void mgos_aepd_draw_bitmap_a_bg(Adafruit_EPD *epd, int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color, uint16_t bg) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawBitmap(x, y, bitmap, w, h, color, bg);
}

void mgos_aepd_draw_bitmap_p(Adafruit_EPD *epd, int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawBitmap(x, y, bitmap, w, h, color);
}

void mgos_aepd_draw_bitmap_p_bg(Adafruit_EPD *epd, int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawBitmap(x, y, bitmap, w, h, color, bg);
}

void mgos_aepd_draw_x_bitmap(Adafruit_EPD *epd, int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawXBitmap(x, y, bitmap, w, h, color);
}

void mgos_aepd_draw_grayscale_bitmap_a(Adafruit_EPD *epd, int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawGrayscaleBitmap(x, y, bitmap, w, h);
}

void mgos_aepd_draw_grayscale_bitmap_p(Adafruit_EPD *epd, int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawGrayscaleBitmap(x, y, bitmap, w, h);
}

void mgos_aepd_draw_grayscale_bitmap_a_m(Adafruit_EPD *epd, int16_t x, int16_t y, const uint8_t bitmap[], const uint8_t mask[], int16_t w, int16_t h) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawGrayscaleBitmap(x, y, bitmap, mask, w, h);
}

void mgos_aepd_draw_grayscale_bitmap_p_m(Adafruit_EPD *epd, int16_t x, int16_t y, uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawGrayscaleBitmap(x, y, bitmap, mask, w, h);
}

void mgos_aepd_draw_rgb_bitmap_a(Adafruit_EPD *epd, int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawRGBBitmap(x, y, bitmap, w, h);
}

void mgos_aepd_draw_rgb_bitmap_p(Adafruit_EPD *epd, int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawRGBBitmap(x, y, bitmap, w, h);
}

void mgos_aepd_draw_rgb_bitmap_a_m(Adafruit_EPD *epd, int16_t x, int16_t y, const uint16_t bitmap[], const uint8_t mask[], int16_t w, int16_t h) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawRGBBitmap(x, y, bitmap, mask, w, h);
}

void mgos_aepd_draw_rgb_bitmap_p_m(Adafruit_EPD *epd, int16_t x, int16_t y, uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawRGBBitmap(x, y, bitmap, mask, w, h);
}

void mgos_aepd_draw_char(Adafruit_EPD *epd, int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->drawChar(x, y, c, color, bg, size);
}

void mgos_aepd_set_cursor(Adafruit_EPD *epd, int16_t x, int16_t y) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->setCursor(x, y);
}

void mgos_aepd_set_text_color(Adafruit_EPD *epd, uint16_t c) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->setTextColor(c);
}

void mgos_aepd_set_text_color_bg(Adafruit_EPD *epd, uint16_t c, uint16_t bg) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->setTextColor(c, bg);
}

void mgos_aepd_set_text_size(Adafruit_EPD *epd, uint8_t s) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->setTextSize(s);
}

void mgos_aepd_set_text_wrap(Adafruit_EPD *epd, bool w) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->setTextWrap(w);
}

void mgos_aepd_cp437(Adafruit_EPD *epd, bool x) {
  if (!mgos_aepd_check_init(epd)) {
    return;
  }
  epd->cp437(x);
}

// TODO
// void mgos_aepd_set_font(const GFXfont *f);

void mgos_aepd_get_text_bounds(Adafruit_EPD *epd, char *string, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) {
  if (!mgos_aepd_check_init(epd)) {
    *x1 = -1;
    *y1 = -1;
    *w = -1;
    *h = -1;
    return;
  }
  epd->getTextBounds(string, x, y, x1, y1, w, h);
}

int16_t mgos_aepd_height(Adafruit_EPD *epd) {
  if (!mgos_aepd_check_init(epd)) {
    return -1;
  }
  return epd->height();
}

int16_t mgos_aepd_width(Adafruit_EPD *epd) {
  if (!mgos_aepd_check_init(epd)) {
    return -1;
  }
  return epd->width();
}

uint8_t mgos_aepd_get_rotation(Adafruit_EPD *epd) {
  if (!mgos_aepd_check_init(epd)) {
    return -1;
  }
  return epd->getRotation();
}

int16_t mgos_aepd_get_cursor_x(Adafruit_EPD *epd) {
  if (!mgos_aepd_check_init(epd)) {
    return -1;
  }
  return epd->getCursorX();
}

int16_t mgos_aepd_get_cursor_y(Adafruit_EPD *epd) {
  if (!mgos_aepd_check_init(epd)) {
    return -1;
  }
  return epd->getCursorY();
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// << Print
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// TODO add all/more... write?

size_t mgos_aepd_printf(Adafruit_EPD *epd, const char *format, ...) {
  if (!mgos_aepd_check_init(epd)) {
    return -1;
  }
  char loc_buf[64];
  char *temp = loc_buf;
  va_list arg;
  va_list copy;
  va_start(arg, format);
  va_copy(copy, arg);
  size_t len = vsnprintf(NULL, 0, format, arg);
  va_end(copy);
  if (len >= sizeof(loc_buf)) {
    temp = new char[len + 1];
    if (temp == NULL) {
      return 0;
    }
  }
  len = vsnprintf(temp, len + 1, format, arg);

  mgos_aepd_print(epd, temp);
  va_end(arg);
  if (len > 64) {
    delete[] temp;
  }
  return len;
}

size_t mgos_aepd_print(Adafruit_EPD *epd, const char s[]) {
  if (!mgos_aepd_check_init(epd)) {
    return -1;
  }
  return epd->print(s);
}

size_t mgos_aepd_println(Adafruit_EPD *epd, const char s[]) {
  if (!mgos_aepd_check_init(epd)) {
    return -1;
  }
  return epd->println(s);
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}
