/*
 * MIT License
 *
 * Copyright (c) 2019 Bjoern Bilger
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdbool.h>
#include "mgos.h"
#include "mgos_aepd.h"
#include "mgos_config.h"

static struct Adafruit_EPD *s_global_epd;

bool mgos_arduino_adafruit_epd_init(void) {
  if (!mgos_sys_config_get_aepd_enable()) {
    LOG(LL_INFO, ("not enabled"));
    return true;
  }
  LOG(LL_INFO, ("starting init..."));

  s_global_epd = mgos_aepd_create(mgos_sys_config_get_aepd());

  const bool initialized = s_global_epd != NULL;

  if (initialized) {
    LOG(LL_INFO, ("init finished"));
  } else {
    LOG(LL_ERROR, ("init failed"));
  }

  return initialized || mgos_sys_config_get_aepd_debug();  // => no boot loop in debug mode
}

Adafruit_EPD *mgos_aepd_get_global(void) {
  return s_global_epd;
}
