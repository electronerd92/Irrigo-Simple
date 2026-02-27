#pragma once
#ifndef UNIT_TESTING // Only compile for real hardware

#include <Arduino.h>
#include <EEPROM.h>
#include <interfaces/IEEPROMReader.h>

/**
 * @brief Arduino EEPROM reader implementation
 *
 * Uses real Arduino EEPROM library for production code.
 */
class ArduinoEEPROMReader : public IEEPROMReader
{
private:
    uint16_t currentAddr;

public:
    explicit ArduinoEEPROMReader(uint16_t startAddr = 0)
        : currentAddr(startAddr) {}

    uint8_t readByte() override
    {
        return EEPROM.read(currentAddr++);
    }

    uint16_t readUInt16() override
    {
        uint16_t low = readByte();
        uint16_t high = readByte();
        return (high << 8) | low;
    }

    uint32_t readUInt32() override
    {
        uint32_t byte0 = readByte();
        uint32_t byte1 = readByte();
        uint32_t byte2 = readByte();
        uint32_t byte3 = readByte();
        return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    bool readBool() override
    {
        return readByte() != 0;
    }

    void readBlock(uint8_t *data, uint16_t length) override
    {
        for (uint16_t i = 0; i < length; i++)
        {
            data[i] = EEPROM.read(currentAddr++);
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