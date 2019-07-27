echo "building..."
cd ../../
echo "mos version: "
mos version
echo "building lib for esp8266"
mos build --local --clean --platform esp8266
echo "building lib for esp32"
mos build --local --clean --platform esp32
cd examples
cd hello_c
echo "building examples/hello_c for esp8266"
mos build --local --clean --platform esp8266
echo "building examples/hello_c for esp32"
mos build --local --clean --platform esp32
cd ../hello_cpp
echo "building examples/hello_cpp for esp8266"
mos build --local --clean --platform esp8266
echo "building examples/hello_cpp for esp32"
mos build --local --clean --platform esp32
cd ../hello_js
echo "building examples/hello_js for es8266"
mos build --local --clean --platform esp8266
echo "building examples/hello_js for esp32"
mos build --local --clean --platform esp32
