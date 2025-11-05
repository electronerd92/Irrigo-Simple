#ifndef MOCK_BLINKER_H
#define MOCK_BLINKER_H

#include <interfaces/IBlinker.h>

class MockBlinker : public IBlinker
{
private:
    bool isBlinking;
    String blinkingWord;
    uint8_t blinkingCol;
    uint8_t blinkingRow;
    uint8_t updateCount;

public:
    MockBlinker() : isBlinking(false), blinkingCol(0), blinkingRow(0), updateCount(0) {}

    void update() override { updateCount++; }
    bool getIsBlinking() const override { return isBlinking; }

    void startBlinking(const char *word, uint8_t c, uint8_t r) override
    {
        isBlinking = true;
        blinkingWord = String(word);
        blinkingCol = c;
        blinkingRow = r;
    }

    void stopBlinking() override
    {
        isBlinking = false;
        blinkingWord = "";
        blinkingCol = 0;
        blinkingRow = 0;
    }

    // Test helper methods
    void setBlinking(bool blinking) { isBlinking = blinking; }
    String getBlinkingWord() const { return blinkingWord; }
    uint8_t getBlinkingCol() const { return blinkingCol; }
    uint8_t getBlinkingRow() const { return blinkingRow; }
    uint8_t getUpdateCount() const { return updateCount; }
    void resetUpdateCount() { updateCount = 0; }
};

#endif // MOCK_BLINKER_H