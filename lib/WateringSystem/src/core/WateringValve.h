#pragma once
#include <Arduino.h>
#include <interfaces/IWateringValve.h>
#include <Timer.h>

class WateringValve : public IWateringValve
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
    void setValveMode(ValveMode newMode, uint32_t currentTime) override;
    int getState() override;
    void open(bool state) override;
    void close(bool state) override;

    void setFrequency(uint8_t freq, uint32_t currentTime) override;
    void setStartTime(uint16_t start, uint32_t currentTime) override;
    void setPeriod(uint32_t period) override;

    bool canBeOpened(uint32_t currentTime) const override;
    bool canBeClosed() const override;
};