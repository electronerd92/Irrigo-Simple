#include "DateTimeMenu.h"
#include "../MenuItems.hpp"

DateTimeMenu::DateTimeMenu(Menu *menu) : MenuObj(menu, (uint8_t)DateTimeMenuIndex::ELEMENT_COUNT)
{
}

void DateTimeMenu::executeCmd(Command cmd)
{

    // TODO Il primo SELECT devo skipparlo
    MenuItems *menuItems = menu->getMenuItems();

    switch ((DateTimeMenuIndex)menu->getElementIndex())
    {
    case DateTimeMenuIndex::BACK:
        menu->setCurrentMenu(menuItems->getMainMenu(), (uint8_t)SettingsMenuIndex::DATE_TIME);
        break;

    default:
        break;
    }

    // TODO la prima volta devo fare un refresh totale
    // menu->requestFullRefresh(false);
}

void DateTimeMenu::printElement(uint8_t index, uint8_t row)
{
    Lcd *lcd = menu->getLcd();
    DateTime dateTime = menu->getDateTime();
    switch ((DateTimeMenuIndex)index)
    {
    case DateTimeMenuIndex::BACK:
        lcd->print(F(DATE_TIME_STR), 1, row, PrintFormat::TITLE_WITH_BACK);
        break;
    case DateTimeMenuIndex::DATE:
        snprintf(lcdBuffer, BUFFER_SIZE, "%02u:%02u:%u", dateTime.day(), dateTime.month(), dateTime.year());
        lcd->print(lcdBuffer, 1, row);
        break;
    case DateTimeMenuIndex::TIME:
        snprintf(lcdBuffer, BUFFER_SIZE, "%02u:%02u::%02u", dateTime.hour(), dateTime.minute(), dateTime.second());
        lcd->print(lcdBuffer, 1, row);
        break;
    default:
        break;
    }
}