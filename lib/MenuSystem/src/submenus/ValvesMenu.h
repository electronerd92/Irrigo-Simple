#pragma once
#include <Arduino.h>
#include "core/MenuObj.hpp"

enum class ValvesMenuIndex : uint8_t
{
    BACK = 0,
    ELEMENT_COUNT
};

class ValvesMenu : public MenuObj
{
private:
public:
    ValvesMenu(Menu *menu);
    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};