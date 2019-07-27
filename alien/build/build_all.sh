cd ../../
mos version
mos build --local --clean --platform esp8266
mos build --local --clean --platform esp32
cd examples
cd hello_c
mos build --local --clean --platform esp8266
mos build --local --clean --platform esp32
cd ../hello_cpp
mos build --local --clean --platform esp8266
mos build --local --clean --platform esp32
cd ../hello_js
mos build --local --clean --platform esp8266
mos build --local --clean --platform esp32
