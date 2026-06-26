#include "ConfirmMenu.h"

enum class ConfirmIndex : uint8_t
{
    TITLE,
    NO,
    YES,
    COUNT
};

ConfirmMenu::ConfirmMenu(Menu &menu)
    : MenuObj(menu, static_cast<uint8_t>(ConfirmIndex::COUNT))
{
}

void ConfirmMenu::setContext(MenuObj &prev, const __FlashStringHelper *text)
{
    previous = &prev;
    title = text;
    previousIndex = menu.getSelectedIndex(); // save current index
    reset();
}

void ConfirmMenu::reset()
{
    result = false;
    done = false;
}

void ConfirmMenu::executeCmd(Command cmd)
{
    if (cmd != Command::SELECT)
        return;

    if (menu.getSelectedIndex() == (uint8_t)ConfirmIndex::TITLE)
    {
        // Do nothing if title is selected
        return;
    }

    handleSelect();
}

void ConfirmMenu::handleSelect()
{
    auto idx = static_cast<ConfirmIndex>(menu.getSelectedIndex());

    if (idx == ConfirmIndex::YES)
        result = true;
    else
        result = false;

    done = true;

    // Go back
    if (previous)
        menu.setCurrentMenu(*previous, previousIndex);
}

void ConfirmMenu::printElement(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);

    switch (static_cast<ConfirmIndex>(index))
    {
    case ConfirmIndex::TITLE:
        d.print(title);
        break;

    case ConfirmIndex::NO:
        d.print(F("[No]"));
        break;

    case ConfirmIndex::YES:
        d.print(F("[Yes]"));
        break;

    default:
        break;
    }
}