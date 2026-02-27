#pragma once
#include <Arduino.h>
class IEEPROMWriter;
class IEEPROMReader;

class IPersistable
{
public:
    virtual void save(IEEPROMWriter &writer) const = 0;
    virtual void load(IEEPROMReader &reader) = 0;
    virtual uint16_t getSerializedSize() const = 0;
};