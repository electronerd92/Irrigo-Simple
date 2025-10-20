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

DateTime MainSystem::getDateTime()
{
    return rtc.now();
}