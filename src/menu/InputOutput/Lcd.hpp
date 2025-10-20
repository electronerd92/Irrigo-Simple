#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "../../Config.h"

enum class PrintFormat : byte
{
    NONE,
    TITLE_WITH_BACK,
    WITH_NEXT
};

class Lcd
{
private:
    LiquidCrystal_I2C lcd;

public:
    inline Lcd() : lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS)
    {
        lcd.init();
        lcd.backlight();
    }

    template <typename T>
    inline void print(const T &message, uint8_t col, uint8_t row, PrintFormat format = PrintFormat::NONE)
    {
        lcd.setCursor(col, row);
        switch (format)
        {
        case PrintFormat::NONE:
            lcd.print(message);
            break;

        case PrintFormat::TITLE_WITH_BACK:
            lcd.write('[');
            lcd.print(message);
            lcd.write(']');
            lcd.setCursor(LCD_COLUMNS - 1, row);
            lcd.write('^');
            break;
        case PrintFormat::WITH_NEXT:
            lcd.print(message);
            lcd.setCursor(LCD_COLUMNS - 1, row);
            lcd.write('>');
            break;

        default:
            break;
        }
    }

    template <typename T>
    inline void print(const T &message)
    {
        lcd.print(message);
    }

    inline void clear()
    {
        lcd.clear();
    }

    inline void clearChar(uint8_t col, uint8_t row)
    {
        print(F(" "), col, row);
    }

    inline void clearWord(uint8_t wordLength, uint8_t startCol, uint8_t row)
    {
        lcd.setCursor(startCol, row);
        for (uint8_t c = 0; c < wordLength; c++)
        {
            lcd.print(F(" "));
        }
    }

    inline void clearColumn(uint8_t col)
    {
        for (uint8_t r = 0; r < LCD_ROWS; ++r)
        {
            clearChar(col, r);
        }
    }
};

#endif // LCD_H