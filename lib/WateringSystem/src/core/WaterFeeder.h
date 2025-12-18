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
    void startPump() override;
    void stopPump() override;
    void stopMainWatering()override;
    bool isFeeding() override;
    int getTankValveState() override { return digitalRead(tankValvePin); }
    void setTankValveState(bool state) override { digitalWrite(tankValvePin, state); }
};
