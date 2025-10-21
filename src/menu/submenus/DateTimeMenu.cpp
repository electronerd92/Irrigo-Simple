#include "DateTimeMenu.h"
#include "../MenuItems.hpp"

DateTimeMenu::DateTimeMenu(Menu *menu) : MenuObj(menu, (uint8_t)DateTimeMenuIndex::ELEMENT_COUNT)
{
    updateBlinker = false;
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
        // Handle any other commands if needed
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
    const EditingField editingField = menu->getEditingField();

    switch (currentIndex)
    {
    case DateTimeMenuIndex::DATE:
        handleDateEditing(cmd, editingField);
        break;

    case DateTimeMenuIndex::TIME:
        handleTimeEditing(cmd, editingField);
        break;

    default:
        break;
    }
}

void DateTimeMenu::handleDateEditing(Command cmd, EditingField editingField)
{
    const bool isIncrement = (cmd == Command::RIGHT);
    SystemManager *systemManager = menu->getSystelManager();

    switch (editingField)
    {
    case EditingField::First:
        isIncrement ? systemManager->incrementDay() : systemManager->decreaseDay();
        break;

    case EditingField::Second:
        isIncrement ? systemManager->incrementMonth() : systemManager->decreaseMonth();
        break;

    case EditingField::Third:
        isIncrement ? systemManager->incrementYear() : systemManager->decreaseYear();
        break;

    default:
        return; // Don't update blinker for invalid field
    }

    updateBlinker = true;
}

void DateTimeMenu::handleTimeEditing(Command cmd, EditingField editingField)
{
    const bool isIncrement = (cmd == Command::RIGHT);
    SystemManager *systemManager = menu->getSystelManager();

    switch (editingField)
    {
    case EditingField::First:
        isIncrement ? systemManager->incrementHour() : systemManager->decreaseHour();
        break;

    case EditingField::Second:
        isIncrement ? systemManager->incrementMinute() : systemManager->decreaseMinute();
        break;

    default:
        return; // Don't update blinker for invalid field
    }

    updateBlinker = true;
}

void DateTimeMenu::navigateToSettingsMenu()
{
    menu->setCurrentMenu(
        menu->getMenuItems()->getSettingsMenu(),
        static_cast<uint8_t>(SettingsMenuIndex::DATE_TIME));
}

void DateTimeMenu::handleFieldSelection(EditingField lastField)
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
}

void DateTimeMenu::printElement(uint8_t index, uint8_t row)
{
    const auto menuIndex = static_cast<DateTimeMenuIndex>(index);

    switch (menuIndex)
    {
    case DateTimeMenuIndex::BACK:
        printBackElement(row);
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

void DateTimeMenu::printBackElement(uint8_t row)
{
    menu->getLcd()->print(F(DATE_TIME_STR), 1, row, PrintFormat::TITLE_WITH_BACK);
}

void DateTimeMenu::printDateElement(uint8_t index, uint8_t row)
{
    Lcd *lcd = menu->getLcd();
    const DateTime dateTime = menu->getDateTime();

    lcd->print(F(DATE_STR), 1, row);

    snprintf(lcdBuffer, BUFFER_SIZE, "%02u/%02u/%04d",
             dateTime.day(), dateTime.month(), dateTime.year());

    handleElementDisplay(index, lcdBuffer, LCD_COLUMNS - 10, row);
}

void DateTimeMenu::printTimeElement(uint8_t index, uint8_t row)
{
    Lcd *lcd = menu->getLcd();
    const DateTime dateTime = menu->getDateTime();

    lcd->print(F(TIME_STR), 1, row);

    snprintf(lcdBuffer, BUFFER_SIZE, "%02u:%02u:%02u",
             dateTime.hour(), dateTime.minute(), dateTime.second());

    handleElementDisplay(index, lcdBuffer, LCD_COLUMNS - 8, row);
}

void DateTimeMenu::handleElementDisplay(uint8_t elementIndex, const char *buffer, uint8_t col, uint8_t row)
{
    if (updateBlinker && menu->getIsEditingElement(elementIndex))
    {
        menu->getBlinker()->stopBlinking();
        menu->getBlinker()->startBlinking(buffer, col, row);
        updateBlinker = false;
    }
    else if (!menu->getIsEditingElement(elementIndex))
    {
        menu->getLcd()->print(buffer, col, row);
    }
}