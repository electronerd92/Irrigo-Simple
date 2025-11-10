#pragma once
#include <Arduino.h>

class IWaterFeeder
{
public:
    virtual int getMainWaterValveState(bool state) = 0;
    virtual void setMainWaterValveState(bool state) = 0;
    virtual int getPumpState(bool state) = 0;
    virtual void setPumpState(bool state) = 0;
    virtual int getTankValveState(bool state) = 0;
    virtual void setTankValveState(bool state) = 0;
};