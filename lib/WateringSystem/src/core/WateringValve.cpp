#include "WateringValve.h"

WateringValve::WateringValve(uint8_t valvePin, bool out)
    : pin(valvePin),
      isOutdoor(out),
      mode(ValveMode::OFF)
{
    pinMode(pin, OUTPUT);
}