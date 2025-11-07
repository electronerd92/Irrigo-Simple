#pragma once

class RtcDateTime;

class ISystemManager
{
public:
    virtual void update() = 0;
    virtual RtcDateTime getDateTime() = 0;
    virtual void incrementDay() = 0;
    virtual void decreaseDay() = 0;
    virtual void incrementMonth() = 0;
    virtual void decreaseMonth() = 0;
    virtual void incrementYear() = 0;
    virtual void decreaseYear() = 0;
    virtual void incrementHour() = 0;
    virtual void decreaseHour() = 0;
    virtual void incrementMinute() = 0;
    virtual void decreaseMinute() = 0;
};