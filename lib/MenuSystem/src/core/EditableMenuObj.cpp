#include "EditableMenuObj.h"

EditableMenuObj::EditableMenuObj(Menu *menu, uint8_t elementsCount)
    : MenuObj(menu, elementsCount), updateBlinker(false)
{
}

void EditableMenuObj::handleFieldSelection(EditingField lastField)
{
    if (menu->getEditingField() == lastField)
    {
        menu->stopEditing();
    }
    else
    {
        updateBlinker = true;
        menu->incrementEditingField();
    }
    menu->requestFullRefresh(false);
}

void EditableMenuObj::handleElementDisplay(uint8_t elementIndex, const char *buffer,
                                           uint8_t col, uint8_t row, PrintFormat format)
{
    if (updateBlinker && menu->getIsEditingElement(elementIndex))
    {
        menu->getBlinker()->stopBlinking();
        menu->getBlinker()->startBlinking(buffer, col, row);
        updateBlinker = false;
    }
    else if (!menu->getIsEditingElement(elementIndex))
    {
        uint8_t colOffset = (format == PrintFormat::WITH_SQUARE_BRACKETS) ? 1 : 0;
        menu->getDispay()->printAt(buffer, col - colOffset, row, format);
    }
}

void EditableMenuObj::printBackElement(const __FlashStringHelper *title, uint8_t row)
{
    menu->getDispay()->printAt(title, 1, row, PrintFormat::TITLE_WITH_BACK);
}

void EditableMenuObj::requestBlinkerUpdate()
{
    updateBlinker = true;
    menu->requestFullRefresh(false);
}