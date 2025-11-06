#ifndef MOCK_DISPLAY_H
#define MOCK_DISPLAY_H

#include <interfaces/IDisplay.h>

class MockDisplay : public IDisplay
{
public:
    std::vector<std::string> printedChars;
    uint8_t rows = 4;
    uint8_t columns = 20;

    MockDisplay(uint8_t r = 4, uint8_t c = 20) : rows(r), columns(c) {}
    void clear() override { printedChars.clear(); }
    void clearColumn(uint8_t col) override { printedChars.clear(); }
    void clearChar(uint8_t, uint8_t) override {}
    void clearWord(uint8_t, uint8_t, uint8_t) override {}
    void printChar(char c) override { printedChars.push_back(std::string(1, c)); }
    void print(const char *) override {}
    void print(const __FlashStringHelper *) override {}
    void printCharAt(char c, uint8_t, uint8_t) override { printedChars.push_back(std::string(1, c)); }
    void printAt(const char *, uint8_t, uint8_t, PrintFormat = PrintFormat::NONE) override {}
    void printAt(const __FlashStringHelper *, uint8_t, uint8_t, PrintFormat = PrintFormat::NONE) override {}

    uint8_t getColumns() const override { return columns; }
    uint8_t getRows() const override { return rows; }
};

#endif // MOCK_DISPLAY_H