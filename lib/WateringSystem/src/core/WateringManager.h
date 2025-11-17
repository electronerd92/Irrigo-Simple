#pragma once
#include <Arduino.h>
#include "WateringSysConfig.h"
#include <interfaces/ISystemManager.h>
#include "interfaces/IWaterFeeder.h"
#include "interfaces/IWateringValve.h"
#include <Timer.h>

class WateringManager
{
private:
    ISystemManager *sysManager;
    IWaterFeeder *waterFeeder;
    IWateringValve **wateringValves;
    const uint8_t wateringValvesCount;
    const uint8_t outdoorValvePin;
    const bool valveOn;
    Timer valvePumpDelayTimer;
    bool ongoingOpeningClosing;

    int getOutdoorValveState();
    void setOutdoorValveState(bool state);

    void checkAndOpenValve();
    void checkAndCloseValve();
    void manageOngoingOperation(int8_t openedValve);
    int8_t getOpenedValve();
    void turnWateringOff();

public:
    WateringManager(ISystemManager *sysManager, IWaterFeeder *waterFeeder, IWateringValve **wateringValves, uint8_t valvesCount,
                    uint8_t outdoorValvePin, bool valveOn, uint32_t valvePumpDelay);
    void update();
};