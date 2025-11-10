#pragma once
#include <Arduino.h>
#include "interfaces/IWaterFeeder.h"

class WaterFeeder : public IWaterFeeder
{
private:
    const uint8_t mainWaterValvePin;
    const uint8_t pumpPin;
    const uint8_t tankValvePin;

public:
    WaterFeeder(uint8_t mainWaterValvePin, uint8_t pumpPin, uint8_t tankValvePin);
    int getMainWaterValveState(bool state) override { return digitalRead(mainWaterValvePin); }
    void setMainWaterValveState(bool state) override { digitalWrite(mainWaterValvePin, state); }
    int getPumpState(bool state) override { return digitalRead(pumpPin); }
    void setPumpState(bool state) override { digitalWrite(pumpPin, state); }
    int getTankValveState(bool state) override { return digitalRead(tankValvePin); }
    void setTankValveState(bool state) override { digitalWrite(tankValvePin, state); }
};
