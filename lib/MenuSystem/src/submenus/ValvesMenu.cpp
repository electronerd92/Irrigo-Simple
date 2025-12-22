#include "ValvesMenu.h"
#include "core/MenuItems.hpp"
#include <interfaces/IWateringValve.h>

ValvesMenu::ValvesMenu(Menu *menu) : EditableMenuObj(menu, (uint8_t)ValvesMenuIndex::ELEMENT_COUNT)
{
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
    case ValvesMenuIndex::VALVE_MODE:
        handleFieldSelection(EditingField::First);
        break;

    default:
        break;
    }
}

void ValvesMenu::handleDirectionalCommand(Command cmd)
{
    const auto currentIndex = static_cast<ValvesMenuIndex>(menu->getElementIndex());
    ISystemManager *sysManager = menu->getSystemManager();

    switch (currentIndex)
    {
    case ValvesMenuIndex::SELECTED_VALVE:
        executeDirectionalEdit(cmd, [sysManager]()
                               { sysManager->incrementSelectedValve(); }, [sysManager]()
                               { sysManager->decreaseSelectedValve(); }, true);
        break;
    case ValvesMenuIndex::VALVE_MODE:
        executeDirectionalEdit(cmd, [sysManager]()
                               { sysManager->incrementValveMode(); }, [sysManager]()
                               { sysManager->decreaseValveMode(); });
        break;
    default:
        break;
    }
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
        printBackElement(F(VALVES_STR), row);
        break;
    case ValvesMenuIndex::SELECTED_VALVE:
        printSelectedValve(index, row);
        break;
    case ValvesMenuIndex::VALVE_MODE:
        printValveMode(index, row);
        break;
    default:
        break;
    }
}

void ValvesMenu::printSelectedValve(uint8_t index, uint8_t row)
{
    IDisplay *dispay = menu->getDispay();
    ISystemManager *sysManager = menu->getSystemManager();
    dispay->printAt(F(SELECTED_VALVE_STR), 1, row);
    char *lcdBuffer = menu->getDisplayBuffer();
    snprintf(lcdBuffer, menu->getDisplayBufferSize(), "[%u]", sysManager->getSelectedValve() + 1);
    handleElementDisplay(index, lcdBuffer, dispay->getColumns() - 3, row);
}

void ValvesMenu::printValveMode(uint8_t index, uint8_t row)
{
    IDisplay *dispay = menu->getDispay();
    ISystemManager *sysManager = menu->getSystemManager();
    dispay->printAt(F(VALVE_MODE_STR), 1, row);
    char *lcdBuffer = menu->getDisplayBuffer();
    snprintf(lcdBuffer, menu->getDisplayBufferSize(), "[%s]", valveModeToString(sysManager->getValveMode()));
    handleElementDisplay(index, lcdBuffer, dispay->getColumns() - strlen(lcdBuffer), row);
}