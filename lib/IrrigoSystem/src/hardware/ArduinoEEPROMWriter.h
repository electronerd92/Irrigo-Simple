#pragma once
#ifndef UNIT_TESTING // Only compile for real hardware

#include <Arduino.h>
#include <EEPROM.h>
#include <interfaces/IEEPROMWriter.h>

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

    void writeUInt16(uint16_t value) override
    {
        writeByte(value & 0xFF);
        writeByte((value >> 8) & 0xFF);
    }

    void writeUInt32(uint32_t value) override
    {
        writeByte(value & 0xFF);
        writeByte((value >> 8) & 0xFF);
        writeByte((value >> 16) & 0xFF);
        writeByte((value >> 24) & 0xFF);
    }

    void writeBool(bool value) override
    {
        writeByte(value ? 1 : 0);
    }

    void writeEnum(uint8_t value) override
    {
        writeByte(value);
    }

    void writeBlock(const uint8_t *data, uint16_t length) override
    {
        for (uint16_t i = 0; i < length; i++)
        {
            EEPROM.update(currentAddr++, data[i]);
        }
    }

    uint16_t getAddress() const override
    {
        return currentAddr;
    }

    void skip(uint16_t bytes) override
    {
        currentAddr += bytes;
    }

    void seek(uint16_t address) override
    {
        currentAddr = address;
    }
};

#endif // UNIT_TESTING