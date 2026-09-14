#include <ArduinoFake.h>
#include <unity.h>

#include "../helpers/ArduinoTestHelper.h"

using namespace fakeit;

#include "systems/watering/WateringController.h"

Valve *valves;
Valve *outdoorValve;
Pump *pump;
Tank *tank;
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
    tank = new Tank(TANK_LOW_LEVEL_PIN, TANK_HAS_WATER);

    controller = new WateringController(valves, *outdoorValve, *pump, *tank);
}

void tearDown(void)
{
    delete controller;
    delete tank;
    delete pump;
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

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_automatic_enabled_default);
    RUN_TEST(test_start_test_fails_if_duration_is_zero);
    RUN_TEST(test_start_test_succeeds);
    RUN_TEST(test_remaining_time);
    return UNITY_END();
}