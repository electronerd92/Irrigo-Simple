#include "MainSystem.h"

MainSystem::MainSystem(IRtc *rtc, IPersistenceManager *persistence,
                       ISystemManager *sysManager, IMenuSystem *menuSys,
                       IWateringSystem *wateringSys)
    : state(SystemState::Normal),
      rtc(rtc),
      sysManager(sysManager),
      persistenceManager(persistence),
      menuSys(menuSys),
      wateringSys(wateringSys)
{
    rtc->begin();
    persistenceManager->load();
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

IWateringManager *MainSystem::getWateringManager()
{
    return wateringSys->getWateringManager();
}

bool MainSystem::saveConfiguration()
{
    return persistenceManager->save();
}

bool MainSystem::loadConfiguration()
{
    return persistenceManager->load();
}

void MainSystem::factoryReset()
{
    persistenceManager->reset();
}

bool MainSystem::isConfigurationValid()
{
    return persistenceManager->isValid();
}