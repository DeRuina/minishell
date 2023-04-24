#include "unity.h"
#include "minishell.h"

// // void test_parse_args_0(void)
// // {
// // 	char	*expected[] = {"echo test1", "|", "echo \"|\""};
// // 	char	*actual[] = parse_args("echo test1 | echo test2");

// // 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// // }

// // void test_parse_args_1(void)
// // {
// // 	char	*expected[] = {"echo test1", "|" ,"echo test2", ">", "file.txt"};
// // 	char	*actual = parse_args("echo test1 | echo test2 > file.txt");

// // 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// // }

// // void test_parse_args_2(void)
// // {
// // 	char	*expected[] = {"echo test1", "|" ,"echo test2", ">", "file.txt"};
// // 	char	*actual = parse_args();

// // 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// // }

// void test_parse_args_3(void)
// {
// 	char	*expected = "this ";
// 	char 	*test = ft_strdup("      this     ");
// 	char	*actual = get_token(&test);

// 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// }

// void test_parse_args_4(void)
// {
// 	char	*expected = "this";
// 	char 	*test = ft_strdup("this");
// 	char	*actual = get_token(&test);

// 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// }

// void test_parse_args_5(void)
// {
// 	char	*expected = NULL;
// 	char 	*test = ft_strdup("         ");
// 	char	*actual = get_token(&test);

// 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// }

// void test_parse_args_6(void)
// {
// 	char	*expected = NULL;
// 	char 	*test = NULL;
// 	char	*actual = get_token(&test);

// 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// }

// void test_parse_args_7(void)
// {
// 	char	*expected = "\" ' thisi ' \"";
// 	char 	*test = ft_strdup("\" ' thisi ' \"");
// 	char	*actual = get_token(&test);

// 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// }

// void test_parse_args_8(void)
// {
// 	char	*expected = "\' \" thisi \" \'";
// 	char 	*test = ft_strdup("\' \" thisi \" \'");
// 	char	*actual = get_token(&test);

// 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// }

// void test_parse_args_9(void)
// {
// 	char	*expected = "\' \\' thisi \" \'";
// 	char 	*test = ft_strdup("\' \\' thisi \" \'");
// 	char	*actual = get_token(&test);

// 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// }

void test_ft_cmd_trim_0(void)
{
	char	**expected = NULL;
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("\""), "Result is not NULL #1");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("\'"), "Result is not NULL #2");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("\"\"\'"), "Result is not NULL #3");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("\'\'\""), "Result is not NULL #4");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("\'\"\""), "Result is not NULL #5");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("\'\'\'"), "Result is not NULL #6");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("\"\"\""), "Result is not NULL #7");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim(" \" "), "Result is not NULL #8");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim(" \' "), "Result is not NULL #9");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim(" \" \" \' "), "Result is not NULL #10");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim(" \' \' \" "), "Result is not NULL #11");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim(" \' \" \" "), "Result is not NULL #12");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim(" \' \' \' "), "Result is not NULL #13");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim(" \" \" \" "), "Result is not NULL #14");
}

void test_ft_cmd_trim_1(void)
{
	char	**expected = NULL;
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("echo\" abc"), "Result is not NULL #1");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("echo a\"bc"), "Result is not NULL #2");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("echo\" a\"bc"), "Result is not NULL #3");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("echo\" \"abc"), "Result is not NULL #4");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("ech\"o \"abc"), "Result is not NULL #5");
	TEST_ASSERT_EQUAL_MESSAGE(expected, ft_cmd_trim("\"echo abc\""), "Result is not NULL #6");
}

void test_ft_cmd_trim_2(void)
{
	char	*expected0[] = {"echo", "\"abc\""};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_cmd_trim("echo \"abc\""), 2, "#0");
	char	*expected1[] = {"echo", "\"a\"bc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_cmd_trim("echo \"a\"bc"), 2, "#1");
	char	*expected2[] = {"echo", "\"ab\"c"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, ft_cmd_trim("echo \"ab\"c"), 2, "#2");
	char	*expected3[] = {"echo", "\"\"abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, ft_cmd_trim("echo \"\"abc"), 2, "#3");
	char	*expected4[] = {"echo", "abc\"\""};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, ft_cmd_trim("echo abc\"\""), 2, "#4");
	char	*expected5[] = {"ech\"o\"", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected5, ft_cmd_trim("ech\"o\" abc"), 2, "#5");
	char	*expected6[] = {"echo\"\"", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected6, ft_cmd_trim("echo\"\" abc"), 2, "#6");
	// char	*expected7[] = {"\"\"echo", "abc"};
	// TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected7, ft_cmd_trim("\"\"echo abc"), 2, "#7");
	char	*expected8[] = {"\"echo\"", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected8, ft_cmd_trim("\"echo\" abc"), 2, "#8");
	char	*expected9[] = {"\"echo\"\"\"", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected9, ft_cmd_trim("\"echo\"\"\" abc"), 2, "#9");
}

// Haven't checked if this checks only the stuff it's supposed to.
// Or if it tests anything at all.
// void test_ft_cmd_trim_1337(void)
// {
// 	char	*expected[] = {"<Makefile", "cat|", "echo", "$PWD 'hola'", "~/src", "|", "'tr'", "-d", "/", ">outfile"};
// 	char	**actual = ft_cmd_trim("<Makefile cat| echo \"$PWD 'hola'\" ~/src | 'tr' -d / >outfile");

// 	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, 10);
// }

int test_ft_cmd_trim(void)
{
	UNITY_BEGIN();
	// RUN_TEST(test_ft_cmd_trim_0);
	// RUN_TEST(test_ft_cmd_trim_1);
	RUN_TEST(test_ft_cmd_trim_2);
	// RUN_TEST(test_ft_cmd_trim_1337);
	return UNITY_END();
}
