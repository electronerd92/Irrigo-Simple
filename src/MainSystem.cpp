#include "MainSystem.h"
#include "SystemManager.h"
#include "ConfigFactory.h"

MainSystem::MainSystem() : rtc()
{
    rtc.begin();
    sysManager = new SystemManager(this);
    menuSys = new MenuSystem(sysManager, ConfigFactory::createMenuConfig());
}

void MainSystem::update()
{
    sysManager->update();
    menuSys->update();
}

RTC_DS3231 *MainSystem::getRTC()
{
    return &rtc;
}