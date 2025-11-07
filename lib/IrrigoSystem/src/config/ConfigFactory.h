#pragma once
#include "Config.h"
#include "MenuConfig.h"

class ConfigFactory
{
public:
    static MenuConfig createMenuConfig()
    {
        MenuConfig config;

        config.lcd.address = LCD_ADDRESS;
        config.lcd.columns = LCD_COLUMNS;
        config.lcd.rows = LCD_ROWS;
        config.lcd.timeOn = LCD_TIME_ON;
        config.lcd.blinkInterval = LCD_BLINK_INTERVAL;
        config.lcd.blinkBufferSize = LCD_BLINK_BUFFER_SIZE;

        config.rotary.pinA = ROTARY_PIN_A;
        config.rotary.pinB = ROTARY_PIN_B;
        config.rotary.buttonPin = ROTARY_BUTTON_PIN;

        config.blinker.blinkInterval = LCD_BLINK_INTERVAL;
        config.blinker.bufferSize = LCD_BLINK_BUFFER_SIZE;

        config.bufferSize = BUFFER_SIZE;

        return config;
    }
};