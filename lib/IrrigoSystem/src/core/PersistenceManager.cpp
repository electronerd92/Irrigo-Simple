#include "PersistenceManager.h"

PersistenceManager::PersistenceManager(IEEPROMWriter *w, IEEPROMReader *r,
                                       IPersistable **objects, uint8_t count)
    : writer(w), reader(r), persistables(objects), persistableCount(count) {}

bool PersistenceManager::save()
{
    if (!writer)
        return false;

    // Seek to start
    writer->seek(EEPROM_START_ADDR);

    // Write version header
    writer->writeByte(EEPROM_VERSION_HIGH);
    writer->writeByte(EEPROM_VERSION_LOW);

    uint16_t dataStartAddr = writer->getAddress();

    // Let each object save itself
    for (uint8_t i = 0; i < persistableCount; i++)
    {
        if (persistables[i])
        {
            persistables[i]->save(*writer);
        }
    }

    uint16_t dataEndAddr = writer->getAddress();
    uint16_t dataSize = dataEndAddr - dataStartAddr;

    // Calculate checksum of version + data
    uint8_t checksum = calculateChecksum(EEPROM_START_ADDR, 2 + dataSize);

    // Write checksum at end
    writer->writeByte(checksum);

    return true;
}

bool PersistenceManager::load()
{
    if (!reader)
        return false;

    // Validate version first
    if (!isValidVersion())
    {
        return false;
    }

    // Calculate expected data size
    uint16_t expectedSize = getTotalSize();

    // Validate checksum
    if (!validateChecksum(expectedSize))
    {
        return false;
    }

    // Seek past version header to start of data
    reader->seek(EEPROM_START_ADDR + 2);

    // Let each object load itself
    for (uint8_t i = 0; i < persistableCount; i++)
    {
        if (persistables[i])
        {
            persistables[i]->load(*reader);
        }
    }

    return true;
}

void PersistenceManager::reset()
{
    if (!writer)
        return;

    writer->seek(EEPROM_START_ADDR);
    writer->writeByte(0xFF); // Invalid version
    writer->writeByte(0xFF);
}

uint16_t PersistenceManager::getTotalSize() const
{
    uint16_t total = 0;
    for (uint8_t i = 0; i < persistableCount; i++)
    {
        if (persistables[i])
        {
            total += persistables[i]->getSerializedSize();
        }
    }
    return total;
}

bool PersistenceManager::isValid()
{
    if (!reader)
        return false;

    if (!isValidVersion())
    {
        return false;
    }

    uint16_t expectedSize = getTotalSize();
    return validateChecksum(expectedSize);
}

uint8_t PersistenceManager::calculateChecksum(uint16_t startAddr, uint16_t length)
{
    if (!reader)
        return 0;

    uint8_t checksum = 0;
    uint16_t savedAddr = reader->getAddress(); // Save current position

    reader->seek(startAddr);
    for (uint16_t i = 0; i < length; i++)
    {
        checksum ^= reader->readByte();
    }

    reader->seek(savedAddr); // Restore position
    return checksum;
}

bool PersistenceManager::validateChecksum(uint16_t dataSize)
{
    if (!reader)
        return false;

    // Checksum is stored after: version(2) + data(dataSize)
    uint16_t checksumAddr = EEPROM_START_ADDR + 2 + dataSize;

    // Read stored checksum
    uint16_t savedAddr = reader->getAddress();
    reader->seek(checksumAddr);
    uint8_t storedChecksum = reader->readByte();
    reader->seek(savedAddr);

    // Calculate checksum of version + data
    uint8_t calculatedChecksum = calculateChecksum(EEPROM_START_ADDR, 2 + dataSize);

    return storedChecksum == calculatedChecksum;
}

bool PersistenceManager::isValidVersion()
{
    if (!reader)
        return false;

    uint16_t savedAddr = reader->getAddress();

    reader->seek(EEPROM_START_ADDR);
    uint8_t high = reader->readByte();
    uint8_t low = reader->readByte();

    reader->seek(savedAddr);

    return (high == EEPROM_VERSION_HIGH && low == EEPROM_VERSION_LOW);
}