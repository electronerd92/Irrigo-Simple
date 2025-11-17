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
    const bool getIsOutdoor() override;
    void setValveMode(ValveMode newMode) override { mode = newMode; }
    int getState() override;
    void setState(bool state) override;

    bool canBeOpened() override;
    bool canBeClosed() override;
};