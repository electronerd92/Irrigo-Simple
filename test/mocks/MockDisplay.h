#ifndef MOCK_DISPLAY_H
#define MOCK_DISPLAY_H

#include <interfaces/IDisplay.h>

class MockDisplay : public IDisplay
{
private:
    const uint8_t rows;
    const uint8_t columns;
    bool cleared;
    uint8_t clearedColumn;
    uint8_t clearedCharCol, clearedCharRow;
    uint8_t clearedWordLength, clearedWordStartCol, clearedWordRow;
    char lastPrintedChar;
    char lastCharAt;
    uint8_t lastCharAtCol, lastCharAtRow;
    String lastPrintedString;
    String lastPrintedAtString;
    uint8_t lastPrintAtCol, lastPrintAtRow;
    PrintFormat lastPrintFormat;

public:
    MockDisplay(uint8_t r = 4, uint8_t c = 20)
        : rows(r), columns(c), cleared(false), clearedColumn(255),
          clearedCharCol(255), clearedCharRow(255), clearedWordLength(0),
          clearedWordStartCol(255), clearedWordRow(255), lastPrintedChar(0),
          lastCharAt(0), lastCharAtCol(255), lastCharAtRow(255),
          lastPrintAtCol(255), lastPrintAtRow(255), lastPrintFormat(PrintFormat::NONE) {}

    // Interface implementation
    uint8_t getColumns() const override { return columns; }
    uint8_t getRows() const override { return rows; }
    void clear() override { cleared = true; }
    void clearColumn(uint8_t col) override { clearedColumn = col; }
    void clearChar(uint8_t col, uint8_t row) override
    {
        clearedCharCol = col;
        clearedCharRow = row;
    }
    void clearWord(uint8_t wordLength, uint8_t startCol, uint8_t row) override
    {
        clearedWordLength = wordLength;
        clearedWordStartCol = startCol;
        clearedWordRow = row;
    }
    void printChar(char c) override { lastPrintedChar = c; }
    void print(const char *str) override { lastPrintedString = String(str); }
    void print(const __FlashStringHelper *str) override { lastPrintedString = String(str); }
    void printCharAt(char c, uint8_t col, uint8_t row) override
    {
        lastCharAt = c;
        lastCharAtCol = col;
        lastCharAtRow = row;
    }
    void printAt(const char *str, uint8_t col, uint8_t row, PrintFormat format = PrintFormat::NONE) override
    {
        lastPrintedAtString = String(str);
        lastPrintAtCol = col;
        lastPrintAtRow = row;
        lastPrintFormat = format;
    }
    void printAt(const __FlashStringHelper *str, uint8_t col, uint8_t row, PrintFormat format = PrintFormat::NONE) override
    {
        lastPrintedAtString = String(str);
        lastPrintAtCol = col;
        lastPrintAtRow = row;
        lastPrintFormat = format;
    }

    // Test helper methods
    bool wasCleared() const { return cleared; }
    uint8_t getClearedColumn() const { return clearedColumn; }
    uint8_t getClearedCharCol() const { return clearedCharCol; }
    uint8_t getClearedCharRow() const { return clearedCharRow; }
    uint8_t getClearedWordLength() const { return clearedWordLength; }
    uint8_t getClearedWordStartCol() const { return clearedWordStartCol; }
    uint8_t getClearedWordRow() const { return clearedWordRow; }
    char getLastPrintedChar() const { return lastPrintedChar; }
    String getLastPrintedString() const { return lastPrintedString; }
    char getLastCharAt() const { return lastCharAt; }
    uint8_t getLastCharAtCol() const { return lastCharAtCol; }
    uint8_t getLastCharAtRow() const { return lastCharAtRow; }
    String getLastPrintedAtString() const { return lastPrintedAtString; }
    uint8_t getLastPrintAtCol() const { return lastPrintAtCol; }
    uint8_t getLastPrintAtRow() const { return lastPrintAtRow; }
    PrintFormat getLastPrintFormat() const { return lastPrintFormat; }

    void resetFlags()
    {
        cleared = false;
        clearedColumn = 255;
        clearedCharCol = 255;
        clearedCharRow = 255;
        clearedWordLength = 0;
        clearedWordStartCol = 255;
        clearedWordRow = 255;
        lastPrintedChar = 0;
        lastCharAt = 0;
        lastCharAtCol = 255;
        lastCharAtRow = 255;
        lastPrintedString = "";
        lastPrintedAtString = "";
        lastPrintAtCol = 255;
        lastPrintAtRow = 255;
        lastPrintFormat = PrintFormat::NONE;
    }
};

#endif // MOCK_DISPLAY_H