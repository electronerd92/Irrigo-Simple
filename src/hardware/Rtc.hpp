#pragma once
#ifndef UNIT_TESTING
#include <RTClib.h>
#include "interfaces/IRtc.h"

class Rtc : public IRtc
{
private:
    RTC_DS3231 rtc;

public:
    Rtc() : rtc() {}

    RtcDateTime now() override
    {
        DateTime dt = rtc.now();
        return {dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second()};
    }

    uint32_t unixtime() override
    {
        DateTime dt = rtc.now();
        return dt.unixtime();
    }

    void adjust(const RtcDateTime &dt) override
    {
        rtc.adjust(DateTime(dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second));
    }

    bool begin() override
    {
        return rtc.begin();
    }
};

#endif // UNIT_TESTING