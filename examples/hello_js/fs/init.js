load('api_arduino_adafruit_epd.js');

let epd = ArduinoAdafruitEpd.createGlobal();

// will be done automatically for the global EDP if not configured differently
// epd.begin(true)

epd.clearBuffer();
epd.setTextWrap(true);
epd.setTextColor(0);

let imgDim = 50;
let img = ffi('void *mgos_aepd_ex_get_logo(void)')();
epd.drawBitmap(0, 0, img, imgDim, imgDim, 0);

epd.setCursor(0, imgDim + 2);

epd.setTextSize(2);
epd.print("Hello World!");

let currX = epd.getCursorX();

epd.println("");
let currY = epd.getCursorY();

let gfxPrimDim = 20;
let gfxPrimOffset = 5;

epd.drawLine(0, currY, currX, currY, 0);
currX = 0;
currY = currY + gfxPrimOffset;

epd.drawRect(0, currY, gfxPrimDim, gfxPrimDim, 0);
currX = gfxPrimDim + gfxPrimOffset;

epd.fillRect(currX, currY, gfxPrimDim, gfxPrimDim, 0);
currX = currX + gfxPrimDim + gfxPrimOffset;

epd.drawCircle(currX + gfxPrimDim / 2, currY + gfxPrimDim / 2, gfxPrimDim / 2, 0);
currX = currX + gfxPrimDim + gfxPrimOffset;

epd.fillCircle(currX + gfxPrimDim / 2, currY + gfxPrimDim / 2, gfxPrimDim / 2, 0);
currX = currX + gfxPrimDim + gfxPrimOffset;

epd.drawTriangle(currX, currY + gfxPrimDim, currX + gfxPrimDim / 2, currY, currX + gfxPrimDim, currY + gfxPrimDim, 0);
currX = currX + gfxPrimDim + gfxPrimOffset;

epd.fillTriangle(currX, currY + gfxPrimDim, currX + gfxPrimDim / 2, currY, currX + gfxPrimDim, currY + gfxPrimDim, 0);
currX = currX + gfxPrimDim + gfxPrimOffset;

epd.drawRoundRect(currX, currY, gfxPrimDim, gfxPrimDim, 5, 0);
currX = currX + gfxPrimDim + gfxPrimOffset;

epd.fillRoundRect(currX, currY, gfxPrimDim, gfxPrimDim, 5, 0);
currX = currX + gfxPrimDim + gfxPrimOffset;

currX = 0;
currY = currY + gfxPrimDim + gfxPrimOffset;

let header = "Made with <3 in Berlin";
epd.setTextSize(1);
let b = epd.getTextBounds(header, 0, 0);
epd.setCursor(epd.width() - b.w, epd.height() - b.h);
epd.print(header);

epd.display();
