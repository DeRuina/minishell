/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_split_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:47:23 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/17 13:50:13 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"

void test_ft_split_operators_0(void)
{
	char	*expected0[] = {"echo", NULL};
	char	*array0[] = {"echo", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_split_operators(array0), 2, "#0");
	char	*expected1[] = {"echo", "|", NULL};
	char	*array1[] = {"echo", "|", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_split_operators(array1), 3, "#1");
	char	*expected2[] = {"echo", "|", NULL};
	char	*array2[] = {"echo|", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, ft_split_operators(array2), 3, "#2");
	char	**expected4 = NULL;
	char	**array4 = NULL;
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, ft_split_operators(array4), 1, "#4");
	char	*expected5[] = {"echo", "|", "ls", NULL};
	char	*array5[] = {"echo", "|ls", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected5, ft_split_operators(array5), 4, "#5");
}

void test_ft_split_operators_1(void)
{
	char	*expected0[] = {"echo", "|", "|", NULL};
	char	*array0[] = {"echo||", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_split_operators(array0), 4, "#0");
	char	*expected1[] = {"echo", "|", "echo" ,"|", NULL};
	char	*array1[] = {"echo|echo|", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_split_operators(array1), 5, "#1");
	char	*expected2[] = {"<", "Makefile", NULL};
	char	*array2[] = {"<Makefile", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, ft_split_operators(array2), 3, "#2");
	char	*expected3[] = {"<", "Makefile", ">", NULL};
	char	*array3[] = {"<Makefile>", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, ft_split_operators(array3), 4, "#3");
	char	*expected4[] = {"echo", "\"echo\"", "|", "cat", "-e", NULL};
	char	*array4[] = {"echo", "\"echo\"|", "cat", "-e", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, ft_split_operators(array4), 6, "#4");
	char	*expected5[] = {"echo", "\"echo\"", "|", "cat", "-e", NULL};
	char	*array5[] = {"echo", "\"echo\"|cat", "-e", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected5, ft_split_operators(array5), 6, "#5");
	char	*expected6[] = {"/Users/druina/Desktop/github/minishellGitHub", NULL};
	char	*array6[] = {"/Users/druina/Desktop/github/minishellGitHub", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected6, ft_split_operators(array6), 2, "#6");
	char	*expected7[] = {"echo", "\"/Users/druina/Desktop/github/minishellGitHub\"", "|", "cat", "-e", NULL};
	char	*array7[] = {"echo", "\"/Users/druina/Desktop/github/minishellGitHub\"|cat", "-e", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected7, ft_split_operators(array7), 6, "#7");
	char	*expected8[] = {"<", "file.txt", ">", "outfile", NULL};
	char	*array8[] = {"<file.txt>outfile", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected8, ft_split_operators(array8), 5, "#8");
	char	*expected9[] = {"<", "file.txt", ">>", "outfile", NULL};
	char	*array9[] = {"<file.txt>>outfile", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected9, ft_split_operators(array9), 5, "#9");
	char	*expected10[] = {"<", "file.txt", ">", "in", ">", "outfile", NULL};
	char	*array10[] = {"<", "file.txt>", "in", ">outfile", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected10, ft_split_operators(array10), 7, "#10");
	char	*expected11[] = {"<", "file.txt", ">", "in", ">>", "outfile", NULL};
	char	*array11[] = {"<", "file.txt>in>>", "outfile", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected11, ft_split_operators(array11), 7, "#11");
	char	*expected12[] = {"<<", "file", ">>", "outfile", NULL};
	char	*array12[] = {"<<file>>outfile", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected12, ft_split_operators(array12), 5, "#12");
	char	*expected13[] = {"<<", "file", ">", "in", ">>", "outfile", NULL};
	char	*array13[] = {"<<file>", "in>>outfile", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected13, ft_split_operators(array13), 7, "#13");


}

void test_ft_split_operators_2(void)
{
	char	*expected0[] = {"<", "Makefile", "cat" , "|", "echo", "\"/Users/druina/Desktop/github/minishell 'hola'\"", "/Users/druina/src", "|", "'tr'", "-d", "/", ">", "outfile", NULL};
	char	*array0[] = {"<Makefile", "cat|", "echo", "\"/Users/druina/Desktop/github/minishell 'hola'\"", "/Users/druina/src", "|", "'tr'", "-d", "/", ">outfile", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_split_operators(array0), 14, "#0");
	char	*expected1[] = {"<", "file.txt", ">", "in", "echo", "hey", ">>", "outfile", NULL};
	char	*array1[] = {"<", "file.txt", ">in", "echo", "hey" ">>", "outfile", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_split_operators(array1), 9, "#1");
}

int test_ft_split_operators(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_split_operators_0);
	RUN_TEST(test_ft_split_operators_1);
	RUN_TEST(test_ft_split_operators_2);
	return UNITY_END();
}
