#include <unity.h>
#include <RTClib.h>
#include "../../mocks/MockMainSystem.h"

// Include the REAL SystemManager
#include <core/SystemManager.h>

MockMainSystem *mockMainSystem;
SystemManager *systemManager;

void setUp(void)
{
    mockMainSystem = new MockMainSystem();
    systemManager = new SystemManager(mockMainSystem);
}

void tearDown(void)
{
    delete systemManager;
    delete mockMainSystem;
}

void test_get_date_time(void)
{
    DateTime testTime(2024, 6, 15, 14, 30, 45);
    mockMainSystem->getMockRTC()->setTime(testTime);

    DateTime result = systemManager->getDateTime();

    TEST_ASSERT_EQUAL(2024, result.year());
    TEST_ASSERT_EQUAL(6, result.month());
    TEST_ASSERT_EQUAL(15, result.day());
    TEST_ASSERT_EQUAL(14, result.hour());
    TEST_ASSERT_EQUAL(30, result.minute());
    TEST_ASSERT_EQUAL(45, result.second());
}

void test_increment_day_calls_rtc_adjust(void)
{
    mockMainSystem->getMockRTC()->setTime(DateTime(2024, 1, 15, 12, 30, 0));
    mockMainSystem->getMockRTC()->resetCallCount();

    systemManager->incrementDay();

    TEST_ASSERT_EQUAL(1, mockMainSystem->getMockRTC()->getAdjustCallCount());

    DateTime result = mockMainSystem->getMockRTC()->now();
    TEST_ASSERT_EQUAL(16, result.day());
}

void test_increment_day_leap_year_february(void)
{
    mockMainSystem->getMockRTC()->setTime(DateTime(2024, 2, 28, 12, 0, 0));

    systemManager->incrementDay();

    DateTime result = mockMainSystem->getMockRTC()->now();
    TEST_ASSERT_EQUAL(29, result.day());
    TEST_ASSERT_EQUAL(2, result.month());
    TEST_ASSERT_EQUAL(2024, result.year());
}

// ... rest of your tests

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_get_date_time);
    RUN_TEST(test_increment_day_calls_rtc_adjust);
    RUN_TEST(test_increment_day_leap_year_february);
    // ... other tests

    return UNITY_END();
}