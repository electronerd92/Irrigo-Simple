#pragma once
#include <Arduino.h>

class IEEPROMWriter
{
public:
    virtual void writeByte(uint8_t value) = 0;
    virtual void writeUInt32(uint32_t value) = 0;
    virtual void writeEnum(uint8_t value) = 0;
    virtual void seek(uint16_t address) = 0;
};