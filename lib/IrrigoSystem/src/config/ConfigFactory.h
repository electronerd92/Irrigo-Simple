#pragma once
#include "Config.h"
#include "MenuConfig.h"
#include "WateringSysConfig.h"

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

    static WateringSysConfig createWateringSysConfig()
    {
        WateringSysConfig config;

        config.valveOn = VALVE_ON;
        config.pumpOn = PUMP_ON;

        config.valvePumpDelay = VALVE_PUMP_DELAY;

        config.wateringValvesCount = WATERING_VALVES_COUNT;

        config.valvePinout.valve1 = PIN_VALVE_1;
        config.valvePinout.valve2 = PIN_VALVE_2;
        config.valvePinout.valve3 = PIN_VALVE_3;
        config.valvePinout.valve4 = PIN_VALVE_4;
        config.valvePinout.valveOut5 = PIN_VALVE_5;
        config.valvePinout.valveOut6 = PIN_VALVE_6;
        config.valvePinout.valveOut7 = PIN_VALVE_7;
        config.valvePinout.valveOut8 = PIN_VALVE_8;
        config.valvePinout.valveMainWater = PIN_VALVE_MAIN_WATER;
        config.valvePinout.valveOut = PIN_VALVE_OUT;
        config.valvePinout.valveTank = PIN_VALVE_TANK;
        return config;
    }
};