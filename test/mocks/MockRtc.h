#pragma once
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

    uint32_t unixtime() override
    {
        // Simple conversion for testing purposes (not accounting for leap years, etc.)
        return (currentTime.year - 1970) * 31536000 + (currentTime.month - 1) * 2592000 +
               (currentTime.day - 1) * 86400 + currentTime.hour * 3600 + currentTime.minute * 60 + currentTime.second;
    }

    // Test helpers
    void setCurrentTime(const RtcDateTime &dt) { currentTime = dt; }

    // Test helpers
    void setTime(const RtcDateTime &dt) { currentTime = dt; }
    bool isInitialized() const { return initialized; }
    uint32_t getAdjustCallCount() const { return adjustCallCount; }
    void resetCallCount() { adjustCallCount = 0; }
};