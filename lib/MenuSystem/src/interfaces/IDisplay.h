#pragma once
#include <Arduino.h>

enum class PrintFormat : byte
{
    NONE,
    TITLE_WITH_BACK,
    WITH_NEXT
};

class IDisplay
{
public:
    virtual uint8_t getColumns() const = 0;
    virtual uint8_t getRows() const = 0;

    virtual void clear() = 0;
    virtual void clearColumn(uint8_t col) = 0;
    virtual void clearChar(uint8_t col, uint8_t row) = 0;
    virtual void clearWord(uint8_t wordLength, uint8_t startCol, uint8_t row) = 0;
    virtual void printChar(char c) = 0;
    virtual void print(const char *str) = 0;
    virtual void print(const __FlashStringHelper *str) = 0;
    virtual void printCharAt(char c, uint8_t col, uint8_t row) = 0;
    virtual void printAt(const char *str, uint8_t col, uint8_t row, PrintFormat format = PrintFormat::NONE) = 0;
    virtual void printAt(const __FlashStringHelper *str, uint8_t col, uint8_t row, PrintFormat format = PrintFormat::NONE) = 0;
};