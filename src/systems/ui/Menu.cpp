#include "Menu.h"
#include "MenuObj.hpp"
#include "config.h"

Menu::Menu(IDisplay &display,
           IInputDevice &input,
           Blinker &blinker,
           DateTimeService &dateTime,
           char *buffer,
           uint8_t bufferSize)
    : display(display),
      input(input),
      blinker(blinker),
      dateTime(dateTime),
      buffer(buffer),
      bufferSize(bufferSize),
      sleepTimer(MENU_SLEEP_MS)
{
}

void Menu::init(MenuObj &root)
{
    rootMenu = &root;
    setCurrentMenu(root);
    input.readAndClearCommand(); // clear any pending input
}

void Menu::update()
{
    Command cmd = input.readAndClearCommand();

    if (!screenOn)
    {
        if (cmd != Command::NONE)
        {
            wakeUp(); // first input wakes screen
        }
        return; // DO NOT PROCESS MENU
    }

    if (cmd != Command::NONE)
    {
        sleepTimer.start(); // reset sleep timer on any input
    }

    if (!isEditing() && sleepTimer.timeout())
    {
        sleep();
        return; // DO NOT PROCESS MENU
    }

    if (!blinker.getIsBlinking() &&
        (cmd == Command::RIGHT || cmd == Command::LEFT))
    {
        handleNavigation(cmd);
    }
    else
    {
        current->executeCmd(cmd);
    }

    switch (refresh)
    {
    case RefreshType::ClearFull:
        draw(true); // clear screen
        break;

    case RefreshType::Full:
        draw(false); // no clear ✅
        break;

    case RefreshType::CursorOnly:
        drawCursorOnly();
        break;

    default:
        break;
    }

    refresh = RefreshType::None;
    blinker.update();
}

void Menu::handleNavigation(Command cmd)
{
    uint8_t count = current->getElementsCount();

    if (cmd == Command::RIGHT && selected < count - 1)
    {
        selected++;

        if (cursor < display.getRows() - 1)
        {
            cursor++;
            refresh = RefreshType::CursorOnly;
        }
        else
        {
            refresh = RefreshType::ClearFull;
        }
    }
    else if (cmd == Command::LEFT && selected > 0)
    {
        selected--;

        if (cursor > 0)
        {
            cursor--;
            refresh = RefreshType::CursorOnly;
        }
        else
        {
            refresh = RefreshType::ClearFull;
        }
    }
}

void Menu::draw(bool clear)
{
    if (clear)
        display.clear();

    uint8_t offset = selected - cursor;

    for (uint8_t row = 0; row < display.getRows(); row++)
    {
        if (row == cursor)
            drawCursor();

        current->printElement(offset + row, row);
    }
}

void Menu::drawCursor()
{
    display.setCursor(0, cursor);
    display.write('>');
}

void Menu::drawCursorOnly()
{
    for (uint8_t row = 0; row < display.getRows(); ++row)
    {
        display.clearChar(0, row);
    }

    drawCursor();
}

IDisplay &Menu::getDisplay()
{
    return display;
}

Blinker &Menu::getBlinker()
{
    return blinker;
}

DateTimeService &Menu::getDateTime()
{
    return dateTime;
}

char *Menu::getBuffer()
{
    return buffer;
}

uint8_t Menu::getBufferSize() const
{
    return bufferSize;
}

uint8_t Menu::getSelectedIndex() const
{
    return selected;
}

uint8_t Menu::getEditingField() const
{
    return static_cast<uint8_t>(field);
}

bool Menu::isEditing() const
{
    return field != EditingField::None;
}

bool Menu::isEditing(uint8_t index) const
{
    return isEditing() && index == selected;
}

void Menu::nextField()
{
    field = static_cast<EditingField>(
        (static_cast<uint8_t>(field) + 1) %
        static_cast<uint8_t>(EditingField::Max));
}

void Menu::stopEditing()
{
    field = EditingField::None;
    blinker.stopBlinking();
}

void Menu::requestRefresh(bool clear)
{
    refresh = clear ? RefreshType::ClearFull : RefreshType::Full;
}

void Menu::setCurrentMenu(MenuObj &m, uint8_t index)
{
    current = &m;
    selected = index;

    // avoid std::min (macro issues)
    uint8_t rows = display.getRows();
    cursor = (index < rows) ? index : (rows - 1);

    stopEditing();

    refresh = RefreshType::ClearFull;
}

void Menu::sleep()
{
    display.clear();
    display.power(false);
    screenOn = false;
}

void Menu::wakeUp()
{
    display.power(true);
    screenOn = true;
    sleepTimer.start();

    setCurrentMenu(*rootMenu);

    refresh = RefreshType::ClearFull;
}