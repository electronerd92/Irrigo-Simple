#pragma once
#include <Arduino.h>

class IWaterFeeder
{
public:
    virtual void startPump() = 0;
    virtual void stopPump() = 0;
    virtual void stopMainWatering() = 0;
    virtual bool isFeeding() = 0;
    virtual int getTankValveState() = 0;
    virtual void setTankValveState(bool state) = 0;
};