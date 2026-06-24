#include "Valve.h"

Valve::Valve(uint8_t pin, bool activeLevel, bool isOutdoor)
    : pin(pin), activeLevel(activeLevel), outdoor(isOutdoor)
{
    pinMode(pin, OUTPUT);
    close();
}

void Valve::open()
{
    digitalWrite(pin, activeLevel);
}

void Valve::close()
{
    digitalWrite(pin, !activeLevel);
}

bool Valve::isOpen() const
{
    return digitalRead(pin) == activeLevel;
}