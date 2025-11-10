#pragma once

#ifndef UNIT_TESTING

#include <core/MainSystem.h>
#include <core/SystemManager.h>
#include "hardware/Rtc.hpp"
#include <MenuSystem.h>
#include <WateringSystem.h>
#include <config/ConfigFactory.h>

class IrrigoSystem
{
    Rtc rtc;
    SystemManager sysManager;
    MenuSystem menuSys;
    WateringSystem wateringSys;
    MainSystem mainSys;

public:
    IrrigoSystem()
        : rtc(),
          sysManager(&mainSys),
          menuSys(&sysManager, ConfigFactory::createMenuConfig()),
          wateringSys(&sysManager, ConfigFactory::createWateringSysConfig()),
          mainSys(&rtc, &sysManager, &menuSys, &wateringSys)
    {
    }
    void update() { mainSys.update(); }
};

#endif // UNIT_TESTING