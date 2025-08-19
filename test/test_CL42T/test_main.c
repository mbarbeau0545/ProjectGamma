#include "unity.h"
#include "CL42T/Src/CL42T.h"
#include "CL42T/Src/CL42T.c"
#include "mock_FMKCPU.h"
#include "mock_FMKCPU.c"


void setUp(void) {}
void tearDown(void) {}

void test_CL42T_Init(void) {
    CL42T_Init();
    TEST_ASSERT_TRUE(1);  // juste pour tester la compilation
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_CL42T_Init);
    return UNITY_END();
}
