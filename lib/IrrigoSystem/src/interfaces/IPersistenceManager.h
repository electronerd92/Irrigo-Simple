#pragma once
#include <Arduino.h>

/**
 * @brief Interface for persistence management
 *
 * Abstracts persistence operations to enable testing without hardware.
 * Similar pattern to IRtc for RTC abstraction.
 */
class IPersistenceManager
{
public:
    virtual ~IPersistenceManager() = default;

    /**
     * @brief Save all persistent data to storage
     * @return true if save succeeded
     * @return false if save failed
     */
    virtual bool save() = 0;

    /**
     * @brief Load all persistent data from storage
     * @return true if load succeeded
     * @return false if load failed (corrupted, invalid version, etc.)
     */
    virtual bool load() = 0;

    /**
     * @brief Reset storage to factory defaults
     * Invalidates stored data, forcing defaults on next load
     */
    virtual void reset() = 0;

    /**
     * @brief Get total size of persistent data
     * @return uint16_t Size in bytes
     */
    virtual uint16_t getTotalSize() const = 0;

    /**
     * @brief Check if storage is valid
     * @return true if storage contains valid data
     * @return false if storage is corrupted or uninitialized
     */
    virtual bool isValid() = 0;
};