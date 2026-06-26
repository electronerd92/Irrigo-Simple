#pragma once

#include "systems/ui/MenuObj.hpp"

class ConfirmMenu : public MenuObj
{
private:
    MenuObj *previous{nullptr};
    uint8_t previousIndex{0};

    const __FlashStringHelper *title;

    bool result{false};
    bool done{false};

    void handleSelect();

public:
    ConfirmMenu(Menu &menu);

    void setContext(MenuObj &prev, const __FlashStringHelper *text);

    bool isDone() const { return done; }
    bool getResult() const { return result; }

    void reset();

    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};