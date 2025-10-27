#ifndef MOCK_RTC_H
#define MOCK_RTC_H

#include <interfaces/IRtc.h>

class MockRtc : public IRtc
{
private:
    DateTime currentTime;
    bool initialized;
    uint32_t adjustCallCount;

public:
    MockRtc() : currentTime(2024, 1, 15, 12, 30, 0), initialized(false), adjustCallCount(0) {}

    DateTime now() override
    {
        return currentTime;
    }

    void adjust(const DateTime &dt) override
    {
        currentTime = dt;
        adjustCallCount++;
    }

    bool begin() override
    {
        initialized = true;
        return true;
    }

    // Test helpers
    void setTime(const DateTime &dt) { currentTime = dt; }
    bool isInitialized() const { return initialized; }
    uint32_t getAdjustCallCount() const { return adjustCallCount; }
    void resetCallCount() { adjustCallCount = 0; }
};

#endif // MOCK_RTC_H