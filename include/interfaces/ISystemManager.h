#ifndef ISYSTEMMANAGER_H
#define ISYSTEMMANAGER_H

class DateTime;

class ISystemManager
{
public:
    virtual DateTime getDateTime() = 0;
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

#endif // ISYSTEMMANAGER_H