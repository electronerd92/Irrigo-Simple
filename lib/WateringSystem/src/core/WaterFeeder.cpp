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
}

void WaterFeeder::stop()
{
    digitalWrite(mainWaterValvePin, !valveOn);
    digitalWrite(pumpPin, !pumpOn);
}

void WaterFeeder::start(bool feedWithPump)
{
    if (feedWithPump)
    {
        digitalWrite(pumpPin, pumpOn);
        return;
    }

    digitalWrite(mainWaterValvePin, valveOn);
}

bool WaterFeeder::isFeeding()
{
    return digitalRead(pumpPin) == pumpOn || digitalRead(mainWaterValvePin) == valveOn;
}