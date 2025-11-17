#pragma once
#include <Arduino.h>
#include "interfaces/IWaterFeeder.h"

class WaterFeeder : public IWaterFeeder
{
private:
    const bool valveOn;
    const bool pumpOn;
    const uint8_t mainWaterValvePin;
    const uint8_t pumpPin;
    const uint8_t tankValvePin;

public:
    WaterFeeder(bool valveOn, bool pumpOn, uint8_t mainWaterValvePin, uint8_t pumpPin, uint8_t tankValvePin);
    void start(bool feedWithPump = true) override;
    void stop() override;
    bool isFeeding() override;
    int getTankValveState(bool state) override { return digitalRead(tankValvePin); }
    void setTankValveState(bool state) override { digitalWrite(tankValvePin, state); }
};
