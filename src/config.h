#pragma once
#include <Arduino.h>

/* =========================================================
 *  LCD Configuration
 * ========================================================= */
constexpr uint8_t I2C_ADDR_LCD = 0x27;
constexpr uint8_t LCD_COLUMNS = 20;
constexpr uint8_t LCD_ROWS = 4;

/* =========================================================
 *  Rotary Encoder Configuration
 * ========================================================= */
constexpr uint8_t ROTARY_PIN_A = 3;
constexpr uint8_t ROTARY_PIN_B = 2;
constexpr uint8_t ROTARY_BUTTON_PIN = 4;
