#include "unity.h"
#include "minishell.h"

void test_ft_expand_0(void)
{
	char expected[100];
	getwd(expected);
	char *line = "$PWD";

	ft_expand(&line);
	TEST_ASSERT_EQUAL_STRING(expected, line);
}

void test_ft_expand_1(void)
{
	char *expected = getenv("HOME");
	char *line = "~";

	ft_expand(&line);
	TEST_ASSERT_EQUAL_STRING(expected, line);
}

int test_ft_expand(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_expand_0);
	RUN_TEST(test_ft_expand_1);
	return UNITY_END();
}
