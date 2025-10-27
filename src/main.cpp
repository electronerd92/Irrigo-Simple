#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <IrrigoSystem.h>

IrrigoSystem irrigoSystem;

void setup()
{
}

void loop()
{
  irrigoSystem.update();
}