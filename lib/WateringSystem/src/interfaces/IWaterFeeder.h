#pragma once
#include <Arduino.h>

class IWaterFeeder
{
public:
    virtual void start(bool feedWithPump = true) = 0;
    virtual void stop() = 0;
    virtual bool isFeeding() = 0;
    virtual int getTankValveState(bool state) = 0;
    virtual void setTankValveState(bool state) = 0;
};