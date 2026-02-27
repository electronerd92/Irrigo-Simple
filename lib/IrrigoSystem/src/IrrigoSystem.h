#pragma once

#ifndef UNIT_TESTING

#include <core/MainSystem.h>
#include <core/SystemManager.h>
#include <core/PersistenceManager.h>
#include "hardware/ArduinoEEPROMWriter.h"
#include "hardware/ArduinoEEPROMReader.h"
#include "hardware/Rtc.hpp"
#include <MenuSystem.h>
#include <WateringSystem.h>
#include <config/ConfigFactory.h>

class IrrigoSystem
{
    Rtc rtc;
    ArduinoEEPROMWriter eepromWriter;
    ArduinoEEPROMReader eepromReader;

    // Business logic - ORDER MATTERS for initialization
    SystemManager sysManager;   // 1. Needs mainSys
    MenuSystem menuSys;         // 2. Needs sysManager
    WateringSystem wateringSys; // 3. Needs sysManager

    // Persistence
    IPersistable **persistables;
    PersistenceManager persistenceMgr; // 4. Needs writer/reader/persistables

    // Main system - MUST BE LAST
    MainSystem mainSys; // 5. Needs everything above

    /**
     * @brief Create array of persistable objects
     * @return IPersistable** Array of objects to persist
     */
    IPersistable **createPersistableList()
    {
        persistables = new IPersistable *[1];

        // Use reinterpret_cast for interface-to-interface cast
        // Safe because WateringManager implements both IWateringManager and IPersistable
        persistables[0] = reinterpret_cast<IPersistable *>(wateringSys.getWateringManager());

        return persistables;
    }

public:
    IrrigoSystem()
        : rtc(),
          eepromWriter(0),
          eepromReader(0),
          sysManager(&mainSys),
          menuSys(&sysManager, ConfigFactory::createMenuConfig()),
          wateringSys(&sysManager, ConfigFactory::createWateringSysConfig()),
          persistables(nullptr),
          persistenceMgr(&eepromWriter, &eepromReader, createPersistableList(), 1),
          mainSys(&rtc, &persistenceMgr, &sysManager, &menuSys, &wateringSys)
    {
    }
    void update()
    {
        mainSys.update();
    }
};

#endif // UNIT_TESTING