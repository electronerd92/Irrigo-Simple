#include <Arduino.h>
#include <unity.h>

using namespace fakeit;

#include "../mocks/MockSystemManager.h"
#include "../mocks/MockDisplay.h"
#include "../mocks/MockInputDevice.h"
#include "../mocks/MockBlinker.h"

// Include the REAL Menu
#include <core/Menu.h>
#include <core/MenuItems.hpp>
#include <config/ConfigFactory.h>

MockSystemManager *sys;
MockDisplay *disp;
MockInputDevice *input;
MockBlinker *blinker;

Menu *menu;

void setUp(void)
{
    MenuConfig config = ConfigFactory::createMenuConfig();

    sys = new MockSystemManager();
    disp = new MockDisplay(config.lcd.rows, config.lcd.columns);
    input = new MockInputDevice();
    blinker = new MockBlinker();

    menu = new Menu(sys, disp, input, blinker, config.bufferSize);
}

void test_menu_start_at_main_menu(void)
{
    // Check if the current menu is the main menu
    TEST_ASSERT_EQUAL_PTR(menu->getCurrentMenu(), menu->getMenuItems()->getMainMenu());
}

void test_navigate_to_settings_menu(void)
{
    // Move 3 times (simulate pressing RIGHT 3x)
    for (int i = 0; i < 3; ++i)
    {
        input->nextCommand = Command::RIGHT;
        menu->update();
    }

    // Then press SELECT
    input->nextCommand = Command::SELECT;
    menu->update();

    // The menu should now have switched to the Settings menu
    TEST_ASSERT_EQUAL_PTR(menu->getCurrentMenu(), menu->getMenuItems()->getSettingsMenu());
}

void tearDown(void)
{
    delete sys;
    delete disp;
    delete input;
    delete blinker;
    delete menu;
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_menu_start_at_main_menu);
    RUN_TEST(test_navigate_to_settings_menu);

    return UNITY_END();
}