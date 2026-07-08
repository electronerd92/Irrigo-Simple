#include "Tank.h"

Tank::Tank(uint8_t pin, bool hasWaterLevel)
    : lowLevelPin(pin), hasWaterLevel(hasWaterLevel)
{
    pinMode(lowLevelPin, INPUT_PULLUP);
}

bool Tank::hasWater() const
{
    return digitalRead(lowLevelPin) == hasWaterLevel;
}