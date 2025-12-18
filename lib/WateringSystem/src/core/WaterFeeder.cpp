#include "WaterFeeder.h"

WaterFeeder::WaterFeeder(bool valveOn, bool pumpOn, uint8_t mainWaterValvePin, uint8_t pumpPin, uint8_t tankValvePin)
    : valveOn(valveOn),
      pumpOn(pumpOn),
      mainWaterValvePin(mainWaterValvePin),
      pumpPin(pumpPin),
      tankValvePin(tankValvePin)
{
    pinMode(mainWaterValvePin, OUTPUT);
    pinMode(pumpPin, OUTPUT);
    pinMode(tankValvePin, OUTPUT);
    digitalWrite(mainWaterValvePin, !valveOn);
    digitalWrite(pumpPin, !pumpOn);
    digitalWrite(tankValvePin, !valveOn);
}

void WaterFeeder::stopMainWatering()
{
    digitalWrite(mainWaterValvePin, !valveOn);
}

void WaterFeeder::stopPump()
{
    digitalWrite(pumpPin, !pumpOn);
}

void WaterFeeder::startPump()
{
    digitalWrite(pumpPin, pumpOn);
}

bool WaterFeeder::isFeeding()
{
    return digitalRead(pumpPin) == pumpOn || digitalRead(mainWaterValvePin) == valveOn;
}