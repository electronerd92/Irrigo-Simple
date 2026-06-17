#pragma once
#ifndef UNIT_TESTING
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "interfaces/IDisplay.h"
#include "config.h"

class Lcd : public IDisplay
{
public:
    Lcd() : lcd(I2C_ADDR_LCD, LCD_COLUMNS, LCD_ROWS) {}

    void begin() override
    {
        lcd.init();
        lcd.backlight();
    }

    void clear() override { lcd.clear(); }

    void clearChar(uint8_t col, uint8_t row) override
    {
        setCursor(col, row);
        write(' ');
    }

    void setCursor(uint8_t col, uint8_t row) override
    {
        lcd.setCursor(col, row);
    }

    void write(char c) override
    {
        lcd.write(c);
    }

    void print(const char *str) override
    {
        lcd.print(str);
    }

    void print(const __FlashStringHelper *str) override
    {
        lcd.print(str);
    }

    uint8_t getColumns() const override { return LCD_COLUMNS; }
    uint8_t getRows() const override { return LCD_ROWS; }

private:
    LiquidCrystal_I2C lcd;
};

#endif // UNIT_TESTING