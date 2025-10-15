#include "Menu.h"
#include "../Config.h"
#include "MenuItems.hpp"
#include "Debug.hpp"

Menu::Menu(SystemManager *systemManager)
    : systemManager(systemManager),
      lcd(),
      rotaryEncoder(),
      blinker(&lcd),
      menuItems(nullptr),
      currentMenuItem(nullptr),
      elementIndex(0),
      cursor(0),
      refreshScreen(true)
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
        }
        else
        {
            refreshScreen = true; // Need to scroll
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
        }
        else
        {
            refreshScreen = true; // Need to scroll
        }
    }
}

void Menu::updateScreen(Command cmd)
{
    if (refreshScreen)
    {
        renderFullScreen();
    }
    else if (cmd != Command::NONE)
    {
        updateCursorOnly();
    }

    blinker.update();
}

void Menu::renderFullScreen()
{
    lcd.clear();
    const uint8_t offset = elementIndex - cursor;
    for (uint8_t row = 0; row < LCD_ROWS; row++)
    {
        if (row == cursor)
        {
            printCursor();
        }
        currentMenuItem->printElement(offset + row, row);
    }
    refreshScreen = false;
}

void Menu::updateCursorOnly()
{
    lcd.clearColumn(0);
    printCursor();
}

void Menu::printCursor()
{
    lcd.print(F(">"), 0, cursor);
}

Lcd *Menu::getLcd()
{
    return &lcd;
}

MenuItems *Menu::getMenuItems()
{
    return menuItems;
}

void Menu::setCurrentMenu(MenuObj *menuItem)
{
    // TODO
    /*
    quando setto il menu passo ozionalmente l'emem index per la back function
    In questo modo ritorno a dove ero prima
    Il cursore punterà all'emento in modo che se l'emento è < LCDROW allora il cursore
    sarà sull'elemento senno sarà al max
    cursor = min (elementIndex, ldcRow)
    */
    currentMenuItem = menuItem;
    elementIndex = 0;
    cursor = 0;
    refreshScreen = true;
}

uint8_t Menu::getElementIndex() const
{
    return elementIndex;
}

void Menu::printBackArrow(uint8_t row)
{
    lcd.print(F("^"), LCD_COLUMNS - 1, row);
}

void Menu::printNextMenuArrow(uint8_t row)
{
    lcd.print(F("->"), LCD_COLUMNS - 2, row);
}