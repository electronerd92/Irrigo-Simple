#include <unity.h>

void setUp(void)
{
    // Set up code here, if needed
}
void tearDown(void) {}

void test_move_up_no_underflow_at_zero(void)
{
    TEST_ASSERT_FALSE(false);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test1);
    return UNITY_END();
}