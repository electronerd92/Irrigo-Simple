#include "EditMenu.h"

EditMenu::EditMenu(Menu *menu) : MenuObj(menu, elementCount)
{
}

void EditMenu::executeCmd(Command cmd)
{
}

void EditMenu::printElement(uint8_t index, uint8_t row)
{
    Lcd *lcd = menu->getLcd();
    switch (index)
    {
    case timeIndex:
        lcd->print(F("Time"));
        break;

    default:
        break;
    }
}