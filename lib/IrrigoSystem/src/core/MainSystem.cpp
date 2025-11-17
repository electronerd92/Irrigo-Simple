#include "MainSystem.h"

MainSystem::MainSystem(IRtc *rtc, ISystemManager *sysManager, IMenuSystem *menuSys, IWateringSystem *wateringSys)
    : state(SystemState::Normal),
      rtc(rtc),
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

SystemState MainSystem::getState()
{
    return state;
}

void MainSystem::setState(SystemState sysState)
{
    state = sysState;
}

IRtc *MainSystem::getRTC()
{
    return rtc;
}