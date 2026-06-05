#include <unity.h>

// Include module header and, when needed, C file + mocks

void setUp(void)
{
    // Reset globals and fakes
}

void tearDown(void)
{
}

void test_feature_should_behave_as_expected(void)
{
    TEST_FAIL_MESSAGE("Replace with real assertions");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_feature_should_behave_as_expected);
    return UNITY_END();
}
