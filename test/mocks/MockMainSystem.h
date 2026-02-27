#pragma once
#include <interfaces/IMainSystem.h>
#include "MockRtc.h"

class MockMainSystem : public IMainSystem
{
private:
    MockRtc *rtc;
    uint32_t updateCallCount;
    SystemState currentState;

public:
    MockMainSystem() : rtc(new MockRtc()), updateCallCount(0) {}

    ~MockMainSystem()
    {
        delete rtc;
    }

    void update() override
    {
        updateCallCount++;
    }

    IRtc *getRTC() override
    {
        return rtc;
    }

    IWateringManager *getWateringManager() override
    {
        return nullptr; // Return nullptr for testing purposes
    }

    SystemState getState() override
    {
        return currentState;
    }

    void setState(SystemState sysState) override
    {
        currentState = sysState;
    }

    // Test helpers
    MockRtc *getMockRTC() { return rtc; }
    uint32_t getUpdateCallCount() const { return updateCallCount; }
    void resetUpdateCallCount() { updateCallCount = 0; }
};