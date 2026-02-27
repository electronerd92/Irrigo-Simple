#pragma once
#include <Arduino.h>
#include <interfaces/IPersistenceManager.h>
#include <interfaces/IEEPROMWriter.h>
#include <interfaces/IEEPROMReader.h>
#include <interfaces/IPersistable.h>

class PersistenceManager : public IPersistenceManager
{
private:
    static constexpr uint8_t EEPROM_VERSION_HIGH = 1;
    static constexpr uint8_t EEPROM_VERSION_LOW = 0;
    static constexpr uint16_t EEPROM_START_ADDR = 0;

    IEEPROMWriter *writer;
    IEEPROMReader *reader;
    IPersistable **persistables;
    uint8_t persistableCount;

    uint8_t calculateChecksum(uint16_t startAddr, uint16_t length);
    bool validateChecksum(uint16_t dataSize);
    bool isValidVersion();

public:
    PersistenceManager(IEEPROMWriter *w, IEEPROMReader *r,
                       IPersistable **objects, uint8_t count);

    bool save() override;
    bool load() override;
    void reset() override;
    uint16_t getTotalSize() const override;
    bool isValid() override;
};