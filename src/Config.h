#ifndef CONFIG_H
#define CONFIG_H

// Define LCD parameters
const uint8_t LCD_ADDRESS = 0x27;
const uint8_t LCD_COLUMNS = 20;
const uint8_t LCD_ROWS = 4;
const unsigned long LCD_TIME_ON = 60000;      // ms
const unsigned long LCD_BLINK_INTERVAL = 500; // ms
const uint8_t LCD_BLINK_BUFFER_SIZE = 9;      // 8 character buffer size + '\0'

// Define pinout for the rotary
const uint8_t ROTARY_PIN_A = 3;
const uint8_t ROTARY_PIN_B = 2;
const uint8_t ROTARY_BUTTON_PIN = 4;

#endif // PROJECT_CONFIG_H