#pragma once

#include <Arduino.h>
#include "MenuObj.hpp"

class EditableMenuObj : public MenuObj
{
protected:
    bool updateBlinker{false};

    void handleFieldSelection(uint8_t lastField);

    void handleElementDisplay(uint8_t index,
                              const char *buffer,
                              uint8_t col,
                              uint8_t row);

    void printBackElement(const __FlashStringHelper *title,
                          uint8_t row);

    template <typename Inc, typename Dec>
    void executeDirectionalEdit(Command cmd,
                                Inc inc,
                                Dec dec,
                                bool forceRefresh = false)
    {
        if (cmd == Command::RIGHT)
            inc();
        else if (cmd == Command::LEFT)
            dec();

        requestBlinkerUpdate(forceRefresh);
    }

    void requestBlinkerUpdate(bool forceRefresh);

public:
    EditableMenuObj(Menu &menu, uint8_t count);
};