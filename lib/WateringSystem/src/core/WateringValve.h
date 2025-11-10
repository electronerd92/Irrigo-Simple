#pragma once
#include <Arduino.h>
#include <interfaces/IWateringValve.h>

class WateringValve : public IWateringValve
{
private:
    const uint8_t pin;
    const bool isOutdoor;
    ValveMode mode;

public:
    WateringValve(uint8_t valvePin, bool out);
    void setValveMode(ValveMode newMode) override { mode = newMode; }
    int getState(bool state) override { return digitalRead(pin); }
    void setState(bool state) override { digitalWrite(pin, state); }
};