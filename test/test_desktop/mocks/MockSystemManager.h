#ifndef MOCK_SYSTEM_MANAGER_H
#define MOCK_SYSTEM_MANAGER_H

#include <RTClib.h>
#include <interfaces/ISystemManager.h>

class MockSystemManager : public ISystemManager
{
private:
    DateTime mockDateTime;
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
    MockSystemManager() : mockDateTime(2024, 1, 15, 12, 30, 0), updateCallCount(0) {}

    void update()
    {
        updateCallCount++;
    }

    DateTime getDateTime() override
    {
        return mockDateTime;
    }

    // Implement exactly like your real SystemManager
    void incrementDay() override
    {
        DateTime now = mockDateTime;
        uint8_t day = now.day() + 1;
        uint8_t maxDay = daysInMonth(now.year(), now.month());

        if (day > maxDay)
        {
            day = 1;
        }

        mockDateTime = DateTime(now.year(), now.month(), day, now.hour(), now.minute(), now.second());
    }

    void decreaseDay() override
    {
        DateTime now = mockDateTime;
        uint8_t day = now.day() - 1;
        uint8_t maxDay = daysInMonth(now.year(), now.month());

        if (day < 1)
        {
            day = maxDay;
        }

        mockDateTime = DateTime(now.year(), now.month(), day, now.hour(), now.minute(), now.second());
    }

    void incrementMonth() override
    {
        DateTime now = mockDateTime;
        uint8_t month = (now.month() % 12) + 1;
        uint16_t year = now.year();

        uint8_t maxDay = daysInMonth(year, month);
        uint8_t day = min(now.day(), maxDay);

        mockDateTime = DateTime(year, month, day, now.hour(), now.minute(), now.second());
    }

    void decreaseMonth() override
    {
        DateTime now = mockDateTime;
        uint8_t month = (now.month() + 10) % 12 + 1;
        uint16_t year = now.year();

        uint8_t maxDay = daysInMonth(year, month);
        uint8_t day = min(now.day(), maxDay);

        mockDateTime = DateTime(year, month, day, now.hour(), now.minute(), now.second());
    }

    void incrementYear() override
    {
        DateTime now = mockDateTime;
        mockDateTime = DateTime(now.year() + 1, now.month(), now.day(),
                                now.hour(), now.minute(), now.second());
    }

    void decreaseYear() override
    {
        DateTime now = mockDateTime;
        mockDateTime = DateTime(now.year() - 1, now.month(), now.day(),
                                now.hour(), now.minute(), now.second());
    }

    void incrementHour() override
    {
        DateTime now = mockDateTime;
        uint8_t hour = (now.hour() + 1) % 24;

        mockDateTime = DateTime(now.year(), now.month(), now.day(),
                                hour, now.minute(), now.second());
    }

    void decreaseHour() override
    {
        DateTime now = mockDateTime;
        uint8_t hour = (now.hour() + 23) % 24;

        mockDateTime = DateTime(now.year(), now.month(), now.day(),
                                hour, now.minute(), now.second());
    }

    void incrementMinute() override
    {
        DateTime now = mockDateTime;
        uint8_t minute = (now.minute() + 1) % 60;

        mockDateTime = DateTime(now.year(), now.month(), now.day(),
                                now.hour(), minute, 0);
    }

    void decreaseMinute() override
    {
        DateTime now = mockDateTime;
        uint8_t minute = (now.minute() + 59) % 60;

        mockDateTime = DateTime(now.year(), now.month(), now.day(),
                                now.hour(), minute, 0);
    }

    // Test helper methods
    void setDateTime(const DateTime &dt)
    {
        mockDateTime = dt;
    }

    void setDateTime(uint16_t year, uint8_t month, uint8_t day,
                     uint8_t hour, uint8_t minute, uint8_t second)
    {
        mockDateTime = DateTime(year, month, day, hour, minute, second);
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