#include "MainSystem.h"
#include "SystemManager.h"

MainSystem::MainSystem() : rtc()
{
    rtc.begin();
    systemManager = new SystemManager(this);
}

void MainSystem::update()
{
    systemManager->update();
}

RTC_DS3231 *MainSystem::getRTC()
{
    return &rtc;
}