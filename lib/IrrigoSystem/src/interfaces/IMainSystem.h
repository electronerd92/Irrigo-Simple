#pragma once
#include <Arduino.h>
#include "IRtc.h"
#include <interfaces/IWateringManager.h>

enum class SystemState : uint8_t
{
    Normal,
    Testing,
    Warning,
    Error
};

class IMainSystem
{
public:
    virtual void update() = 0;
    virtual IRtc *getRTC() = 0;
    virtual IWateringManager *getWateringManager() = 0;
    virtual SystemState getState() = 0;
    virtual void setState(SystemState sysState) = 0;
};