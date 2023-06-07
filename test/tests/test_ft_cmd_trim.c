/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_cmd_trim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:46:37 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/07 12:11:05 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"

void test_ft_cmd_trim_0(void)
{
	char	*expected[] = {"echo"};
	char	**actual = ft_cmd_trim("   echo   ");
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, 1);
	free_2d(actual);
}

void test_ft_cmd_trim_1(void)
{
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(NULL, ft_cmd_trim(NULL), 1, "#0");
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(NULL, ft_cmd_trim("      "), 1, "#1");
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(NULL, ft_cmd_trim(""), 1, "#2");
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(NULL, ft_cmd_trim("\0"), 1, "#3");
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(NULL, ft_cmd_trim("  ""    "), 1, "#4");
}

void test_ft_cmd_trim_2(void)
{
	char	*expected0[] = {"echo", "\"abc\""};
	char	**actual = ft_cmd_trim("echo \"abc\"");
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, actual, 2, "#0");
	free_2d(actual);
	actual = ft_cmd_trim("echo \"a\"bc");
	char	*expected1[] = {"echo", "\"a\"bc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, actual, 2, "#1");
	free_2d(actual);
	actual = ft_cmd_trim("echo \"ab\"c");
	char	*expected2[] = {"echo", "\"ab\"c"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, actual, 2, "#2");
	free_2d(actual);
	actual = ft_cmd_trim("echo \"\"abc");
	char	*expected3[] = {"echo", "\"\"abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, actual, 2, "#3");
	free_2d(actual);
	actual = ft_cmd_trim("echo abc\"\"");
	char	*expected4[] = {"echo", "abc\"\""};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, actual, 2, "#4");
	free_2d(actual);
	actual = ft_cmd_trim("ech'o' abc");
	char	*expected5[] = {"ech'o'", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected5, actual, 2, "#5");
	free_2d(actual);
	actual = ft_cmd_trim("echo\"\" abc");
	char	*expected6[] = {"echo\"\"", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected6, actual, 2, "#6");
	free_2d(actual);
	actual = ft_cmd_trim("\"\"echo abc");
	char	*expected7[] = {"\"\"echo", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected7, actual, 2, "#7");
	free_2d(actual);
	actual = ft_cmd_trim("\"echo\" abc");
	char	*expected8[] = {"\"echo\"", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected8, actual, 2, "#8");
	free_2d(actual);
	actual = ft_cmd_trim("\"echo\"\"\" abc");
	char	*expected9[] = {"\"echo\"\"\"", "abc"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected9, actual, 2, "#9");
	free_2d(actual);
	actual = ft_cmd_trim("\"   /   \"   echo   tr -d  ");
	char	*expected10[] = {"\"   /   \"", "echo", "tr", "-d"};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected10, actual, 4, "#10");
	free_2d(actual);
	actual = ft_cmd_trim("cd ..");
	char	*expected11[] = {"cd", ".."};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected11, actual, 2, "#11");
	free_2d(actual);
}

void test_ft_cmd_trim_3(void)
{
	char	*expected0[] = {"\" sass \"\"    l  \""};
	char	**actual = ft_cmd_trim("\" sass \"\"    l  \"");
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected0, actual, 1);
	free_2d(actual);
}

// Haven't checked if this checks only the stuff it's supposed to.
// Or if it tests anything at all.
void test_ft_cmd_trim_1337(void)
{
	char	*expected[] = {"<Makefile", "cat|", "echo", "\"$PWD 'hola'\"", "~/src", "|", "'tr'", "-d", "/", ">outfile"};
	char	**actual = ft_cmd_trim("<Makefile cat| echo \"$PWD 'hola'\" ~/src | 'tr' -d / >outfile");

	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, 10);
	free_2d(actual);
}

int test_ft_cmd_trim(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_cmd_trim_0);
	RUN_TEST(test_ft_cmd_trim_1);
	RUN_TEST(test_ft_cmd_trim_2);
	RUN_TEST(test_ft_cmd_trim_3);
	RUN_TEST(test_ft_cmd_trim_1337);
	return UNITY_END();
}
