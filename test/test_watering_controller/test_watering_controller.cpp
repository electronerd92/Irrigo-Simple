#include <ArduinoFake.h>
#include <unity.h>

#include "../helpers/ArduinoTestHelper.h"

using namespace fakeit;

#include "systems/watering/WateringController.h"

Valve *valves;
Valve *outdoorValve;
Pump *pump;
Tank *tank;
Valve *tankFillValve;
Valve *mainFeedValve;
WateringController *controller;

void setUp(void)
{
    setupArduinoFake();

    valves = new Valve[VALVE_COUNT]{
        Valve(2, VALVE_ON, false),
        Valve(3, VALVE_ON, false),
        Valve(4, VALVE_ON, false),
        Valve(5, VALVE_ON, false),
        Valve(6, VALVE_ON, true),
        Valve(7, VALVE_ON, true),
        Valve(8, VALVE_ON, true),
        Valve(9, VALVE_ON, true)};
    outdoorValve = new Valve(10, VALVE_ON, false);
    pump = new Pump(11, PUMP_ON);
    tank = new Tank(TANK_LOW_LEVEL_PIN, TANK_HAS_WATER, TANK_FILLED_LEVEL_PIN, TANK_IS_FILLED);
    tankFillValve = new Valve(12, VALVE_ON, false);
    mainFeedValve = new Valve(13, VALVE_ON, false);

    controller = new WateringController(valves, *outdoorValve, *tankFillValve, *mainFeedValve, *pump, *tank);
}

void tearDown(void)
{
    delete controller;
    delete tank;
    delete pump;
    delete mainFeedValve;
    delete tankFillValve;
    delete outdoorValve;
    delete[] valves;
}

void test_automatic_enabled_default(void)
{
    TEST_ASSERT_TRUE(controller->isAutomaticEnabled());
}

void test_start_test_fails_if_duration_is_zero()
{
    bool result =
        controller->startTest(0, 0, 1000);

    TEST_ASSERT_FALSE(result);
}

void test_start_test_succeeds()
{
    When(Method(ArduinoFake(), digitalRead))
        .AlwaysReturn(HIGH); // tank has water

    bool result =
        controller->startTest(0, 60, 1000);

    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_TRUE(controller->isTesting());
}

void test_remaining_time()
{
    When(Method(ArduinoFake(), digitalRead))
        .AlwaysReturn(HIGH); // tank has water

    controller->startTest(0, 120, 1000);

    uint32_t remaining = controller->getRemainingTestTime(1060);

    TEST_ASSERT_EQUAL(60, remaining);
}

void test_start_fill_tank_fails_if_already_filled()
{
    When(Method(ArduinoFake(), digitalRead))
        .AlwaysReturn(HIGH); // tank filled sensor is active

    bool result = controller->startFillTank(1000);

    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_FALSE(controller->isFillingTank());
}

void test_start_fill_tank_succeeds_if_not_filled()
{
    When(Method(ArduinoFake(), digitalRead))
        .AlwaysReturn(LOW); // tank filled sensor is inactive

    bool result = controller->startFillTank(1000);

    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_TRUE(controller->isFillingTank());
    TEST_ASSERT_EQUAL(30, controller->getTankFillElapsedTime(1030));
}

void test_stop_fill_tank()
{
    When(Method(ArduinoFake(), digitalRead))
        .AlwaysReturn(LOW); // tank filled sensor is inactive

    controller->startFillTank(1000);
    controller->stopFillTank(1030);

    TEST_ASSERT_TRUE(controller->isFillingTank());
    TEST_ASSERT_EQUAL(30, controller->getTankFillElapsedTime(1060));
    TEST_ASSERT_EQUAL(30, controller->getLastTankFillDuration());
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_automatic_enabled_default);
    RUN_TEST(test_start_test_fails_if_duration_is_zero);
    RUN_TEST(test_start_test_succeeds);
    RUN_TEST(test_remaining_time);
    RUN_TEST(test_start_fill_tank_fails_if_already_filled);
    RUN_TEST(test_start_fill_tank_succeeds_if_not_filled);
    RUN_TEST(test_stop_fill_tank);
    return UNITY_END();
}