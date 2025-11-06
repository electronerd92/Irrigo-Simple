#ifndef MOCK_RTC_H
#define MOCK_RTC_H

#include <interfaces/IRtc.h>

class MockRtc : public IRtc
{
private:
    RtcDateTime currentTime;
    bool initialized;
    uint32_t adjustCallCount;

public:
    MockRtc() : currentTime{2024, 1, 15, 12, 30, 0}, initialized(false), adjustCallCount(0)
    {
    }

    RtcDateTime now() override
    {
        return currentTime;
    }

    void adjust(const RtcDateTime &dt) override
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
    void setTime(const RtcDateTime &dt) { currentTime = dt; }
    bool isInitialized() const { return initialized; }
    uint32_t getAdjustCallCount() const { return adjustCallCount; }
    void resetCallCount() { adjustCallCount = 0; }
};

#endif // MOCK_RTC_H