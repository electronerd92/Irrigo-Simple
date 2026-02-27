#pragma once
#include <Arduino.h>
#include "WateringSysConfig.h"
#include <interfaces/IWateringManager.h>
#include <interfaces/ISystemManager.h>
#include <interfaces/IEEPROMReader.h>
#include <interfaces/IEEPROMWriter.h>
#include <interfaces/IPersistable.h>
#include "interfaces/IWaterFeeder.h"
#include "interfaces/IWateringValve.h"
#include <Timer.h>

class WateringManager : public IWateringManager, public IPersistable
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
    uint8_t selectedValveIndex;

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
    void update() override;

    uint8_t getSelectedValve() override { return selectedValveIndex; }
    void setSelectedValve(uint8_t index) override { selectedValveIndex = index; }
    uint8_t getValvesCount() override { return wateringValvesCount; }

    ValveMode getSelectedValveMode() override { return wateringValves[selectedValveIndex]->getMode(); }
    void setSelectedValveMode(ValveMode newMode) override { wateringValves[selectedValveIndex]->setSelectedValveMode(newMode, sysManager->getUnixTime()); }

    uint32_t getSelectedValveFrequency() override { return wateringValves[selectedValveIndex]->getFrequency(); }
    void setSelectedValveFrequency(uint32_t frequency) override { wateringValves[selectedValveIndex]->setFrequency(frequency, sysManager->getUnixTime()); }

    uint32_t getSelectedValveDuration() override { return wateringValves[selectedValveIndex]->getDuration(); }
    void setSelectedValveDuration(uint32_t duration) override { wateringValves[selectedValveIndex]->setDuration(duration); }

    uint32_t getSelectedValveStartTime() override { return wateringValves[selectedValveIndex]->getStartTime(); }
    void setSelectedValveStartTime(uint32_t startTime) override { wateringValves[selectedValveIndex]->setStartTime(startTime, sysManager->getUnixTime()); }

    void save(IEEPROMWriter &writer) const override;
    void load(IEEPROMReader &reader) override;
    uint16_t getSerializedSize() const override;
};