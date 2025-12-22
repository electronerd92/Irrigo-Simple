#pragma once

class IWateringSystem
{
public:
    virtual void update() = 0;
    virtual IWateringManager *getWateringManager() = 0;
};
