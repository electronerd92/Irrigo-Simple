#pragma once
#ifndef UNIT_TESTING
#include <Arduino.h>
#include <interfaces/IWateringSystem.h>
#include "WateringSysConfig.h"
#include "core/WateringValve.h"
#include "core/WateringManager.h"
#include "core/WaterFeeder.h"

class WateringSystem : public IWateringSystem
{
private:
    WaterFeeder waterFeeder;
    IWateringValve **valves;
    WateringManager wateringManager;

public:
    WateringSystem(ISystemManager *sysManager, const WateringSysConfig &config)
        : waterFeeder(config.valveOn, config.pumpOn, config.valvePinout.valveMainWater, config.pumpPin, config.valvePinout.valveTank),
          wateringManager(sysManager, &waterFeeder, valves, config.wateringValvesCount, config.valvePinout.valveOut, config.valveOn, config.valvePumpDelay)
    {
        valves = new IWateringValve *[config.wateringValvesCount];
        valves[0] = new WateringValve(config.valvePinout.valve1, false);
        valves[1] = new WateringValve(config.valvePinout.valve2, false);
        valves[2] = new WateringValve(config.valvePinout.valve3, false);
        valves[3] = new WateringValve(config.valvePinout.valve4, false);
        valves[4] = new WateringValve(config.valvePinout.valveOut5, true);
        valves[5] = new WateringValve(config.valvePinout.valveOut6, true);
        valves[6] = new WateringValve(config.valvePinout.valveOut7, true);
        valves[7] = new WateringValve(config.valvePinout.valveOut8, true);
    }
    void update() override { wateringManager.update(); }
};

#endif // UNIT_TESTING