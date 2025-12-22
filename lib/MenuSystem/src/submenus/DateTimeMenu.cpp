#include "DateTimeMenu.h"
#include "core/MenuItems.hpp"

DateTimeMenu::DateTimeMenu(Menu *menu) : EditableMenuObj(menu, (uint8_t)DateTimeMenuIndex::ELEMENT_COUNT)
{
}

void DateTimeMenu::executeCmd(Command cmd)
{
    switch (cmd)
    {
    case Command::NONE:
        handleNoCommand();
        break;

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

void DateTimeMenu::handleNoCommand()
{
    //? The time will be updated if not under edition
    menu->requestFullRefresh(false);
}

void DateTimeMenu::handleSelectCommand()
{
    const auto currentIndex = static_cast<DateTimeMenuIndex>(menu->getElementIndex());

    switch (currentIndex)
    {
    case DateTimeMenuIndex::BACK:
        navigateToSettingsMenu();
        break;

    case DateTimeMenuIndex::DATE:
        handleFieldSelection(EditingField::Third);
        break;

    case DateTimeMenuIndex::TIME:
        handleFieldSelection(EditingField::Second);
        break;

    default:
        break;
    }
}

void DateTimeMenu::handleDirectionalCommand(Command cmd)
{
    const auto currentIndex = static_cast<DateTimeMenuIndex>(menu->getElementIndex());

    switch (currentIndex)
    {
    case DateTimeMenuIndex::DATE:
        handleDateEditing(cmd);
        break;

    case DateTimeMenuIndex::TIME:
        handleTimeEditing(cmd);
        break;

    default:
        break;
    }
}

void DateTimeMenu::handleDateEditing(Command cmd)
{
    const EditingField editingField = menu->getEditingField();
    ISystemManager *sysManager = menu->getSystemManager();

    switch (editingField)
    {
    case EditingField::First:
        executeDirectionalEdit(cmd, [sysManager]()
                               { sysManager->incrementDay(); }, [sysManager]()
                               { sysManager->decreaseDay(); });
        break;

    case EditingField::Second:
        executeDirectionalEdit(cmd, [sysManager]()
                               { sysManager->incrementMonth(); }, [sysManager]()
                               { sysManager->decreaseMonth(); });
        break;

    case EditingField::Third:
        executeDirectionalEdit(cmd, [sysManager]()
                               { sysManager->incrementYear(); }, [sysManager]()
                               { sysManager->decreaseYear(); });
        break;

    default:
        return; // Don't update blinker for invalid field
    }
}

void DateTimeMenu::handleTimeEditing(Command cmd)
{
    const EditingField editingField = menu->getEditingField();
    ISystemManager *sysManager = menu->getSystemManager();

    switch (editingField)
    {
    case EditingField::First:
        executeDirectionalEdit(cmd, [sysManager]()
                               { sysManager->incrementHour(); }, [sysManager]()
                               { sysManager->decreaseHour(); });
        break;

    case EditingField::Second:
        executeDirectionalEdit(cmd, [sysManager]()
                               { sysManager->incrementMinute(); }, [sysManager]()
                               { sysManager->decreaseMinute(); });
        break;

    default:
        return; // Don't update blinker for invalid field
    }
}

void DateTimeMenu::navigateToSettingsMenu()
{
    menu->setCurrentMenu(
        menu->getMenuItems()->getSettingsMenu(),
        static_cast<uint8_t>(SettingsMenuIndex::DATE_TIME));
}

void DateTimeMenu::printElement(uint8_t index, uint8_t row)
{
    const auto menuIndex = static_cast<DateTimeMenuIndex>(index);

    switch (menuIndex)
    {
    case DateTimeMenuIndex::BACK:
        printBackElement(F(DATE_TIME_STR), row);
        break;

    case DateTimeMenuIndex::DATE:
        printDateElement(index, row);
        break;

    case DateTimeMenuIndex::TIME:
        printTimeElement(index, row);
        break;

    default:
        break;
    }
}

void DateTimeMenu::printDateElement(uint8_t index, uint8_t row)
{
    IDisplay *dispay = menu->getDispay();
    const RtcDateTime dateTime = menu->getDateTime();

    dispay->printAt(F(DATE_STR), 1, row);

    char *lcdBuffer = menu->getDisplayBuffer();
    snprintf(lcdBuffer, menu->getDisplayBufferSize(), "%02u/%02u/%04d",
             dateTime.day, dateTime.month, dateTime.year);

    handleElementDisplay(index, lcdBuffer, dispay->getColumns() - 10, row);
}

void DateTimeMenu::printTimeElement(uint8_t index, uint8_t row)
{
    IDisplay *dispay = menu->getDispay();
    const RtcDateTime dateTime = menu->getDateTime();

    dispay->printAt(F(TIME_STR), 1, row);

    char *lcdBuffer = menu->getDisplayBuffer();
    snprintf(lcdBuffer, menu->getDisplayBufferSize(), "%02u:%02u:%02u",
             dateTime.hour, dateTime.minute, dateTime.second);

    handleElementDisplay(index, lcdBuffer, dispay->getColumns() - 8, row);
}