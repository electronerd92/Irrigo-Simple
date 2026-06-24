#include "DateTimeMenu.h"
#include "SettingsMenu.h"

DateTimeMenu::DateTimeMenu(Menu &menu,
                           MenuObj &settingsMenu,
                           DateTimeService &service)
    : EditableMenuObj(menu, static_cast<uint8_t>(DateTimeMenuIndex::ELEMENT_COUNT)),
      settingsMenu(settingsMenu),
      dateTime(service)
{
}

void DateTimeMenu::executeCmd(Command cmd)
{
    switch (cmd)
    {
    case Command::SELECT:
        handleSelect();
        break;

    case Command::LEFT:
    case Command::RIGHT:
        handleEdit(cmd);
        break;

    case Command::NONE:
        menu.requestRefresh(false);
        break;

    default:
        break;
    }
}

void DateTimeMenu::handleSelect()
{
    switch (static_cast<DateTimeMenuIndex>(menu.getSelectedIndex()))
    {
    case DateTimeMenuIndex::BACK:
        menu.setCurrentMenu(settingsMenu, static_cast<uint8_t>(SettingsMenuIndex::DATE_TIME));
        break;

    case DateTimeMenuIndex::DATE:
        handleFieldSelection(3); // Third
        break;

    case DateTimeMenuIndex::TIME:
        handleFieldSelection(2); // Second
        break;

    default:
        break;
    }
}

void DateTimeMenu::handleEdit(Command cmd)
{
    if (!menu.isEditing(menu.getSelectedIndex()))
        return;

    uint8_t f = menu.getEditingField();

    switch (static_cast<DateTimeMenuIndex>(menu.getSelectedIndex()))
    {
    case DateTimeMenuIndex::DATE:
        switch (f)
        {
        case 1: // Day
            executeDirectionalEdit(
                cmd,
                [&]()
                { dateTime.incDay(); },
                [&]()
                { dateTime.decDay(); });
            break;

        case 2: // Month
            executeDirectionalEdit(
                cmd,
                [&]()
                { dateTime.incMonth(); },
                [&]()
                { dateTime.decMonth(); });
            break;

        case 3: // Year
            executeDirectionalEdit(
                cmd,
                [&]()
                { dateTime.incYear(); },
                [&]()
                { dateTime.decYear(); });
            break;

        default:
            return;
        }
        break;

    case DateTimeMenuIndex::TIME:
        switch (f)
        {
        case 1: // Hour
            executeDirectionalEdit(
                cmd,
                [&]()
                { dateTime.incHour(); },
                [&]()
                { dateTime.decHour(); });
            break;

        case 2: // Minute
            executeDirectionalEdit(
                cmd,
                [&]()
                { dateTime.incMinute(); },
                [&]()
                { dateTime.decMinute(); });
            break;

        default:
            return;
        }
        break;

    default:
        break;
    }
}

void DateTimeMenu::printElement(uint8_t index, uint8_t row)
{
    switch (static_cast<DateTimeMenuIndex>(index))
    {
    case DateTimeMenuIndex::BACK:
        printWithBack(F("Date & Time"), row);
        break;

    case DateTimeMenuIndex::DATE:
        printDate(index, row);
        break;

    case DateTimeMenuIndex::TIME:
        printTime(index, row);
        break;

    default:
        break;
    }
}

void DateTimeMenu::printDate(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);
    d.print(F("Date"));

    auto dt = dateTime.get();

    char *buf = menu.getBuffer();
    snprintf(buf, menu.getBufferSize(),
             "%02u/%02u/%04u",
             dt.day, dt.month, dt.year);

    handleElementDisplay(index, buf, d.getColumns() - 10, row);
}

void DateTimeMenu::printTime(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);
    d.print(F("Time"));

    auto dt = dateTime.get();

    char *buf = menu.getBuffer();
    snprintf(buf, menu.getBufferSize(),
             "%02u:%02u:%02u",
             dt.hour, dt.minute, dt.second);

    handleElementDisplay(index, buf, d.getColumns() - 8, row);
}