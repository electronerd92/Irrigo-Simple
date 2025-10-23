#include <Debug.hpp>
#include <Config.h>
#include "Menu.h"
#include "MenuItems.hpp"

char lcdBuffer[BUFFER_SIZE];

Menu::Menu(SystemManager *systemManager)
    : systemManager(systemManager),
      lcd(),
      rotaryEncoder(),
      blinker(&lcd),
      menuItems(nullptr),
      currentMenuItem(nullptr),
      elementIndex(0),
      cursor(0),
      refreshType(RefreshType::ClearAndFullScreen),
      editingField(EditingField::None)
{
    menuItems = new MenuItems(this);
    currentMenuItem = menuItems->getMainMenu();
}

void Menu::update()
{
    Command cmd = rotaryEncoder.readCommand();
    if (!blinker.getIsBlinking() && (cmd == Command::RIGHT || cmd == Command::LEFT))
    {
        updateElementAndCursor(cmd);
    }
    else
    {
        currentMenuItem->executeCmd(cmd);
    }
    updateScreen(cmd);
}

void Menu::updateElementAndCursor(Command cmd)
{
    const uint8_t maxElements = currentMenuItem->getElementsCount();

    switch (cmd)
    {
    case Command::RIGHT:
        moveDown(maxElements);
        break;

    case Command::LEFT:
        moveUp();
        break;

    default:
        break;
    }
}

void Menu::moveDown(uint8_t maxElements)
{
    if (elementIndex < maxElements - 1)
    {
        elementIndex++;

        if (cursor < LCD_ROWS - 1)
        {
            cursor++;
            refreshType = RefreshType::CursorOnly;
        }
        else
        {
            refreshType = RefreshType::ClearAndFullScreen; // Need to scroll
        }
    }
}

void Menu::moveUp()
{
    if (elementIndex > 0)
    {
        elementIndex--;

        if (cursor > 0)
        {
            cursor--;
            refreshType = RefreshType::CursorOnly;
        }
        else
        {
            refreshType = RefreshType::ClearAndFullScreen; // Need to scroll
        }
    }
}

void Menu::updateScreen(Command cmd)
{
    switch (refreshType)
    {
    case RefreshType::ClearAndFullScreen:
        renderFullScreen(true);
        break;

    case RefreshType::FullScreen:
        renderFullScreen(false);
        break;

    case RefreshType::CursorOnly:
        updateCursorOnly();
        break;

    case RefreshType::None:
    default:
        break;
    }

    refreshType = RefreshType::None; // reset after drawing
    blinker.update();
}

void Menu::renderFullScreen(bool clearAll)
{
    if (clearAll)
    {
        lcd.clear();
    }

    const uint8_t offset = elementIndex - cursor;
    for (uint8_t row = 0; row < LCD_ROWS; row++)
    {
        if (row == cursor)
        {
            printCursor();
        }
        currentMenuItem->printElement(offset + row, row);
    }
}

void Menu::updateCursorOnly()
{
    lcd.clearColumn(0);
    printCursor();
}

void Menu::printCursor()
{
    lcd.print('>', 0, cursor);
}

SystemManager *Menu::getSystelManager()
{
    return systemManager;
}

Lcd *Menu::getLcd()
{
    return &lcd;
}

Blinker *Menu::getBlinker()
{
    return &blinker;
}

MenuItems *Menu::getMenuItems()
{
    return menuItems;
}

void Menu::setCurrentMenu(MenuObj *menuItem, uint8_t position)
{
    //? Il cursore punterà all'elemento, limitandolo all'ultima row dell'lcd
    currentMenuItem = menuItem;
    elementIndex = position;
    cursor = min(position, LCD_ROWS - 1);
    refreshType = RefreshType::ClearAndFullScreen;
    stopEditing();
}

uint8_t Menu::getElementIndex() const
{
    return elementIndex;
}

DateTime Menu::getDateTime()
{
    return systemManager->getDateTime();
}

EditingField Menu::getEditingField() const
{
    return editingField;
}

bool Menu::getIsEditingElement(uint8_t index)
{
    return editingField != EditingField::None && index == elementIndex;
}

void Menu::incrementEditingField()
{
    // TODO add an optional parameter to pause the system when a field is being edited
    editingField = (EditingField)(((uint8_t)editingField + 1) % (uint8_t)EditingField::Max);
}

void Menu::stopEditing()
{
    editingField = EditingField::None;
    blinker.stopBlinking();
}