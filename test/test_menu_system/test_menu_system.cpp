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

void tearDown(void)
{
    delete sys;
    delete disp;
    delete input;
    delete blinker;
    delete menu;
    sys = nullptr;
    disp = nullptr;
    input = nullptr;
    blinker = nullptr;
    menu = nullptr;
}

// Helper function to send command and update menu
void sendCommand(Command cmd, int repeat = 1)
{
    for (int i = 0; i < repeat; ++i)
    {
        input->nextCommand = cmd;
        menu->update();
    }
}
/* #region menu navigation */
void test_menu_start_at_main_menu(void)
{
    // Check if the current menu is the main menu
    TEST_ASSERT_EQUAL_PTR(menu->getCurrentMenu(), menu->getMenuItems()->getMainMenu());
}

void test_navigate_to_settings_menu(void)
{
    menu->init();

    // Move 3 times (simulate pressing RIGHT 3x)
    sendCommand(Command::RIGHT, 3);

    // Then press SELECT
    sendCommand(Command::SELECT);

    // The menu should now have switched to the Settings menu
    TEST_ASSERT_EQUAL_PTR(menu->getCurrentMenu(), menu->getMenuItems()->getSettingsMenu());
}
/* #endregion menu navigation */

/* #region menu calls */
void test_date_field_editing(void)
{
    menu->init();
    menu->setCurrentMenu(menu->getMenuItems()->getDateTimeMenu());
    sendCommand(Command::RIGHT);
    sendCommand(Command::SELECT); // Ented in DATE editing mode
    menu->update();               // refresh lcd and active blinker

    sys->clearCalls();

    // Test Day field (should be first field)
    TEST_MESSAGE("Testing Day field increment");
    sendCommand(Command::RIGHT);
    sys->assertOnlyMethodCalled("incrementDay", 1);
    sys->clearCalls();

    TEST_MESSAGE("Testing Day field decrement");
    sendCommand(Command::LEFT);
    sys->assertOnlyMethodCalled("decreaseDay", 1);
    sys->clearCalls();

    // Move to Month field
    TEST_MESSAGE("Moving to Month field");
    sendCommand(Command::SELECT);
    sys->clearCalls();

    TEST_MESSAGE("Testing Month field increment");
    sendCommand(Command::RIGHT);
    sys->assertOnlyMethodCalled("incrementMonth", 1);
    sys->clearCalls();

    TEST_MESSAGE("Testing Month field decrement");
    sendCommand(Command::LEFT);
    sys->assertOnlyMethodCalled("decreaseMonth", 1);
    sys->clearCalls();

    // Move to Year field
    TEST_MESSAGE("Moving to Year field");
    sendCommand(Command::SELECT);
    sys->clearCalls();

    TEST_MESSAGE("Testing Year field increment");
    sendCommand(Command::RIGHT);
    sys->assertOnlyMethodCalled("incrementYear", 1);
    sys->clearCalls();

    TEST_MESSAGE("Testing Year field decrement");
    sendCommand(Command::LEFT);
    sys->assertOnlyMethodCalled("decreaseYear", 1);

    // Test Year field should be last field
    sendCommand(Command::SELECT); // Exit editing mode
    TEST_ASSERT_EQUAL(menu->getEditingField(), EditingField::None);
    TEST_ASSERT_FALSE(menu->getBlinker()->getIsBlinking());
}

void test_time_field_editing(void)
{
    menu->init();
    menu->setCurrentMenu(menu->getMenuItems()->getDateTimeMenu());
    sendCommand(Command::RIGHT);
    sendCommand(Command::RIGHT);
    sendCommand(Command::SELECT); // Ented in TIME editing mode
    menu->update();               // refresh lcd and active blinker

    sys->clearCalls();

    // Test Hour field (should be first field)
    TEST_MESSAGE("Testing Hour field increment");
    sendCommand(Command::RIGHT);
    sys->assertOnlyMethodCalled("incrementHour", 1);
    sys->clearCalls();

    TEST_MESSAGE("Testing Hour field decrement");
    sendCommand(Command::LEFT);
    sys->assertOnlyMethodCalled("decreaseHour", 1);
    sys->clearCalls();

    // Move to Minute field
    TEST_MESSAGE("Moving to Minute field");
    sendCommand(Command::SELECT);
    sys->clearCalls();

    // Test Minute field (should be first field)
    TEST_MESSAGE("Testing Minute field increment");
    sendCommand(Command::RIGHT);
    sys->assertOnlyMethodCalled("incrementMinute", 1);
    sys->clearCalls();

    TEST_MESSAGE("Testing Minute field decrement");
    sendCommand(Command::LEFT);
    sys->assertOnlyMethodCalled("decreaseMinute", 1);
    sys->clearCalls();

    // Test Minute field should be last field
    sendCommand(Command::SELECT); // Exit editing mode
    TEST_ASSERT_EQUAL(menu->getEditingField(), EditingField::None);
    TEST_ASSERT_FALSE(menu->getBlinker()->getIsBlinking());
}

/* #endregion menu calls */

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_menu_start_at_main_menu);
    RUN_TEST(test_navigate_to_settings_menu);
    RUN_TEST(test_date_field_editing);
    RUN_TEST(test_time_field_editing);

    return UNITY_END();
}