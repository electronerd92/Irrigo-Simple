#include "Blinker.h"

Blinker::Blinker(IDisplay *dispay, const BlinkerConfig &config)
    : dispay(dispay),
      blinkTimer(config.blinkInterval),
      bufferSize(config.bufferSize),
      col(0),
      row(0),
      blinkState(false),
      isBlinking(false),
      wordLength(0)
{
    buffer = new char[bufferSize];
    buffer[0] = '\0'; // Initialize empty string
}
void Blinker::startBlinking(const char *word, uint8_t c, uint8_t r)
{
    wordLength = min((uint8_t)strlen(word), bufferSize - 1);
    strncpy(buffer, word, wordLength);
    buffer[wordLength] = '\0'; // Null-terminate
    col = c;
    row = r;
    blinkState = true;
    isBlinking = true;
    blinkTimer.start();
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
    if (isBlinking && blinkTimer.timeout())
    {
        if (blinkState)
        {
            clearWord();
        }
        else
        {
            printWord();
        }
        blinkState = !blinkState; // Toggle the blink state
        blinkTimer.start();       // Restart the blink timer
    }
}

bool Blinker::getIsBlinking() const
{
    return isBlinking;
}

void Blinker::printWord()
{
    dispay->printAt(buffer, col, row);
}

void Blinker::clearWord()
{
    dispay->clearWord(wordLength, col, row);
}
