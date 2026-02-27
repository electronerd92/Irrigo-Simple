#pragma once
#include <Arduino.h>
#include <interfaces/IWateringValve.h>
#include <Timer.h>
#include <interfaces/IPersistable.h>
#include <interfaces/IEEPROMWriter.h>
#include <interfaces/IEEPROMReader.h>

class WateringValve : public IWateringValve, public IPersistable
{
private:
    const uint8_t pin;
    const bool isOutdoor;
    ValveMode mode;
    uint32_t frequency; // in seconds
    Timer timer;
    uint32_t nextWateringTime; // in seconds since epoch
    uint32_t startTime;        // in seconds since midnight

    void updateNextWateringTime(uint32_t currentTime);

public:
    WateringValve(uint8_t valvePin, bool out);
    bool getIsOutdoor() const override;
    ValveMode getMode() const override { return mode; }
    uint32_t getFrequency() const override { return frequency; }
    uint32_t getStartTime() const override { return startTime; }
    uint32_t getDuration() const override { return timer.getInterval() / 1000LU; }

    void setSelectedValveMode(ValveMode newMode, uint32_t currentTime) override;
    int getState() override;
    void open(bool state) override;
    void close(bool state) override;

    void setFrequency(uint32_t freq, uint32_t currentTime) override;
    void setStartTime(uint32_t start, uint32_t currentTime) override;
    void setDuration(uint32_t period) override;

    bool canBeOpened(uint32_t currentTime) const override;
    bool canBeClosed() const override;

    void save(IEEPROMWriter &writer) const override;
    void load(IEEPROMReader &reader) override;
    uint16_t getSerializedSize() const override;
};