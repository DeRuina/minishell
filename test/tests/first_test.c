#include "unity.h"
#include "mytest.h"

void test_first_test_0(void)
{
	int	expected = 42;
	int	actual = my_test();

	TEST_ASSERT_EQUAL_INT_MESSAGE(expected, actual, "Result was not 42");
}

int test0(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_first_test_0);
	RUN_TEST(test_first_test_0);
	return UNITY_END();
}
