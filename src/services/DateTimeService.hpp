#pragma once
#include <Arduino.h>
#include "hardware/interfaces/IRtc.h"

class DateTimeService
{
public:
    explicit DateTimeService(IRtc &rtc)
        : rtc(rtc)
    {
    }

    // -------------------------------------------------
    // Read access (always from RTC)
    // -------------------------------------------------
    RtcDateTime get() const
    {
        return rtc.now();
    }

    uint32_t unixTime() const
    {
        return rtc.unixtime();
    }

    // -------------------------------------------------
    // Field-wise editing (direct RTC adjust)
    // -------------------------------------------------
    void incYear()
    {
        adjust([](RtcDateTime &dt)
               { dt.year++; });
    }
    void decYear()
    {
        adjust([](RtcDateTime &dt)
               { dt.year--; });
    }

    void incMonth()
    {
        adjust([this](RtcDateTime &dt)
               {
        wrap(dt.month, 1, 12, +1);
        clampDay(dt); });
    }

    void decMonth()
    {
        adjust([this](RtcDateTime &dt)
               {
        wrap(dt.month, 1, 12, -1);
        clampDay(dt); });
    }

    void incDay()
    {
        adjust([this](RtcDateTime &dt)
               { wrap(dt.day, 1, daysInMonth(dt), +1); });
    }

    void decDay()
    {
        adjust([this](RtcDateTime &dt)
               { wrap(dt.day, 1, daysInMonth(dt), -1); });
    }

    void incHour()
    {
        adjust([](RtcDateTime &dt)
               { wrap(dt.hour, 0, 23, +1); });
    }

    void decHour()
    {
        adjust([](RtcDateTime &dt)
               { wrap(dt.hour, 0, 23, -1); });
    }

    void incMinute()
    {
        adjust([](RtcDateTime &dt)
               {
        wrap(dt.minute, 0, 59, +1);
        dt.second = 0; });
    }

    void decMinute()
    {
        adjust([](RtcDateTime &dt)
               {
        wrap(dt.minute, 0, 59, -1);
        dt.second = 0; });
    }

private:
    IRtc &rtc;

    // -------------------------------------------------
    // Helpers
    // -------------------------------------------------
    template <typename Fn>
    void adjust(Fn fn)
    {
        RtcDateTime dt = rtc.now(); // read
        fn(dt);                     // modify
        rtc.adjust(dt);             // write
    }

    static void wrap(uint8_t &value,
                     uint8_t min,
                     uint8_t max,
                     int8_t delta)
    {
        int16_t v = static_cast<int16_t>(value) + delta;
        if (v < min)
            v = max;
        if (v > max)
            v = min;
        value = static_cast<uint8_t>(v);
    }

    static uint8_t daysInMonth(const RtcDateTime &dt)
    {
        const uint16_t y = dt.year;
        const uint8_t m = dt.month;

        if (m == 2)
        {
            if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
                return 29;
            return 28;
        }

        if (m == 4 || m == 6 || m == 9 || m == 11)
            return 30;

        return 31;
    }

    static void clampDay(RtcDateTime &dt)
    {
        uint8_t maxDay = daysInMonth(dt);
        if (dt.day > maxDay)
            dt.day = maxDay;
    }
};