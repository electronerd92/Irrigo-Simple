#include "MainSystem.h"

MainSystem::MainSystem(IRtc *rtc, ISystemManager *sysManager, IMenuSystem *menuSys)
    : rtc(rtc),
      sysManager(sysManager),
      menuSys(menuSys)
{
    rtc->begin();
}

void MainSystem::update()
{
    sysManager->update();
    menuSys->update();
}

IRtc *MainSystem::getRTC()
{
    return rtc;
}