#include "Pump.h"

Pump::Pump(uint8_t pin, bool activeLevel)
    : pin(pin), activeLevel(activeLevel)
{
    pinMode(pin, OUTPUT);
    stop();
}

void Pump::start()
{
    digitalWrite(pin, activeLevel);
}

void Pump::stop()
{
    digitalWrite(pin, !activeLevel);
}

bool Pump::isRunning() const
{
    return digitalRead(pin) == activeLevel;
}