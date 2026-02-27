#pragma once
#include <Arduino.h>

/**
 * @brief Interface for EEPROM read operations
 *
 * Abstracts EEPROM reading to enable testing without hardware.
 * Business objects use this interface in their load() methods.
 */
class IEEPROMReader
{
public:
    virtual ~IEEPROMReader() = default;

    /**
     * @brief Read a single byte
     * @return uint8_t Read value
     */
    virtual uint8_t readByte() = 0;

    /**
     * @brief Read a 16-bit unsigned integer
     * @return uint16_t Read value
     */
    virtual uint16_t readUInt16() = 0;

    /**
     * @brief Read a 32-bit unsigned integer
     * @return uint32_t Read value
     */
    virtual uint32_t readUInt32() = 0;

    /**
     * @brief Read a boolean value
     * @return bool Read value
     */
    virtual bool readBool() = 0;

    /**
     * @brief Read an enum value
     * @tparam T Enum type
     * @return T Enum value
     */
    template <typename T>
    T readEnum()
    {
        return static_cast<T>(readByte());
    }

    /**
     * @brief Read a block of data
     * @param data Pointer to buffer
     * @param length Number of bytes to read
     */
    virtual void readBlock(uint8_t *data, uint16_t length) = 0;

    /**
     * @brief Get current read address
     * @return uint16_t Current address
     */
    virtual uint16_t getAddress() const = 0;

    /**
     * @brief Skip bytes
     * @param bytes Number of bytes to skip
     */
    virtual void skip(uint16_t bytes) = 0;

    /**
     * @brief Seek to specific address
     * @param address Target address
     */
    virtual void seek(uint16_t address) = 0;
};