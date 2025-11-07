#pragma once
#include <interfaces/IMainSystem.h>
#include "MockRtc.h"

class MockMainSystem : public IMainSystem
{
private:
    MockRtc *rtc;
    uint32_t updateCallCount;

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

    // Test helpers
    MockRtc *getMockRTC() { return rtc; }
    uint32_t getUpdateCallCount() const { return updateCallCount; }
    void resetUpdateCallCount() { updateCallCount = 0; }
};