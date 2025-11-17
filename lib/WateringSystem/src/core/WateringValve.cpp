#include "WateringValve.h"

WateringValve::WateringValve(uint8_t valvePin, bool out)
    : pin(valvePin),
      isOutdoor(out),
      mode(ValveMode::OFF)
{
    pinMode(pin, OUTPUT);
}

const bool WateringValve::getIsOutdoor()
{
    return isOutdoor;
}

int WateringValve::getState()
{
    return digitalRead(pin);
}

void WateringValve::setState(bool state)
{
    digitalWrite(pin, state);
}

bool WateringValve::canBeOpened()
{
    // TODO Implement logic
    //? send the current unix time as parameter
    return true;
}

bool WateringValve::canBeClosed()
{
    // TODO Implement logic
    return true;
}