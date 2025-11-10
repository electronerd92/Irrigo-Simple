#include "MainSystem.h"

MainSystem::MainSystem(IRtc *rtc, ISystemManager *sysManager, IMenuSystem *menuSys, IWateringSystem *wateringSys)
    : rtc(rtc),
      sysManager(sysManager),
      menuSys(menuSys),
      wateringSys(wateringSys)
{
    rtc->begin();
}

void MainSystem::update()
{
    sysManager->update();
    menuSys->update();
    wateringSys->update();
}

IRtc *MainSystem::getRTC()
{
    return rtc;
}