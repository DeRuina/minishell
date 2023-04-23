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
	char	*expected[] = NULL;
	char	**actual = fd_cmd_trim("\"");
	TEST_ASSERT_EQUAL_MESSAGE(expected, actual, "Result is not NULL");
}

// Haven't checked if this checks only the stuff it's supposed to.
// void test_ft_cmd_trim_1337(void)
// {
// 	char	*expected[] = {"<Makefile", "cat|", "echo", "$PWD 'hola'", "~/src", "|", "'tr'", "-d", "/", ">outfile"};
// 	char	**actual = fd_cmdtrim("<Makefile cat| echo \"$PWD 'hola'\" ~/src | 'tr' -d / >outfile");

// 	TEST_ASSERT_EQUAL_MEMORY(expected, actual, sizeof(char *) * 10);
// }

int test_ft_cmd_trim(void)
{
	UNITY_BEGIN();
	// RUN_TEST(test_ft_cmd_trim_1337);
	return UNITY_END();
}
