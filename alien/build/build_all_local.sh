function f_build_curr {
  echo "building for esp8266"
  mos build --local --clean --platform esp8266
  local r_esp8266=$?

  echo "building for esp32"
  mos build --local --clean --platform esp32
  local r_esp32=$?

  if [ $r_esp8266 -ne 0 ] || [ $r_esp32 -ne 0 ]
  then
    echo "build failed"
    return 1
  else
    return 0
  fi
}

function f_build_curr_example {
  # local build
  sed -i 's|- origin: https://github.com/bbilger/mgos-arduino-adafruit-epd|- origin: ../../../mgos-arduino-adafruit-epd|' mos.yml

  f_build_curr
  local r_build=$?

  # and back to what it was
  sed -i 's|- origin: ../../../mgos-arduino-adafruit-epd|- origin: https://github.com/bbilger/mgos-arduino-adafruit-epd|' mos.yml

  if [ $r_build -ne 0 ]
  then
    exit 1
  fi
}

echo "building..."
cd ../../
echo "mos version: "
mos version
echo "building lib"
f_build_curr
if [ $? -ne 0 ]
then
  echo "build failed"
  exit 1
fi

cd examples

cd hello_c
echo "building hello_c example"
f_build_curr_example

cd ../hello_cpp
echo "building hello_cpp example"
f_build_curr_example

cd ../hello_js
echo "building hello_js example"
f_build_curr_example
