#include "ActionsMenu.h"

ActionsMenu::ActionsMenu(Menu &menu)
    : MenuObj(menu, static_cast<uint8_t>(ActionsMenuIndex::ELEMENT_COUNT))
{
}

void ActionsMenu::setMainMenu(MenuObj &m)
{
    mainMenu = &m;
}

void ActionsMenu::setValveTestMenu(MenuObj &m)
{
    valveTestMenu = &m;
}

void ActionsMenu::executeCmd(Command cmd)
{
    if (cmd != Command::SELECT)
        return;

    handleSelect();
}

void ActionsMenu::handleSelect()
{
    switch (static_cast<ActionsMenuIndex>(menu.getSelectedIndex()))
    {
    case ActionsMenuIndex::BACK:
        menu.setCurrentMenu(*mainMenu, static_cast<uint8_t>(MainMenuIndex::ACTIONS));
        break;

    case ActionsMenuIndex::VALVE_TEST:
        menu.setCurrentMenu(*valveTestMenu);
        break;

    default:
        break;
    }
}

void ActionsMenu::printElement(uint8_t index, uint8_t row)
{
    auto &display = menu.getDisplay();

    display.setCursor(1, row);

    switch (static_cast<ActionsMenuIndex>(index))
    {
    case ActionsMenuIndex::BACK:
        printBackElement(F("Actions"), row);
        break;

    case ActionsMenuIndex::VALVE_TEST:
        printNextMenu(F("Valve Test"), row);
        break;

    default:
        break;
    }
}