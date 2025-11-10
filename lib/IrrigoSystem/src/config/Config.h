#pragma once
#include <Arduino.h>

// Define LCD parameters
#define LCD_ADDRESS 0x27;
#define LCD_COLUMNS 20;
#define LCD_ROWS 4;
#define LCD_TIME_ON 60000;        // ms
#define LCD_BLINK_INTERVAL 500;   // ms
#define LCD_BLINK_BUFFER_SIZE 12; // 8 character buffer size + '\0'

#define BUFFER_SIZE 20

// Define pinout for the rotary
#define ROTARY_PIN_A 3;
#define ROTARY_PIN_B 2;
#define ROTARY_BUTTON_PIN 4;

// Define watering system parameters

#define VALVE_ON LOW;
#define PUMP_ON LOW;

#define WATERING_VALVES_COUNT 8;

#define PIN_VALVE_1 10;
#define PIN_VALVE_2 11;
#define PIN_VALVE_3 12;
#define PIN_VALVE_4 13;
#define PIN_VALVE_5 14;
#define PIN_VALVE_6 15;
#define PIN_VALVE_7 16;
#define PIN_VALVE_8 17;

#define PIN_VALVE_MAIN_WATER 19;
#define PIN_VALVE_OUT 20;
#define PIN_VALVE_TANK 21;