#pragma once
#include <Arduino.h>
#include "WateringSysConfig.h"
#include <interfaces/ISystemManager.h>
#include "interfaces/IWaterFeeder.h"
#include "interfaces/IWateringValve.h"

class WateringManager
{
private:
    ISystemManager *sysManager;
    IWaterFeeder *waterFeeder;
    IWateringValve **wateringValves;
    const uint8_t wateringValvesCount;
    const bool valveOn;
    const bool pumpOn;

    void turnWateringOff();

public:
    WateringManager(ISystemManager *sysManager, IWaterFeeder *waterFeeder, IWateringValve **wateringValves, uint8_t valvesCount, bool valveOn, bool pumpOn);
    void update();
};