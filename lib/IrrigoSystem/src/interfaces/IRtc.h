#ifndef I_RTC_H
#define I_RTC_H

#include <RTClib.h>

class IRtc
{
public:
    virtual DateTime now() = 0;
    virtual void adjust(const DateTime &dt) = 0;
    virtual bool begin() = 0; // For initialization
};

#endif // I_RTC_H