#pragma once

struct RtcDateTime
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

class IRtc
{
public:
    virtual RtcDateTime now() = 0;
    virtual void adjust(const RtcDateTime &dt) = 0;
    virtual bool begin() = 0; // For initialization
};