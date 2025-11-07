#pragma once

#ifndef UNIT_TESTING

#include <core/MainSystem.h>
#include <core/SystemManager.h>
#include "hardware/Rtc.hpp"
#include <MenuSystem.h>
#include <config/ConfigFactory.h>

class IrrigoSystem
{
    Rtc rtc;
    SystemManager sysManager;
    MenuSystem menuSys;
    MainSystem mainSys;

public:
    IrrigoSystem()
        : rtc(),
          sysManager(&mainSys),
          menuSys(&sysManager, ConfigFactory::createMenuConfig()),
          mainSys(&rtc, &sysManager, &menuSys)
    {
    }
    void update() { mainSys.update(); }
};

#endif // UNIT_TESTING