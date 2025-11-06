#include <Arduino.h>
#include <unity.h>

using namespace fakeit;

#include "../mocks/MockMainSystem.h"

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
    RtcDateTime testTime{2024, 6, 15, 14, 30, 45};
    mockMainSystem->getMockRTC()->setTime(testTime);

    RtcDateTime result = systemManager->getDateTime();

    TEST_ASSERT_EQUAL(2024, result.year);
    TEST_ASSERT_EQUAL(6, result.month);
    TEST_ASSERT_EQUAL(15, result.day);
    TEST_ASSERT_EQUAL(14, result.hour);
    TEST_ASSERT_EQUAL(30, result.minute);
    TEST_ASSERT_EQUAL(45, result.second);
}

/* #region DAY TESTS */

void test_increment_day_calls_rtc_adjust(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 1, 15, 12, 30, 0});
    mockMainSystem->getMockRTC()->resetCallCount();
    systemManager->incrementDay();

    TEST_ASSERT_EQUAL(1, mockMainSystem->getMockRTC()->getAdjustCallCount());

    RtcDateTime result = mockMainSystem->getMockRTC()->now();
    TEST_ASSERT_EQUAL(16, result.day);
}

void test_increment_day_wraps_within_same_month(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 1, 31, 23, 59, 59});
    systemManager->incrementDay();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(1, result.day);
    TEST_ASSERT_EQUAL(1, result.month); // Month should NOT change
    TEST_ASSERT_EQUAL(2024, result.year);
}

void test_increment_day_leap_year_february(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 2, 28, 12, 0, 0});
    systemManager->incrementDay();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(29, result.day);
    TEST_ASSERT_EQUAL(2, result.month);
    TEST_ASSERT_EQUAL(2024, result.year);
}

void test_increment_day_non_leap_year_february(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2023, 2, 28, 12, 0, 0});
    systemManager->incrementDay();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(1, result.day);
    TEST_ASSERT_EQUAL(2, result.month);
    TEST_ASSERT_EQUAL(2023, result.year);
}

void test_decrease_day_wraps_within_same_month(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 3, 1, 10, 0, 0});
    systemManager->decreaseDay();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(31, result.day); // February 2024
    TEST_ASSERT_EQUAL(3, result.month);
}

void test_decrease_day_basic(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 6, 10, 8, 0, 0});
    systemManager->decreaseDay();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(9, result.day);
    TEST_ASSERT_EQUAL(6, result.month);
}

/* #endregion */

/* #region MONTH TESTS */

void test_increment_month_wraps_to_january(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 12, 15, 10, 0, 0});
    systemManager->incrementMonth();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(1, result.month);
    TEST_ASSERT_EQUAL(2024, result.year);
}

void test_decrease_month_wraps_to_december(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 1, 10, 8, 0, 0});
    systemManager->decreaseMonth();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(12, result.month);
    TEST_ASSERT_EQUAL(2024, result.year);
}

void test_increment_month_adjusts_day_if_needed(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 1, 31, 12, 0, 0});
    systemManager->incrementMonth();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(2, result.month);
    TEST_ASSERT_EQUAL(29, result.day); // February 2024 (leap)
}

/* #endregion */

/* #region YEAR TESTS */

void test_increment_year(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 6, 15, 10, 0, 0});
    systemManager->incrementYear();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(2025, result.year);
}

void test_decrease_year(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 6, 15, 10, 0, 0});
    systemManager->decreaseYear();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(2023, result.year);
}

/* #endregion */

/* #region HOUR TESTS */

void test_increment_hour_wraps_to_zero(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 5, 5, 23, 30, 0});
    systemManager->incrementHour();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(0, result.hour);
}

void test_decrease_hour_wraps_to_23(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 5, 5, 0, 30, 0});
    systemManager->decreaseHour();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(23, result.hour);
}

/* #endregion */

/* #region MINUTE TESTS */
void test_increment_minute_wraps_to_zero(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 5, 5, 12, 59, 30});
    systemManager->incrementMinute();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(0, result.minute);
    TEST_ASSERT_EQUAL(0, result.second);
}

void test_decrease_minute_wraps_to_59(void)
{
    mockMainSystem->getMockRTC()->setTime(RtcDateTime{2024, 5, 5, 12, 0, 0});
    systemManager->decreaseMinute();
    RtcDateTime result = mockMainSystem->getMockRTC()->now();

    TEST_ASSERT_EQUAL(59, result.minute);
    TEST_ASSERT_EQUAL(0, result.second);
}
/* #endregion */

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_get_date_time);

    RUN_TEST(test_increment_day_calls_rtc_adjust);
    RUN_TEST(test_increment_day_wraps_within_same_month);
    RUN_TEST(test_increment_day_leap_year_february);
    RUN_TEST(test_increment_day_non_leap_year_february);
    RUN_TEST(test_decrease_day_wraps_within_same_month);
    RUN_TEST(test_decrease_day_basic);

    RUN_TEST(test_increment_month_wraps_to_january);
    RUN_TEST(test_decrease_month_wraps_to_december);
    RUN_TEST(test_increment_month_adjusts_day_if_needed);

    RUN_TEST(test_increment_year);
    RUN_TEST(test_decrease_year);

    RUN_TEST(test_increment_hour_wraps_to_zero);
    RUN_TEST(test_decrease_hour_wraps_to_23);

    RUN_TEST(test_increment_minute_wraps_to_zero);
    RUN_TEST(test_decrease_minute_wraps_to_59);

    return UNITY_END();
}