#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "core/MainSystem.h"
#include "hardware/Rtc.hpp"
#include "hardware/Lcd.hpp"
#include "hardware/RotaryEncoder.h"

Rtc rtc;
Lcd lcd;
RotaryEncoder rotaryEncoder;
MainSystem mainSystem(rtc, lcd, rotaryEncoder);

void setup()
{
}

void loop()
{
  mainSystem.update();
}