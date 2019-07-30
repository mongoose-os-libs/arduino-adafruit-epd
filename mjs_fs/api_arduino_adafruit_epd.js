
let ArduinoAdafruitEpd = {

  createGlobal: function() {
    let obj = Object.create(ArduinoAdafruitEpd._proto);
    obj.epd = ArduinoAdafruitEpd._getGlobalEpd();
    return obj;
  },

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  // << FFI
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  // << mgos lib specific
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  _createInt16Pair: ffi('void *mgos_aepd_mjs_create_int16_pair(int, int)'),
  _freeInt16Pair: ffi('void mgos_aepd_mjs_free_int16_pair(void *)'),
  _getInt16PairDescr: ffi('void *mgos_aepd_get_int16_pair_descr(void)'),

  _getGlobalEpd: ffi('void *mgos_aepd_get_global(void)'),

  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  // << Adafruit_EDP
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  _begin: ffi('bool mgos_aepd_begin(void *, bool)'),
  _drawPixel: ffi('void mgos_aepd_draw_pixel(void *, int, int, int)'),
  _clearBuffer: ffi('void mgos_aepd_clear_buffer(void *)'),
  _clearDisplay: ffi('void mgos_aepd_clear_display(void *)'),
  _setBlackBuffer: ffi('void mgos_aepd_set_black_buffer(void *, int, bool)'),
  _setColorBuffer: ffi('void mgos_aepd_set_color_buffer(void *, int, bool)'),
  _display: ffi('void mgos_aepd_display(void *)'),

  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  // << Adafruit_GFX
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  _startWrite: ffi('void mgos_aepd_start_write(void *)'),
  _writePixel: ffi('void mgos_aepd_write_pixel(void *, int, int, int)'),
  _writeFillRect: ffi('void mgos_aepd_write_fill_rect(void *, int, int, int, int, int)'),
  _writeFastVLine: ffi('void mgos_aepd_write_fast_v_line(void *, int, int, int, int)'),
  _writeFastHLine: ffi('void mgos_aepd_write_fast_h_line(void *, int, int, int, int)'),
  _writeLine: ffi('void mgos_aepd_write_line(void *, int, int, int, int, int)'),
  _endWrite: ffi('void mgos_aepd_end_write(void *)'),
  _setRotation: ffi('void mgos_aepd_set_rotation(void *, int)'),
  _invertDisplay: ffi('void mgos_aepd_invert_display(void *, bool)'),
  _drawFastHLine: ffi('void mgos_aepd_draw_fast_h_line(void *, int, int, int, int)'),
  _drawFastVLine: ffi('void mgos_aepd_draw_fast_v_line(void *, int, int, int, int)'),
  _fillRect: ffi('void mgos_aepd_fill_rect(void *, int, int, int, int, int)'),
  _fillScreen: ffi('void mgos_aepd_fill_screen(void *, int)'),
  _drawLine: ffi('void mgos_aepd_draw_line(void *, int, int, int, int, int)'),
  _drawRect: ffi('void mgos_aepd_draw_rect(void *, int, int, int, int, int)'),
  _drawCircle: ffi('void mgos_aepd_draw_circle(void *, int, int, int, int)'),
  _drawCircleHelper: ffi('void mgos_aepd_draw_circle_helper(void *, int, int, int, int, int)'),
  _fillCircle: ffi('void mgos_aepd_fill_circle(void *, int, int, int, int)'),
  _fillCircleHelper: ffi('void mgos_aepd_fill_circle_helper_mjs(void *, void *, int, int, int, int)'),
  _drawTriangle: ffi('void mgos_aepd_draw_triangle_mjs(void *, void *, void *, void *, int);'),
  _fillTriangle: ffi('void mgos_aepd_fill_triangle_mjs(void *, void *, void *, void *, int)'),
  _drawRoundRect: ffi('void mgos_aepd_draw_round_rect_mjs(void *, void *, void *, int, int)'),
  _fillRoundRect: ffi('void mgos_aepd_fill_round_rect_mjs(void *, void *, void *, int, int)'),
  _drawBitmap: ffi('void mgos_aepd_draw_bitmap_mjs(void *, void *, void *, void *, int)'),
  _drawBitmapBg: ffi('void mgos_aepd_draw_bitmap_bg_mjs(void *, void*, void *, void *, int, int)'),
  _drawXBitmap: ffi('void mgos_aepd_draw_x_bitmap_mjs(void *, void *, void *, void *, int);'),
  _drawGrayscaleBitmap: ffi('void mgos_aepd_draw_grayscale_bitmap_mjs(void *, void *, void *, void *)'),
  _drawGrayscaleBitmapMasked: ffi('void mgos_aepd_draw_grayscale_bitmap_masked_mjs(void *, void *, void *, void *, void *)'),
  _drawRgbBitmap: ffi('void mgos_aepd_draw_rgb_bitmap_mjs(void *, void *, void *, void *)'),
  _drawRgbBitmapMasked: ffi('void mgos_aepd_draw_rgb_bitmap_masked_mjs(void *, void *, void *, void *, void *)'),
  _drawChar: ffi('void mgos_aepd_draw_char_mjs(void *, void *, int, int, int, int)'),
  _setCursor: ffi('void mgos_aepd_set_cursor(void *, int, int)'),
  _setTextColor: ffi('void mgos_aepd_set_text_color(void *, int)'),
  _setTextColorBg: ffi('void mgos_aepd_set_text_color_bg(void *, int, int)'),
  _setTextSize: ffi('void mgos_aepd_set_text_size(void *, int)'),
  _setTextWrap: ffi('void mgos_aepd_set_text_wrap(void *, bool)'),
  _cp437: ffi('void mgos_aepd_cp437(void *, bool)'),
  _getTextBounds: ffi('void mgos_aepd_get_text_bounds_mjs(void *, char *, void *, void *, void *)'),
  _height: ffi('int mgos_aepd_height(void *)'),
  _width: ffi('int mgos_aepd_width(void *)'),
  _getRotation: ffi('int mgos_aepd_get_rotation(void *)'),
  _getCursorX: ffi('int mgos_aepd_get_cursor_x(void *)'),
  _getCursorY: ffi('int mgos_aepd_get_cursor_y(void *)'),

  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  // << Print
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  // not possible with mJS, AFAIK
  // printf: ffi('int mgos_aepd_printf(void *epd, char *format, ...)'),

  _print: ffi('int mgos_aepd_print(void *, char *)'),
  _println: ffi('int mgos_aepd_println(void *, char *)'),

  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  // >> FFI
  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  // << proto
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  _proto: {
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    // << mgos lib specific
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    // << Adafruit_EDP
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    begin: function(epd, reset) {
      return ArduinoAdafruitEpd._begin(this.epd, reset);
    },
    drawPixel: function(x, y, color) {
      return ArduinoAdafruitEpd._drawPixel(this.epd, x, y, color);
    },
    clearBuffer: function() {
      return ArduinoAdafruitEpd._clearBuffer(this.epd);
    },
    clearDisplay: function() {
      return ArduinoAdafruitEpd._clearDisplay(this.epd);
    },
    setBlackBuffer: function(index, inverted) {
      return ArduinoAdafruitEpd._setBlackBuffer(this.epd, index, inverted);
    },
    setColorBuffer: function(index, inverted) {
      return ArduinoAdafruitEpd._setColorBuffer(this.epd, index, inverted);
    },
    display: function() {
      return ArduinoAdafruitEpd._display(this.epd);
    },

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    // << Adafruit_GFX
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    startWrite: function() {
      return ArduinoAdafruitEpd._startWrite(this.epd);
    },
    writePixel: function(x, y, color) {
      return ArduinoAdafruitEpd._writePixel(this.epd, x, y, color);
    },
    writeFillRect: function(x, y, w, h, color) {
      return ArduinoAdafruitEpd._writeFillRect(this.epd, x, y, w, h, color);
    },
    writeFastVLine: function(x, y, h, color) {
      return ArduinoAdafruitEpd._writeFastVLine(this.epd, x, y, h, color);
    },
    writeFastHLine: function(x, y, w, color) {
      return ArduinoAdafruitEpd._writeFastHLine(this.epd, x, y, w, color);
    },
    writeLine: function(x0, y0, x1, y1, color) {
      return ArduinoAdafruitEpd._writeLine(this.epd, x0, y0, x1, y1, color);
    },
    endWrite: function() {
      return ArduinoAdafruitEpd._endWrite(this.epd);
    },
    setRotation: function(r) {
      return ArduinoAdafruitEpd._setRotation(this.epd, r);
    },
    invertDisplay: function(i) {
      return ArduinoAdafruitEpd._invertDisplay(this.epd, i);
    },
    drawFastHLine: function(x, y, h, color) {
      return ArduinoAdafruitEpd._drawFastHLine(this.epd, x, y, h, color);
    },
    drawFastVLine: function(x, y, h, color) {
      return ArduinoAdafruitEpd._drawFastVLine(this.epd, x, y, h, color);
    },
    fillRect: function(x, y, w, h, color) {
      return ArduinoAdafruitEpd._fillRect(this.epd, x, y, w, h, color);
    },
    fillScreen: function(color) {
      return ArduinoAdafruitEpd._fillScreen(this.epd, color);
    },
    drawLine: function(x0, y0, x1, y1, color) {
      return ArduinoAdafruitEpd._drawLine(this.epd, x0, y0, x1, y1, color);
    },
    drawRect: function(x, y, w, h, color) {
      return ArduinoAdafruitEpd._drawRect(this.epd, x, y, w, h, color);
    },
    drawCircle: function(x0, y0, r, color) {
      return ArduinoAdafruitEpd._drawCircle(this.epd, x0, y0, r, color);
    },
    drawCircleHelper: function(x0, y0, r, cornername, color) {
      return ArduinoAdafruitEpd._drawCircle(this.epd, x0, y0, r, cornername, color);
    },
    fillCircle: function(x0, y0, r, color) {
      return ArduinoAdafruitEpd._fillCircle(this.epd, x0, y0, r, color);
    },
    fillCircleHelper: function(coordinates, r, cornername, delta, color) {
      return ArduinoAdafruitEpd._fillCircleHelper(this.epd, coordinates, r, cornername, delta, color);
    },
    drawTriangle: function(x0, y0, x1, y1, x2, y2, color) {
      let c0 = ArduinoAdafruitEpd._createInt16Pair(x0, y0);
      let c1 = ArduinoAdafruitEpd._createInt16Pair(x1, y1);
      let c2 = ArduinoAdafruitEpd._createInt16Pair(x2, y2);
      ArduinoAdafruitEpd._drawTriangle(this.epd, c0, c1, c2, color);
      ArduinoAdafruitEpd._freeInt16Pair(c0);
      ArduinoAdafruitEpd._freeInt16Pair(c1);
      ArduinoAdafruitEpd._freeInt16Pair(c2);
    },
    fillTriangle: function(x0, y0, x1, y1, x2, y2, color) {
      let c0 = ArduinoAdafruitEpd._createInt16Pair(x0, y0);
      let c1 = ArduinoAdafruitEpd._createInt16Pair(x1, y1);
      let c2 = ArduinoAdafruitEpd._createInt16Pair(x2, y2);
      ArduinoAdafruitEpd._fillTriangle(this.epd, c0, c1, c2, color);
      ArduinoAdafruitEpd._freeInt16Pair(c0);
      ArduinoAdafruitEpd._freeInt16Pair(c1);
      ArduinoAdafruitEpd._freeInt16Pair(c2);
    },
    drawRoundRect: function(x0, y0, w, h, radius, color) {
      let c0 = ArduinoAdafruitEpd._createInt16Pair(x0, y0);
      let d = ArduinoAdafruitEpd._createInt16Pair(w, h);
      ArduinoAdafruitEpd._drawRoundRect(this.epd, c0, d, radius, color);
      ArduinoAdafruitEpd._freeInt16Pair(c0);
      ArduinoAdafruitEpd._freeInt16Pair(d);
    },
    fillRoundRect: function(x0, y0, w, h, radius, color) {
      let c0 = ArduinoAdafruitEpd._createInt16Pair(x0, y0);
      let d = ArduinoAdafruitEpd._createInt16Pair(w, h);
      ArduinoAdafruitEpd._fillRoundRect(this.epd, c0, d, radius, color);
      ArduinoAdafruitEpd._freeInt16Pair(c0);
      ArduinoAdafruitEpd._freeInt16Pair(d);
    },
    drawBitmap: function(x, y, bitmap, w, h, color) {
      let c = ArduinoAdafruitEpd._createInt16Pair(x, y);
      let d = ArduinoAdafruitEpd._createInt16Pair(w, h);
      ArduinoAdafruitEpd._drawBitmap(this.epd, c, bitmap, d, color);
      ArduinoAdafruitEpd._freeInt16Pair(c);
      ArduinoAdafruitEpd._freeInt16Pair(d);
    },
    drawBitmapBg: function(x, y, bitmap, w, h, color, bg) {
      let c = ArduinoAdafruitEpd._createInt16Pair(x, y);
      let d = ArduinoAdafruitEpd._createInt16Pair(w, h);
      ArduinoAdafruitEpd._drawBitmapBg(this.epd, c, bitmap, d, color, bg);
      ArduinoAdafruitEpd._freeInt16Pair(c);
      ArduinoAdafruitEpd._freeInt16Pair(d);
    },
    drawXBitmap: function(x, y, bitmap, w, h, color) {
      let c = ArduinoAdafruitEpd._createInt16Pair(x, y);
      let d = ArduinoAdafruitEpd._createInt16Pair(w, h);
      ArduinoAdafruitEpd._drawXBitmap(this.epd, c, bitmap, d, color);
      ArduinoAdafruitEpd._freeInt16Pair(c);
      ArduinoAdafruitEpd._freeInt16Pair(d);
    },
    drawGrayscaleBitmap: function(x, y, bitmap, w, h) {
      let c = ArduinoAdafruitEpd._createInt16Pair(x, y);
      let d = ArduinoAdafruitEpd._createInt16Pair(w, h);
      ArduinoAdafruitEpd._drawGrayscaleBitmap(this.epd, c, bitmap, d);
      ArduinoAdafruitEpd._freeInt16Pair(c);
      ArduinoAdafruitEpd._freeInt16Pair(d);
    },
    drawGrayscaleBitmapMasked: function(x, y, bitmap, mask, w, h) {
      let c = ArduinoAdafruitEpd._createInt16Pair(x, y);
      let d = ArduinoAdafruitEpd._createInt16Pair(w, h);
      ArduinoAdafruitEpd._drawGrayscaleBitmapMasked(this.epd, c, bitmap, mask, d);
      ArduinoAdafruitEpd._freeInt16Pair(c);
      ArduinoAdafruitEpd._freeInt16Pair(d);
    },
    drawRgbBitmap: function(x, y, bitmap, w, h) {
      let c = ArduinoAdafruitEpd._createInt16Pair(x, y);
      let d = ArduinoAdafruitEpd._createInt16Pair(w, h);
      ArduinoAdafruitEpd._drawRgbBitmap(this.epd, c, bitmap, d);
      ArduinoAdafruitEpd._freeInt16Pair(c);
      ArduinoAdafruitEpd._freeInt16Pair(d);
    },
    drawRgbBitmapMasked: function(x, y, bitmap, mask, w, h) {
      let c = ArduinoAdafruitEpd._createInt16Pair(x, y);
      let d = ArduinoAdafruitEpd._createInt16Pair(w, h);
      ArduinoAdafruitEpd._drawRgbBitmapMasked(this.epd, c, bitmap, mask, d);
      ArduinoAdafruitEpd._freeInt16Pair(c);
      ArduinoAdafruitEpd._freeInt16Pair(d);
    },
    drawChar: function(coordinates, c, color, bg, size) {
      return ArduinoAdafruitEpd._drawChar(this.epd, coordinates, c, color, bg, size);
    },
    setCursor: function(x, y) {
      return ArduinoAdafruitEpd._setCursor(this.epd, x, y);
    },
    setTextColor: function(c) {
      return ArduinoAdafruitEpd._setTextColor(this.epd, c);
    },
    setTextColorBg: function(c, bg) {
      return ArduinoAdafruitEpd._setTextColor(this.epd, c, bg);
    },
    setTextSize: function(s) {
      return ArduinoAdafruitEpd._setTextSize(this.epd, s);
    },
    setTextWrap: function(w) {
      return ArduinoAdafruitEpd._setTextWrap(this.epd, w);
    },
    cp437: function(x) {
      return ArduinoAdafruitEpd._cp437(this.epd, x);
    },
    getTextBounds: function(str, x, y) {
      let cInP = ArduinoAdafruitEpd._createInt16Pair(x, y);
      let cOutP = ArduinoAdafruitEpd._createInt16Pair(-1, -1);
      let dOutP = ArduinoAdafruitEpd._createInt16Pair(-1, -1);

      ArduinoAdafruitEpd._getTextBounds(this.epd, str, cInP, cOutP, dOutP);

      let descr = ArduinoAdafruitEpd._getInt16PairDescr();
      let cOut = s2o(cOutP, descr);
      let dOut = s2o(dOutP, descr);

      let rtr = { "x": cOut.first, "y": cOut.second, "w": dOut.first, "h": dOut.second };

      ArduinoAdafruitEpd._freeInt16Pair(cInP);
      ArduinoAdafruitEpd._freeInt16Pair(cOutP);
      ArduinoAdafruitEpd._freeInt16Pair(dOutP);

      return rtr;
    },
    height: function() {
      return ArduinoAdafruitEpd._height(this.epd);
    },
    width: function() {
      return ArduinoAdafruitEpd._width(this.epd);
    },
    getRotation: function() {
      return ArduinoAdafruitEpd._getRotation(this.epd);
    },
    getCursorX: function() {
      return ArduinoAdafruitEpd._getCursorX(this.epd);
    },
    getCursorY: function() {
      return ArduinoAdafruitEpd._getCursorY(this.epd);
    },

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    // << Print
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    print: function(s) {
      return ArduinoAdafruitEpd._print(this.epd, s);
    },
    println: function(s) {
      return ArduinoAdafruitEpd._println(this.epd, s);
    }

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  }

  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  // >> proto
  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}
