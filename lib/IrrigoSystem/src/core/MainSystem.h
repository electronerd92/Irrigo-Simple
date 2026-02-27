#pragma once
#include <Arduino.h>
#include "interfaces/IMainSystem.h"
#include "interfaces/ISystemManager.h"
#include "interfaces/IRtc.h"
#include "interfaces/IPersistenceManager.h"
#include <interfaces/IMenuSystem.h>
#include <interfaces/IWateringSystem.h>
#include <interfaces/IWateringManager.h>
#include "PersistenceManager.h"
#include <interfaces/IPersistable.h>

// Forward declaration to avoid circular dependency
class SystemManager;

class MainSystem : public IMainSystem
{
private:
    SystemState state;
    IRtc *rtc;
    ISystemManager *sysManager;
    IPersistenceManager *persistenceManager;
    IMenuSystem *menuSys;
    IWateringSystem *wateringSys;

public:
    MainSystem(IRtc *rtc, IPersistenceManager *persistence,
               ISystemManager *sysManager, IMenuSystem *menuSys,
               IWateringSystem *wateringSys);
    void update() override;
    SystemState getState() override;
    void setState(SystemState sysState) override;

    IRtc *getRTC();
    IWateringManager *getWateringManager() override;

    bool saveConfiguration();
    bool loadConfiguration();
    void factoryReset();
    bool isConfigurationValid();
};