#pragma once
#include <Arduino.h>

enum class ValveMode : uint8_t
{
    OFF,
    TIMER,
    COUNT // used to get the number of ValveMode by Menu
};

class IWateringValve
{
public:
    virtual void setValveMode(ValveMode newMode) = 0;
    virtual const bool getIsOutdoor() = 0;
    virtual int getState() = 0;
    virtual void setState(bool state) = 0;
    virtual bool canBeOpened() = 0;
    virtual bool canBeClosed() = 0;
};