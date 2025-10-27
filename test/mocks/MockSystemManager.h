#ifndef MOCK_SYSTEM_MANAGER_H
#define MOCK_SYSTEM_MANAGER_H

#include <RTClib.h>
#include <interfaces/ISystemManager.h>

class MockSystemManager : public ISystemManager
{
private:
    DateTime mockDateTime;

public:
    MockSystemManager() : mockDateTime(2024, 1, 15, 12, 30, 0) {}

    DateTime getDateTime() override
    {
        return mockDateTime;
    }

    void incrementDay() override
    {
        mockDateTime = DateTime(mockDateTime.year(), mockDateTime.month(),
                                mockDateTime.day() + 1, mockDateTime.hour(),
                                mockDateTime.minute(), mockDateTime.second());
    }

    void decreaseDay() override
    {
        if (mockDateTime.day() > 1)
        {
            mockDateTime = DateTime(mockDateTime.year(), mockDateTime.month(),
                                    mockDateTime.day() - 1, mockDateTime.hour(),
                                    mockDateTime.minute(), mockDateTime.second());
        }
    }

    void incrementMonth() override
    {
        uint16_t newMonth = mockDateTime.month() + 1;
        uint16_t newYear = mockDateTime.year();
        if (newMonth > 12)
        {
            newMonth = 1;
            newYear++;
        }
        mockDateTime = DateTime(newYear, newMonth, mockDateTime.day(),
                                mockDateTime.hour(), mockDateTime.minute(), mockDateTime.second());
    }

    void decreaseMonth() override
    {
        uint16_t newMonth = mockDateTime.month() - 1;
        uint16_t newYear = mockDateTime.year();
        if (newMonth < 1)
        {
            newMonth = 12;
            newYear--;
        }
        mockDateTime = DateTime(newYear, newMonth, mockDateTime.day(),
                                mockDateTime.hour(), mockDateTime.minute(), mockDateTime.second());
    }

    void incrementYear() override
    {
        mockDateTime = DateTime(mockDateTime.year() + 1, mockDateTime.month(),
                                mockDateTime.day(), mockDateTime.hour(),
                                mockDateTime.minute(), mockDateTime.second());
    }

    void decreaseYear() override
    {
        if (mockDateTime.year() > 2000)
        {
            mockDateTime = DateTime(mockDateTime.year() - 1, mockDateTime.month(),
                                    mockDateTime.day(), mockDateTime.hour(),
                                    mockDateTime.minute(), mockDateTime.second());
        }
    }

    void incrementHour() override
    {
        uint8_t newHour = (mockDateTime.hour() + 1) % 24;
        mockDateTime = DateTime(mockDateTime.year(), mockDateTime.month(),
                                mockDateTime.day(), newHour,
                                mockDateTime.minute(), mockDateTime.second());
    }

    void decreaseHour() override
    {
        uint8_t newHour = mockDateTime.hour();
        if (newHour == 0)
        {
            newHour = 23;
        }
        else
        {
            newHour--;
        }
        mockDateTime = DateTime(mockDateTime.year(), mockDateTime.month(),
                                mockDateTime.day(), newHour,
                                mockDateTime.minute(), mockDateTime.second());
    }

    void incrementMinute() override
    {
        uint8_t newMinute = (mockDateTime.minute() + 1) % 60;
        mockDateTime = DateTime(mockDateTime.year(), mockDateTime.month(),
                                mockDateTime.day(), mockDateTime.hour(),
                                newMinute, mockDateTime.second());
    }

    void decreaseMinute() override
    {
        uint8_t newMinute = mockDateTime.minute();
        if (newMinute == 0)
        {
            newMinute = 59;
        }
        else
        {
            newMinute--;
        }
        mockDateTime = DateTime(mockDateTime.year(), mockDateTime.month(),
                                mockDateTime.day(), mockDateTime.hour(),
                                newMinute, mockDateTime.second());
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
};

#endif // MOCK_SYSTEM_MANAGER_H