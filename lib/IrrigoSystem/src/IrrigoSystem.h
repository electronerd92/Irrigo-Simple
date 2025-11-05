#ifdef UNIT_TESTING
#else
#ifndef SYSTEM_H
#define SYSTEM_H

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

#endif // SYSTEM_H
#endif // UNIT_TESTING