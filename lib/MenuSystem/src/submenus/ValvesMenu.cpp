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
    case ValvesMenuIndex::FREQUENCY:
        handleFieldSelection(EditingField::First);
        break;
    case ValvesMenuIndex::DURATION:
        handleFieldSelection(EditingField::First);
        break;
    case ValvesMenuIndex::START_TIME:
        handleFieldSelection(EditingField::Second);
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
                               { sysManager->incrementSelectedValveMode(); }, [sysManager]()
                               { sysManager->decreaseSelectedValveMode(); });
        break;
    case ValvesMenuIndex::FREQUENCY:
        executeDirectionalEdit(cmd, [sysManager]()
                               { sysManager->incrementSelectedValveFrequency(); }, [sysManager]()
                               { sysManager->decreaseSelectedValveFrequency(); });
        break;
    case ValvesMenuIndex::DURATION:
        executeDirectionalEdit(cmd, [sysManager]()
                               { sysManager->incrementSelectedValveDuration(); }, [sysManager]()
                               { sysManager->decreaseSelectedValveDuration(); });
        break;
    case ValvesMenuIndex::START_TIME:
        handleStartTimeEditing(cmd);
        break;

    default:
        break;
    }
}

void ValvesMenu::handleStartTimeEditing(Command cmd)
{
    const EditingField editingField = menu->getEditingField();
    ISystemManager *sysManager = menu->getSystemManager();

    switch (editingField)
    {
    case EditingField::First:
        executeDirectionalEdit(cmd, [sysManager]()
                               { sysManager->incrementSelectedValveStartHour(); }, [sysManager]()
                               { sysManager->decreaseSelectedValveStartHour(); });
        break;

    case EditingField::Second:
        executeDirectionalEdit(cmd, [sysManager]()
                               { sysManager->incrementSelectedValveStartMinute(); }, [sysManager]()
                               { sysManager->decreaseSelectedValveStartMinute(); });
        break;

    default:
        return; // Don't update blinker for invalid field
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
    case ValvesMenuIndex::FREQUENCY:
        printFrequency(index, row);
        break;
    case ValvesMenuIndex::DURATION:
        printDuration(index, row);
        break;
    case ValvesMenuIndex::START_TIME:
        printStartTime(index, row);
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
    snprintf(lcdBuffer, menu->getDisplayBufferSize(), "[%s]", valveModeToString(sysManager->getSelectedValveMode()));
    handleElementDisplay(index, lcdBuffer, dispay->getColumns() - strlen(lcdBuffer), row);
}

void ValvesMenu::printFrequency(uint8_t index, uint8_t row)
{
    IDisplay *dispay = menu->getDispay();
    ISystemManager *sysManager = menu->getSystemManager();
    dispay->printAt(F(FREQUENCY_STR), 1, row);
    char *lcdBuffer = menu->getDisplayBuffer();
    snprintf(lcdBuffer, menu->getDisplayBufferSize(), "%luh", sysManager->getSelectedValveFrequency() / 3600UL);
    handleElementDisplay(index, lcdBuffer, dispay->getColumns() - strlen(lcdBuffer), row);
}

void ValvesMenu::printDuration(uint8_t index, uint8_t row)
{
    IDisplay *dispay = menu->getDispay();
    ISystemManager *sysManager = menu->getSystemManager();
    dispay->printAt(F(DURATION_STR), 1, row);
    char *lcdBuffer = menu->getDisplayBuffer();
    snprintf(lcdBuffer, menu->getDisplayBufferSize(), "%lumin", sysManager->getSelectedValveDuration() / 60UL);
    handleElementDisplay(index, lcdBuffer, dispay->getColumns() - strlen(lcdBuffer), row);
}

void ValvesMenu::printStartTime(uint8_t index, uint8_t row)
{
    IDisplay *dispay = menu->getDispay();
    ISystemManager *sysManager = menu->getSystemManager();
    dispay->printAt(F(START_TIME_STR), 1, row);

    uint8_t hour = sysManager->getSelectedValveStartHour();
    uint8_t minute = sysManager->getSelectedValveStartMinute();

    char *lcdBuffer = menu->getDisplayBuffer();
    snprintf(lcdBuffer, menu->getDisplayBufferSize(), "%02u:%02u", hour, minute);

    handleElementDisplay(index, lcdBuffer, dispay->getColumns() - 5, row);
}