#pragma once
#include <Arduino.h>

/**
 * @brief Interface for EEPROM write operations
 *
 * Abstracts EEPROM writing to enable testing without hardware.
 * Business objects use this interface in their save() methods.
 */
class IEEPROMWriter
{
public:
    virtual ~IEEPROMWriter() = default;

    /**
     * @brief Write a single byte
     * @param value Byte to write
     */
    virtual void writeByte(uint8_t value) = 0;

    /**
     * @brief Write a 16-bit unsigned integer
     * @param value Value to write
     */
    virtual void writeUInt16(uint16_t value) = 0;

    /**
     * @brief Write a 32-bit unsigned integer
     * @param value Value to write
     */
    virtual void writeUInt32(uint32_t value) = 0;

    /**
     * @brief Write a boolean value
     * @param value Boolean to write
     */
    virtual void writeBool(bool value) = 0;

    /**
     * @brief Write an enum value (as uint8_t)
     * @param value Enum value to write
     */
    virtual void writeEnum(uint8_t value) = 0;

    /**
     * @brief Write a block of data
     * @param data Pointer to data
     * @param length Number of bytes
     */
    virtual void writeBlock(const uint8_t *data, uint16_t length) = 0;

    /**
     * @brief Get current write address
     * @return uint16_t Current address
     */
    virtual uint16_t getAddress() const = 0;

    /**
     * @brief Skip bytes (for padding/alignment)
     * @param bytes Number of bytes to skip
     */
    virtual void skip(uint16_t bytes) = 0;

    /**
     * @brief Seek to specific address
     * @param address Target address
     */
    virtual void seek(uint16_t address) = 0;
};