#include <stdbool.h>
#include "mgos.h"
#include "mgos_aepd.h"
#include "mgos_config.h"

static struct Adafruit_EPD *s_global_epd;

// TODO rename to mgos_arduino_adafruit_epd_init once it's in mongoose-os-libs as "arduino_adafruit_edp"
bool mgos_mgos_arduino_adafruit_epd_init(void) {
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
