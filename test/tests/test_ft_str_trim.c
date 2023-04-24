#include "unity.h"
#include "minishell.h"


void test_ft_str_trim_0(void)
{
	char	**expected = NULL;
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("\""), "Result is not NULL #1");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("\'"), "Result is not NULL #2");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("\"\"\'"), "Result is not NULL #3");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("\'\'\""), "Result is not NULL #4");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("\'\"\""), "Result is not NULL #5");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("\'\'\'"), "Result is not NULL #6");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("\"\"\""), "Result is not NULL #7");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim(" \" "), "Result is not NULL #8");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim(" \' "), "Result is not NULL #9");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim(" \" \" \' "), "Result is not NULL #10");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim(" \' \' \" "), "Result is not NULL #11");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim(" \' \" \" "), "Result is not NULL #12");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim(" \' \' \' "), "Result is not NULL #13");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim(" \" \" \" "), "Result is not NULL #14");
}

void test_ft_str_trim_1(void)
{
	char	**expected = NULL;
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("echo\" abc"), "Result is not NULL #1");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("echo a\"bc"), "Result is not NULL #2");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("echo\" a\"bc"), "Result is not NULL #3");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("echo\" \"abc"), "Result is not NULL #4");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("ech\"o \"abc"), "Result is not NULL #5");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_str_trim("\"echo abc\""), "Result is not NULL #6");
}

void test_ft_str_trim_2(void)
{
	char	*expected0[] = {"echo", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_cmd_trim("echo \"abc\""), 2, "#0");
	char	*expected1[] = {"echo", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_cmd_trim("echo \"a\"bc"), 2, "#1");
	char	*expected2[] = {"echo", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, ft_cmd_trim("echo \"ab\"c"), 2, "#2");
	char	*expected3[] = {"echo", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, ft_cmd_trim("echo \"\"abc"), 2, "#3");
	char	*expected4[] = {"echo", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, ft_cmd_trim("echo abc\"\""), 2, "#4");
	char	*expected5[] = {"echo", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected5, ft_cmd_trim("ech\"o\" abc"), 2, "#5");
	char	*expected6[] = {"echo", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected6, ft_cmd_trim("echo\"\" abc"), 2, "#6");
	char	*expected7[] = {"echo", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected7, ft_cmd_trim("\"\"echo abc"), 2, "#7");
	char	*expected8[] = {"echo", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected8, ft_cmd_trim("\"echo\" abc"), 2, "#8");
	char	*expected9[] = {"echo", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected9, ft_cmd_trim("\"echo\"\"\" abc"), 2, "#9");
}

int test_ft_str_trim(void)
{
	UNITY_BEGIN();
	// RUN_TEST(test_ft_str_trim_0);
	// RUN_TEST(test_ft_str_trim_1);
	// RUN_TEST(test_ft_str_trim_2;
	return UNITY_END();
}
