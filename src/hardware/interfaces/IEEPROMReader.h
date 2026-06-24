#pragma once
#include <Arduino.h>

class IEEPROMReader
{
public:
    virtual uint8_t readByte() = 0;
    virtual uint32_t readUInt32() = 0;

    template <typename T>
    T readEnum()
    {
        return static_cast<T>(readByte());
    }

    virtual void seek(uint16_t address) = 0;
};