#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "core/MainSystem.h"
#include "hardware/Rtc.hpp"
#include "hardware/Lcd.hpp"
#include "hardware/RotaryEncoder.h"
#include "hardware/ArduinoEEPROMReader.h"
#include "hardware/ArduinoEEPROMWriter.h"

Rtc rtc;
Lcd lcd;
RotaryEncoder rotaryEncoder;
ArduinoEEPROMReader eepromReader;
ArduinoEEPROMWriter eepromWriter;
MainSystem mainSystem(rtc, lcd, rotaryEncoder, eepromWriter, eepromReader);

void setup()
{
  rtc.begin();
  lcd.begin();
  mainSystem.begin();
}

void loop()
{
  mainSystem.update();
}