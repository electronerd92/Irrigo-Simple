#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "MainSystem.h"

MainSystem *mainSystem;

void setup()
{
  mainSystem = new MainSystem();
}

void loop()
{
  mainSystem->update();
}