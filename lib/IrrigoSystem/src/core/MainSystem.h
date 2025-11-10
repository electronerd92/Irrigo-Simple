#pragma once
#include <Arduino.h>
#include "interfaces/IMainSystem.h"
#include "interfaces/ISystemManager.h"
#include "interfaces/IRtc.h"
#include <interfaces/IMenuSystem.h>
#include <interfaces/IWateringSystem.h>

// Forward declaration to avoid circular dependency
class SystemManager;

class MainSystem : public IMainSystem
{
private:
    IRtc *rtc;
    ISystemManager *sysManager;
    IMenuSystem *menuSys;
    IWateringSystem *wateringSys;

public:
    MainSystem(IRtc *rtc, ISystemManager *sysManager, IMenuSystem *menuSys, IWateringSystem *wateringSys);
    void update() override;
    IRtc *getRTC();
};