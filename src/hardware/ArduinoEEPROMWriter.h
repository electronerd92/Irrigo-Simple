#pragma once
#ifndef UNIT_TESTING // Only compile for real hardware

#include <Arduino.h>
#include <EEPROM.h>
#include "interfaces/IEEPROMWriter.h"

/**
 * @brief Arduino EEPROM writer implementation
 *
 * Uses real Arduino EEPROM library for production code.
 */
class ArduinoEEPROMWriter : public IEEPROMWriter
{
private:
    uint16_t currentAddr;

public:
    explicit ArduinoEEPROMWriter(uint16_t startAddr = 0)
        : currentAddr(startAddr) {}

    void writeByte(uint8_t value) override
    {
        EEPROM.update(currentAddr++, value);
    }

    void writeUInt32(uint32_t value) override
    {
        writeByte(value & 0xFF);
        writeByte((value >> 8) & 0xFF);
        writeByte((value >> 16) & 0xFF);
        writeByte((value >> 24) & 0xFF);
    }

    void writeEnum(uint8_t value) override
    {
        writeByte(value);
    }

    void seek(uint16_t address) override
    {
        currentAddr = address;
    }
};

#endif // UNIT_TESTING