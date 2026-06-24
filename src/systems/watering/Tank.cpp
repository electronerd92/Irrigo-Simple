#include "Tank.h"

Tank::Tank(uint8_t pin, bool hasWaterLevel)
    : levelPin(pin), hasWaterLevel(hasWaterLevel)
{
    pinMode(levelPin, INPUT);
}

bool Tank::hasWater() const
{
    return digitalRead(levelPin) == hasWaterLevel;
}