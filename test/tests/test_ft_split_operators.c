#include "unity.h"
#include "minishell.h"

void test_ft_split_operators_0(void)
{
	char	*expected0[] = {"echo"};
	char	*array0[] = {"echo"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_split_operators(array0), 1, "#0");
	char	*expected1[] = {"echo", "|"};
	char	*array1[] = {"echo", "|"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_split_operators(array1), 2, "#1");
	char	*expected2[] = {"echo", "|"};
	char	*array2[] = {"echo|"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, ft_split_operators(array2), 2, "#2");
	char	*expected3[] = {NULL};
	char	*array3[] = {NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, ft_split_operators(array3), 1, "#3");
	char	**expected4 = NULL;
	char	**array4 = NULL;
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, ft_split_operators(array4), 1, "#4");
	char	*expected5[] = {"echo", NULL, "|", "ls"};
	char	*array5[] = {"echo", NULL, "|ls"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected5, ft_split_operators(array5), 1, "#5");
}

void test_ft_split_operators_1(void)
{
	char	*expected0[] = {"echo", "|", "|"};
	char	*array0[] = {"echo||"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_split_operators(array0), 3, "#0");
	char	*expected1[] = {"echo", "|", "echo" ,"|"};
	char	*array1[] = {"echo|echo|"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_split_operators(array1), 4, "#1");
	char	*expected2[] = {"<", "Makefile"};
	char	*array2[] = {"<Makefile"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, ft_split_operators(array2), 2, "#2");
	char	*expected3[] = {"<", "Makefile", ">"};
	char	*array3[] = {"<Makefile>"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, ft_split_operators(array3), 3, "#3");
	char	*expected4[] = {"echo", "\"echo\"", "|", "cat", "-e"};
	char	*array4[] = {"echo \"echo\"|cat -e"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, ft_split_operators(array4), 5, "#4");
	char	*expected5[] = {"echo", "\"echo\"", "|", "cat", "-e"};
	char	*array5[] = {"echo", "\"echo\"|cat", "-e"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected5, ft_split_operators(array5), 5, "#5");
	char	*expected6[] = {"/Users/druina/Desktop/github/minishellGitHub"};
	char	*array6[] = {"/Users/druina/Desktop/github/minishellGitHub"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected6, ft_split_operators(array6), 1, "#6");
	char	*expected7[] = {"echo", "/Users/druina/Desktop/github/minishellGitHub", "|", "cat", "-e"};
	char	*array7[] = {"echo", "\"/Users/druina/Desktop/github/minishellGitHub\"|cat", "-e"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected7, ft_split_operators(array7), 5, "#7");
	char	*expected8[] = {"<", "file.txt", ">", "outfile"};
	char	*array8[] = {"<file.txt>outfile"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected8, ft_split_operators(array8), 4, "#8");
	char	*expected9[] = {"<", "file.txt", ">>", "outfile"};
	char	*array9[] = {"<file.txt>>outfile"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected9, ft_split_operators(array9), 4, "#9");
	char	*expected10[] = {"<", "file.txt", ">", "in" ">", "outfile"};
	char	*array10[] = {"<", "file.txt>", "in", ">outfile"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected10, ft_split_operators(array10), 6, "#10");
	char	*expected11[] = {"<", "file.txt", ">", "in" ">>", "outfile"};
	char	*array11[] = {"<", "file.txt>in>>", "outfile"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected11, ft_split_operators(array11), 6, "#11");
	char	*expected12[] = {"<<", "file", ">", "outfile"};
	char	*array12[] = {"<<file>>outfile"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected12, ft_split_operators(array12), 4, "#12");
	char	*expected13[] = {"<<", "file", ">", "in" ">>", "outfile"};
	char	*array13[] = {"<<file> in>>outfile"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected13, ft_split_operators(array13), 6, "#13");


}

void test_ft_split_operators_2(void)
{
	char	*expected0[] = {"<", "Makefile", "cat" , "|", "echo", "\"/Users/druina/Desktop/github/minishell 'hola'\"", "/Users/druina/src", "|", "'tr'", "-d", "/", ">", "outfile"};
	char	*array0[] = {"<Makefile", "cat|", "echo", "\"/Users/druina/Desktop/github/minishell 'hola'\"", "/Users/druina/src", "|", "'tr'", "-d", "/", ">outfile"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_split_operators(array0), 13, "#0");
	char	*expected1[] = {"<", "file.txt", ">", "in", "echo", "hey", ">>", "outfile"};
	char	*array1[] = {"<", "file.txt", ">in", ">>", "outfile"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_split_operators(array1), 8, "#1");
}

int test_ft_split_operators(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_split_operators_0);
	RUN_TEST(test_ft_split_operators_1);
	RUN_TEST(test_ft_split_operators_2);
	return UNITY_END();
}
