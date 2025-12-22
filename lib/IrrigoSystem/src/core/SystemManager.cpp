#include "SystemManager.h"
#include <Compatibility.h>

SystemManager::SystemManager(IMainSystem *mainSystem)
    : mainSystem(mainSystem)
{
}

void SystemManager::update()
{
}

SystemState SystemManager::getSystemState()
{
    return mainSystem->getState();
}

void SystemManager::setSystemState(SystemState sysState)
{
    mainSystem->setState(sysState);
}

RtcDateTime SystemManager::getDateTime()
{
    return mainSystem->getRTC()->now();
}

uint32_t SystemManager::getUnixTime()
{
    return mainSystem->getRTC()->unixtime();
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
    IRtc *rtc = mainSystem->getRTC();
    RtcDateTime now = rtc->now();
    uint8_t day = now.day + 1;
    uint8_t maxDay = daysInMonth(now.year, now.month);

    if (day > maxDay)
        day = 1;

    RtcDateTime newDateTime = {now.year, now.month, day, now.hour, now.minute, now.second};
    rtc->adjust(newDateTime);
}

void SystemManager::decreaseDay()
{
    IRtc *rtc = mainSystem->getRTC();
    RtcDateTime now = rtc->now();
    uint8_t day = now.day - 1;
    uint8_t maxDay = daysInMonth(now.year, now.month);

    if (day < 1)
        day = maxDay;

    RtcDateTime newDateTime = {now.year, now.month, day, now.hour, now.minute, now.second};
    rtc->adjust(newDateTime);
}

void SystemManager::incrementMonth()
{
    IRtc *rtc = mainSystem->getRTC();
    RtcDateTime now = rtc->now();
    uint8_t month = (now.month % 12) + 1;
    uint16_t year = now.year;

    uint8_t maxDay = daysInMonth(year, month);
    uint8_t day = min(now.day, maxDay);

    RtcDateTime newDateTime = {year, month, day, now.hour, now.minute, now.second};
    rtc->adjust(newDateTime);
}

void SystemManager::decreaseMonth()
{
    IRtc *rtc = mainSystem->getRTC();
    RtcDateTime now = rtc->now();
    uint8_t month = (now.month + 10) % 12 + 1;
    uint16_t year = now.year;

    uint8_t maxDay = daysInMonth(year, month);
    uint8_t day = min(now.day, maxDay);

    RtcDateTime newDateTime = {year, month, day, now.hour, now.minute, now.second};
    rtc->adjust(newDateTime);
}

void SystemManager::incrementYear()
{
    IRtc *rtc = mainSystem->getRTC();
    RtcDateTime now = rtc->now();
    RtcDateTime newDateTime = {(uint16_t)(now.year + 1), now.month, now.day, now.hour, now.minute, now.second};
    rtc->adjust(newDateTime);
}

void SystemManager::decreaseYear()
{
    IRtc *rtc = mainSystem->getRTC();
    RtcDateTime now = rtc->now();
    RtcDateTime newDateTime = {(uint16_t)(now.year - 1), now.month, now.day, now.hour, now.minute, now.second};
    rtc->adjust(newDateTime);
}

void SystemManager::incrementHour()
{
    IRtc *rtc = mainSystem->getRTC();
    RtcDateTime now = rtc->now();
    uint8_t hour = (now.hour + 1) % 24;

    RtcDateTime newDateTime = {now.year, now.month, now.day, hour, now.minute, now.second};
    rtc->adjust(newDateTime);
}

void SystemManager::decreaseHour()
{
    IRtc *rtc = mainSystem->getRTC();
    RtcDateTime now = rtc->now();
    uint8_t hour = (now.hour + 23) % 24;

    RtcDateTime newDateTime = {now.year, now.month, now.day, hour, now.minute, now.second};
    rtc->adjust(newDateTime);
}

void SystemManager::incrementMinute()
{
    IRtc *rtc = mainSystem->getRTC();
    RtcDateTime now = rtc->now();
    uint8_t minute = (now.minute + 1) % 60;

    RtcDateTime newDateTime = {now.year, now.month, now.day, now.hour, minute, 0};
    rtc->adjust(newDateTime);
}

void SystemManager::decreaseMinute()
{
    IRtc *rtc = mainSystem->getRTC();
    RtcDateTime now = rtc->now();
    uint8_t minute = (now.minute + 59) % 60;

    RtcDateTime newDateTime = {now.year, now.month, now.day, now.hour, minute, 0};
    rtc->adjust(newDateTime);
}
/* #endregion RTC settings */

uint8_t SystemManager::getSelectedValve()
{
    return mainSystem->getWateringManager()->getSelectedValve();
}

void SystemManager::incrementSelectedValve()
{
    IWateringManager *wateringManager = mainSystem->getWateringManager();
    uint8_t valvesCount = wateringManager->getValvesCount();
    wateringManager->setSelectedValve((wateringManager->getSelectedValve() + 1) % valvesCount);
}

void SystemManager::decreaseSelectedValve()
{
    IWateringManager *wateringManager = mainSystem->getWateringManager();
    uint8_t valvesCount = wateringManager->getValvesCount();
    uint8_t currentValve = wateringManager->getSelectedValve();
    wateringManager->setSelectedValve(currentValve == 0 ? valvesCount - 1 : currentValve - 1);
}