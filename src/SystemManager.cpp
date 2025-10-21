#include "SystemManager.h"
#include "menu/Menu.h"

SystemManager::SystemManager(MainSystem *mainSystem)
    : mainSystem(mainSystem)
{
    menu = new Menu(this);
}

void SystemManager::update()
{
    menu->update();
}

DateTime SystemManager::getDateTime()
{
    return mainSystem->getRTC()->now();
}

/* #region RTC settings */
// Utility function to calculate the number of days in a given month
uint8_t SystemManager::daysInMonth(uint16_t year, uint8_t month)
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

void SystemManager::incrementDay()
{
    RTC_DS3231 *rtc = mainSystem->getRTC();
    DateTime now = rtc->now();
    uint8_t day = now.day() + 1;
    uint8_t maxDay = daysInMonth(now.year(), now.month());

    if (day > maxDay)
    {
        day = 1;
    }

    DateTime newDateTime = DateTime(now.year(), now.month(), day, now.hour(), now.minute(), now.second());
    rtc->adjust(newDateTime);
}

void SystemManager::decreaseDay()
{
    RTC_DS3231 *rtc = mainSystem->getRTC();
    DateTime now = rtc->now();
    uint8_t day = now.day() - 1;
    uint8_t maxDay = daysInMonth(now.year(), now.month());

    if (day < 1)
    {
        day = maxDay;
    }

    DateTime newDateTime = DateTime(now.year(), now.month(), day, now.hour(), now.minute(), now.second());
    rtc->adjust(newDateTime);
}

void SystemManager::incrementMonth()
{
    RTC_DS3231 *rtc = mainSystem->getRTC();
    DateTime now = rtc->now();
    uint8_t month = (now.month() % 12) + 1;
    uint16_t year = now.year();

    uint8_t maxDay = daysInMonth(year, month);
    uint8_t day = min(now.day(), maxDay);

    DateTime newDateTime = DateTime(year, month, day, now.hour(), now.minute(), now.second());
    rtc->adjust(newDateTime);
}

void SystemManager::decreaseMonth()
{
    RTC_DS3231 *rtc = mainSystem->getRTC();
    DateTime now = rtc->now();
    uint8_t month = (now.month() + 10) % 12 + 1;
    uint16_t year = now.year();

    uint8_t maxDay = daysInMonth(year, month);
    uint8_t day = min(now.day(), maxDay);

    DateTime newDateTime = DateTime(year, month, day, now.hour(), now.minute(), now.second());
    rtc->adjust(newDateTime);
}

void SystemManager::incrementYear()
{
    RTC_DS3231 *rtc = mainSystem->getRTC();
    DateTime now = rtc->now();
    DateTime newDateTime = DateTime(now.year() + 1, now.month(), now.day(), now.hour(), now.minute(), now.second());
    rtc->adjust(newDateTime);
}

void SystemManager::decreaseYear()
{
    RTC_DS3231 *rtc = mainSystem->getRTC();
    DateTime now = rtc->now();
    DateTime newDateTime = DateTime(now.year() - 1, now.month(), now.day(), now.hour(), now.minute(), now.second());
    rtc->adjust(newDateTime);
}

void SystemManager::incrementHour()
{
    RTC_DS3231 *rtc = mainSystem->getRTC();
    DateTime now = rtc->now();
    uint8_t hour = (now.hour() + 1) % 24;

    DateTime newDateTime = DateTime(now.year(), now.month(), now.day(), hour, now.minute(), now.second());
    rtc->adjust(newDateTime);
}

void SystemManager::decreaseHour()
{
    RTC_DS3231 *rtc = mainSystem->getRTC();
    DateTime now = rtc->now();
    uint8_t hour = (now.hour() + 23) % 24;

    DateTime newDateTime = DateTime(now.year(), now.month(), now.day(), hour, now.minute(), now.second());
    rtc->adjust(newDateTime);
}

void SystemManager::incrementMinute()
{
    RTC_DS3231 *rtc = mainSystem->getRTC();
    DateTime now = rtc->now();
    uint8_t minute = (now.minute() + 1) % 60;

    DateTime newDateTime = DateTime(now.year(), now.month(), now.day(), now.hour(), minute, 0);
    rtc->adjust(newDateTime);
}

void SystemManager::decreaseMinute()
{
    RTC_DS3231 *rtc = mainSystem->getRTC();
    DateTime now = rtc->now();
    uint8_t minute = (now.minute() + 59) % 60;

    DateTime newDateTime = DateTime(now.year(), now.month(), now.day(), now.hour(), minute, 0);
    rtc->adjust(newDateTime);
}
/* #endregion RTC settings */