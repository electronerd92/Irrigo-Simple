#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <IrrigoSystem.h>

IrrigoSystem *irrigoSystem;

void setup()
{
  irrigoSystem = new IrrigoSystem();
}

void loop()
{
  irrigoSystem->update();
}