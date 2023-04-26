#include "unity.h"
#include "minishell.h"

void test_ft_expand_0(void)
{
	char expected[100];
	getcwd(expected, 100);
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

void test_ft_expand_2(void)
{
	char *expected[] = {"test~", "hehe"};
	char *line[] = {"test~ hehe"};

	ft_expand(line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_3(void)
{
	char *expected[] = {"test", getenv("HOME"), "hehe"};
	char *line[] = {"test ~ hehe"};

	ft_expand(line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 3);
}

int test_ft_expand(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_expand_0);
	RUN_TEST(test_ft_expand_1);
	RUN_TEST(test_ft_expand_2);
	RUN_TEST(test_ft_expand_3);
	return UNITY_END();
}
