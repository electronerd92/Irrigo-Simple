#include "EditableMenuObj.h"

EditableMenuObj::EditableMenuObj(Menu &menu, uint8_t count)
    : MenuObj(menu, count)
{
}

void EditableMenuObj::handleFieldSelection(uint8_t lastField)
{
    uint8_t f = menu.getEditingField();

    if (f == 0) // not editing yet
    {
        menu.nextField(); // go to first field
        updateBlinker = true;
    }
    else if (f == lastField)
    {
        menu.stopEditing(); // exit only at last field
    }
    else
    {
        menu.nextField(); // go to next field
        updateBlinker = true;
    }

    menu.requestRefresh(false);
}

void EditableMenuObj::handleElementDisplay(uint8_t index,
                                           const char *buffer,
                                           uint8_t col,
                                           uint8_t row)
{
    auto &display = menu.getDisplay();
    auto &blinker = menu.getBlinker();

    if (updateBlinker && menu.isEditing(index))
    {
        blinker.stopBlinking();
        blinker.startBlinking(buffer, col, row);
        updateBlinker = false;
    }
    else if (!menu.isEditing(index))
    {
        display.setCursor(col, row);
        display.print(buffer);
    }
}

void EditableMenuObj::requestBlinkerUpdate(bool forceRefresh)
{
    updateBlinker = true;
    menu.requestRefresh(forceRefresh);
}