#include "MainSystem.h"
#include "SystemManager.h"
#include "config/ConfigFactory.h"
#include "hardware/Rtc.hpp"

MainSystem::MainSystem() : rtc(nullptr)
{
    rtc = new Rtc();
    rtc->begin();
    sysManager = new SystemManager(this);
    menuSys = new MenuSystem(sysManager, ConfigFactory::createMenuConfig());
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