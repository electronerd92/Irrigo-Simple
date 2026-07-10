#pragma once
#include <Arduino.h>

/* =========================================================
 *  Project Info
 * ========================================================= */
#define PROJECT_NAME "Irrigo"
#define PROJECT_VERSION "1.0.0"
#define RELEASE_DATE "24/06/2026"

/* =========================================================
 *  Menu LCD Configuration
 * ========================================================= */
constexpr uint8_t I2C_ADDR_LCD = 0x27;
constexpr uint8_t LCD_COLUMNS = 20;
constexpr uint8_t LCD_ROWS = 4;
constexpr uint32_t MENU_SLEEP_MS = 60000; // Time in milliseconds before the menu goes to sleep

/* =========================================================
 *  Rotary Encoder Configuration
 * ========================================================= */
constexpr uint8_t ROTARY_PIN_A = 3;
constexpr uint8_t ROTARY_PIN_B = 2;
constexpr uint8_t ROTARY_BUTTON_PIN = 4;

/* =========================================================
 *  Watering System
 * ========================================================= */

constexpr uint8_t VALVE_COUNT = 8;

// Valves (1..4 indoor, 5..8 outdoor)
constexpr uint8_t VALVE_PINS[VALVE_COUNT] = {5, 6, 7, 8, 9, 10, 11, 12};

// Outdoor shared valve
constexpr uint8_t OUTDOOR_VALVE_PIN = 13;

// Pump
constexpr uint8_t PUMP_PIN = A2;

// Tank sensor
constexpr uint8_t TANK_LOW_LEVEL_PIN = A1;

// Logic levels
constexpr bool VALVE_ON = HIGH;
constexpr bool PUMP_ON = HIGH;

// Tank sensor logic
constexpr bool TANK_HAS_WATER = HIGH;

// Delay between valve and pump (ms)
constexpr uint32_t VALVE_PUMP_DELAY_MS = 500;

/* =========================================================
 *  RGB LED Configuration
 * ========================================================= */

constexpr uint8_t LED_RED_PIN = A3;
constexpr uint8_t LED_GREEN_PIN = A4;
constexpr uint8_t LED_BLUE_PIN = A5;