#ifndef RTC_H
#define RTC_H

#include "interfaces/IRtc.h"

class Rtc : public IRtc
{
private:
    RTC_DS3231 rtc;

public:
    Rtc() : rtc() {}

    DateTime now() override
    {
        return rtc.now();
    }

    void adjust(const DateTime &dt) override
    {
        rtc.adjust(dt);
    }

    bool begin() override
    {
        return rtc.begin();
    }
};

#endif // RTC_H