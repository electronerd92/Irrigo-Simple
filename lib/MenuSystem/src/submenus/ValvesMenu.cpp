#include "ValvesMenu.h"
#include "core/MenuItems.hpp"

ValvesMenu::ValvesMenu(Menu *menu) : MenuObj(menu, (uint8_t)ValvesMenuIndex::ELEMENT_COUNT)
{
    updateBlinker = false;
}

void ValvesMenu::executeCmd(Command cmd)
{
    switch (cmd)
    {
    case Command::SELECT:
        handleSelectCommand();
        break;

    case Command::LEFT:
    case Command::RIGHT:
        handleDirectionalCommand(cmd);
        break;

    default:
        // Handle any other commands if needed
        break;
    }
}

void ValvesMenu::handleSelectCommand()
{
    const auto currentIndex = static_cast<ValvesMenuIndex>(menu->getElementIndex());

    switch (currentIndex)
    {
    case ValvesMenuIndex::BACK:
        navigateToSettingsMenu();
        break;

    case ValvesMenuIndex::SELECTED_VALVE:
        handleFieldSelection(EditingField::First);
        break;

    default:
        break;
    }
}

void ValvesMenu::handleFieldSelection(EditingField lastField)
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

void ValvesMenu::handleDirectionalCommand(Command cmd)
{
    const auto currentIndex = static_cast<ValvesMenuIndex>(menu->getElementIndex());
    const bool isIncrement = (cmd == Command::RIGHT);
    ISystemManager *sysManager = menu->getSystemManager();

    switch (currentIndex)
    {
    case ValvesMenuIndex::SELECTED_VALVE:
        isIncrement ? sysManager->incrementSelectedValve() : sysManager->decreaseSelectedValve();
        break;
    default:
        break;
    }
    updateBlinker = true;
    menu->requestFullRefresh(false);
}

void ValvesMenu::navigateToSettingsMenu()
{
    menu->setCurrentMenu(
        menu->getMenuItems()->getSettingsMenu(),
        static_cast<uint8_t>(SettingsMenuIndex::VALVES));
}

void ValvesMenu::printElement(uint8_t index, uint8_t row)
{

    const auto menuIndex = static_cast<ValvesMenuIndex>(index);
    switch (menuIndex)
    {
    case ValvesMenuIndex::BACK:
        printBackElement(row);
        break;
    case ValvesMenuIndex::SELECTED_VALVE:
        printSelectedValve(index, row);
        break;
    default:
        break;
    }
}

void ValvesMenu::printBackElement(uint8_t row)
{
    menu->getDispay()->printAt(F(VALVES_STR), 1, row, PrintFormat::TITLE_WITH_BACK);
}

void ValvesMenu::printSelectedValve(uint8_t index, uint8_t row)
{
    IDisplay *dispay = menu->getDispay();
    ISystemManager *sysManager = menu->getSystemManager();
    dispay->printAt(F(SELECTED_VALVE_STR), 1, row);
    char *lcdBuffer = menu->getDisplayBuffer();
    snprintf(lcdBuffer, menu->getDisplayBufferSize(), "%u", sysManager->getSelectedValve() + 1);
    handleElementDisplay(index, lcdBuffer, dispay->getColumns() - 2, row);
}

void ValvesMenu::handleElementDisplay(uint8_t elementIndex, const char *buffer, uint8_t col, uint8_t row)
{
    if (updateBlinker && menu->getIsEditingElement(elementIndex))
    {
        menu->getBlinker()->stopBlinking();
        menu->getBlinker()->startBlinking(buffer, col, row);
        updateBlinker = false;
    }
    else if (!menu->getIsEditingElement(elementIndex))
    {
        menu->getDispay()->printAt(buffer, col - 1, row, PrintFormat::WITH_SQUARE_BRACKETS);
    }
}