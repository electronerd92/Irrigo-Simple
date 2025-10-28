#ifndef MOCK_SYSTEM_MANAGER_H
#define MOCK_SYSTEM_MANAGER_H

#include <interfaces/ISystemManager.h>
#include <interfaces/IRtc.h>

class MockSystemManager : public ISystemManager
{
private:
    RtcDateTime mockRtcDateTime;
    uint8_t updateCallCount;

    // Mirror your real implementation's utility function
    uint8_t daysInMonth(uint16_t year, uint8_t month)
    {
        if (month == 2)
        {
            // Check for leap year
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            {
                return 29;
            }
            else
            {
                return 28;
            }
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            return 30;
        }
        else
        {
            return 31;
        }
    }

public:
    MockSystemManager() : mockRtcDateTime{2024, 1, 15, 12, 30, 0}, updateCallCount(0) {}

    void update()
    {
        updateCallCount++;
    }

    RtcDateTime getRtcDateTime() override
    {
        return mockRtcDateTime;
    }

    // Implement exactly like your real SystemManager
    void incrementDay() override
    {
        RtcDateTime now = mockRtcDateTime;
        uint8_t day = now.day + 1;
        uint8_t maxDay = daysInMonth(now.year, now.month);

        if (day > maxDay)
            day = 1;

        mockRtcDateTime = {now.year, now.month, day, now.hour, now.minute, now.second};
    }

    void decreaseDay() override
    {
        RtcDateTime now = mockRtcDateTime;
        uint8_t day = now.day - 1;
        uint8_t maxDay = daysInMonth(now.year, now.month);

        if (day < 1)
            day = maxDay;

        mockRtcDateTime = {now.year, now.month, day, now.hour, now.minute, now.second};
    }

    void incrementMonth() override
    {
        RtcDateTime now = mockRtcDateTime;
        uint8_t month = (now.month % 12) + 1;
        uint16_t year = now.year;

        uint8_t maxDay = daysInMonth(year, month);
        uint8_t day = min(now.day, maxDay);

        mockRtcDateTime = {year, month, day, now.hour, now.minute, now.second};
    }

    void decreaseMonth() override
    {
        RtcDateTime now = mockRtcDateTime;
        uint8_t month = (now.month + 10) % 12 + 1;
        uint16_t year = now.year;

        uint8_t maxDay = daysInMonth(year, month);
        uint8_t day = min(now.day, maxDay);

        mockRtcDateTime = {year, month, day, now.hour, now.minute, now.second};
    }

    void incrementYear() override
    {
        RtcDateTime now = mockRtcDateTime;
        mockRtcDateTime = {now.year + 1, now.month, now.day, now.hour, now.minute, now.second};
    }

    void decreaseYear() override
    {
        RtcDateTime now = mockRtcDateTime;
        mockRtcDateTime = {now.year - 1, now.month, now.day, now.hour, now.minute, now.second};
    }

    void incrementHour() override
    {
        RtcDateTime now = mockRtcDateTime;
        uint8_t hour = (now.hour + 1) % 24;

        mockRtcDateTime = {now.year, now.month, now.day, hour, now.minute, now.second};
    }

    void decreaseHour() override
    {
        RtcDateTime now = mockRtcDateTime;
        uint8_t hour = (now.hour + 23) % 24;

        mockRtcDateTime = {now.year, now.month, now.day, hour, now.minute, now.second};
    }

    void incrementMinute() override
    {
        RtcDateTime now = mockRtcDateTime;
        uint8_t minute = (now.minute + 1) % 60;

        mockRtcDateTime = {now.year, now.month, now.day, now.hour, minute, 0};
    }

    void decreaseMinute() override
    {
        RtcDateTime now = mockRtcDateTime;
        uint8_t minute = (now.minute + 59) % 60;

        mockRtcDateTime = {now.year, now.month, now.day, now.hour, minute, 0};
    }

    // Test helper methods
    void setRtcDateTime(const RtcDateTime &dt)
    {
        mockRtcDateTime = dt;
    }

    void setRtcDateTime(uint16_t year, uint8_t month, uint8_t day,
                        uint8_t hour, uint8_t minute, uint8_t second)
    {
        mockRtcDateTime = {year, month, day, hour, minute, second};
    }

    uint8_t getUpdateCallCount() const
    {
        return updateCallCount;
    }

    void resetUpdateCallCount()
    {
        updateCallCount = 0;
    }
};

#endif // MOCK_SYSTEM_MANAGER_H