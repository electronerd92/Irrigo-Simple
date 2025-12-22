#pragma once

#ifndef UNIT_TESTING

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <interfaces/IDisplay.h>
#include <MenuConfig.h>

class Lcd : public IDisplay
{
private:
    LiquidCrystal_I2C lcd;
    LcdConfig config;

public:
    Lcd(const LcdConfig &lcdConfig)
        : lcd(lcdConfig.address, lcdConfig.columns, lcdConfig.rows),
          config(lcdConfig)
    {
        lcd.init();
        lcd.backlight();
    }

    void clear() override
    {
        lcd.clear();
    }

    void clearColumn(uint8_t col) override
    {
        for (uint8_t r = 0; r < config.rows; ++r)
        {
            clearChar(col, r);
        }
    }

    void clearChar(uint8_t col, uint8_t row) override
    {
        printCharAt(' ', col, row);
    }

    void clearWord(uint8_t wordLength, uint8_t startCol, uint8_t row) override
    {
        lcd.setCursor(startCol, row);
        for (uint8_t c = 0; c < wordLength; c++)
        {
            printChar(' ');
        }
    }

    void printChar(char c) override
    {
        lcd.write(c);
    };

    void print(const char *str) override
    {
        templatePrint(str);
    };

    void print(const __FlashStringHelper *str) override
    {
        templatePrint(str);
    };

    void printCharAt(char c, uint8_t col, uint8_t row) override
    {
        lcd.setCursor(col, row);
        lcd.write(c);
    };

    void printAt(const char *str, uint8_t col, uint8_t row, PrintFormat format = PrintFormat::NONE) override
    {
        templatePrint(str, col, row, format);
    };

    void printAt(const __FlashStringHelper *str, uint8_t col, uint8_t row, PrintFormat format = PrintFormat::NONE) override
    {
        templatePrint(str, col, row, format);
    };

    // Getter methods for config values
    uint8_t getColumns() const override { return config.columns; }
    uint8_t getRows() const override { return config.rows; }

    /* #region Template convenience methods */
    template <typename T>
    inline void templatePrint(const T &message, uint8_t col, uint8_t row, PrintFormat format)
    {
        lcd.setCursor(col, row);
        switch (format)
        {
        case PrintFormat::NONE:
            lcd.print(message);
            break;

        case PrintFormat::WITH_SQUARE_BRACKETS:
            lcd.write('[');
            lcd.print(message);
            lcd.write(']');
            break;

        case PrintFormat::TITLE_WITH_BACK:
            lcd.write('[');
            lcd.print(message);
            lcd.write(']');
            lcd.setCursor(config.columns - 1, row);
            lcd.write('^');
            break;
        case PrintFormat::WITH_NEXT:
            lcd.print(message);
            lcd.setCursor(config.columns - 1, row);
            lcd.write('>');
            break;

        default:
            break;
        }
    }

    template <typename T>
    inline void templatePrint(const T &message)
    {
        lcd.print(message);
    }
    /* #endregion*/
};

#endif // UNIT_TESTING