#include "Menu.h"
#include "MenuItems.hpp"
#include <Compatibility.h>

Menu::Menu(ISystemManager *sysManager, IDisplay *display, IInputDevice *inputDevice, IBlinker *blinker, uint8_t bufferSize)
    : sysManager(sysManager),
      display(display),
      dispayBufferSize(bufferSize),
      inputDevice(inputDevice),
      blinker(blinker),
      menuItems(nullptr),
      currentMenuItem(nullptr),
      elementIndex(0),
      cursor(0),
      refreshType(RefreshType::ClearAndFullScreen),
      editingField(EditingField::None)

{
    dispayBuffer = new char[bufferSize];

    menuItems = new MenuItems(this);
    currentMenuItem = menuItems->getMainMenu();
}

void Menu::update()
{
    Command cmd = inputDevice->readCommand();
    if (!blinker->getIsBlinking() && (cmd == Command::RIGHT || cmd == Command::LEFT))
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

        if (cursor < display->getRows() - 1)
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
    blinker->update();
}

void Menu::renderFullScreen(bool clearAll)
{
    if (clearAll)
    {
        display->clear();
    }

    const uint8_t offset = elementIndex - cursor;
    for (uint8_t row = 0; row < display->getRows(); row++)
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
    display->clearColumn(0);
    printCursor();
}

void Menu::printCursor()
{
    display->printCharAt('>', 0, cursor);
}

ISystemManager *Menu::getSystemManager()
{
    return sysManager;
}

IDisplay *Menu::getDispay()
{
    return display;
}

char *Menu::getDisplayBuffer()
{
    return dispayBuffer;
}

uint8_t Menu::getDisplayBufferSize()
{
    return dispayBufferSize;
}

IBlinker *Menu::getBlinker()
{
    return blinker;
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
    cursor = min(position, display->getRows() - 1);
    refreshType = RefreshType::ClearAndFullScreen;
    stopEditing();
}

uint8_t Menu::getElementIndex() const
{
    return elementIndex;
}

RtcDateTime Menu::getDateTime()
{
    return sysManager->getDateTime();
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
    blinker->stopBlinking();
}