#include "Blinker.h"

Blinker::Blinker(IDisplay &display)
    : display(display),
      blinkTimer(blinkIntervalMs)
{
    buffer[0] = '\0';
}

void Blinker::startBlinking(const char *word, uint8_t c, uint8_t r)
{
    size_t len = strlen(word);
    wordLength = (len < bufferSize - 1) ? len : (bufferSize - 1);
    memcpy(buffer, word, wordLength);
    buffer[wordLength] = '\0';

    col = c;
    row = r;

    blinkState = true;
    isBlinking = true;
    blinkTimer.start();

    printWord(); // show immediately
}

void Blinker::stopBlinking()
{
    if (!isBlinking)
        return;

    isBlinking = false;
    clearWord();
}

void Blinker::update()
{
    if (!isBlinking)
        return;

    if (blinkTimer.timeout())
    {
        if (blinkState)
            clearWord();
        else
            printWord();

        blinkState = !blinkState;
        blinkTimer.start();
    }
}

bool Blinker::getIsBlinking() const
{
    return isBlinking;
}

void Blinker::printWord()
{
    display.setCursor(col, row);
    display.print(buffer);
}

void Blinker::clearWord()
{
    for (uint8_t i = 0; i < wordLength; ++i)
    {
        display.clearChar(col + i, row);
    }
}