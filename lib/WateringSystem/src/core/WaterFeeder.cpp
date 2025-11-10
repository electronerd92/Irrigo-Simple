#include "WaterFeeder.h"

WaterFeeder::WaterFeeder(uint8_t mainWaterValvePin, uint8_t pumpPin, uint8_t tankValvePin)
    : mainWaterValvePin(mainWaterValvePin),
      pumpPin(pumpPin),
      tankValvePin(tankValvePin)
{
    pinMode(mainWaterValvePin, OUTPUT);
    pinMode(pumpPin, OUTPUT);
    pinMode(tankValvePin, OUTPUT);
}