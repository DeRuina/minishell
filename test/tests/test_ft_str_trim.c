/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_str_trim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:47:16 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/19 09:52:32 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"

void test_ft_str_trim_0(void)
{
	char	*expected0[] = {"echo", NULL};
	char	*array0[] = {"'echo'", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_str_trim(array0), 2, "#0");
	char	*expected1[] = {"echo", NULL};
	char	*array1[] = {"\"echo\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_str_trim(array1), 2, "#1");
	char	*expected2[] = {"tr", NULL};
	char	*array2[] = {"'tr'", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, ft_str_trim(array2), 2, "#2");
	char	*expected3[] = {NULL , NULL};
	char	*array3[] = {NULL, NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, ft_str_trim(array3), 2, "#3");
	char	**expected4 = NULL;
	char	**array4 = NULL;
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, ft_str_trim(array4), 1, "#4");
	char	*expected5[] = {"echo", "hey", "|", "tr", "-d", "e", NULL};
	char	*array5[] = {"'echo'", "hey", "|", "\"tr\"", "-d", "e", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected5, ft_str_trim(array5), 7, "#5");

}

void test_ft_str_trim_1(void)
{
	char	*expected0[] = {"echo", "hey 'you'", NULL};
	char	*array0[] = {"echo", "\"hey 'you'\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_str_trim(array0), 3, "#0");
	char	*expected1[] = {"echo", "hey 'you'", "|", "tr", "-d", "e", NULL};
	char	*array1[] = {"'echo'", "\"hey 'you'\"", "|", "\"tr\"", "'-d'", "\"e\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_str_trim(array1), 7, "#1");
	char	*expected2[] = {"/Users/druina/Desktop/github/minishellGitHub 'hola'", NULL};
	char	*array2[] = {"\"/Users/druina/Desktop/github/minishellGitHub 'hola'\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, ft_str_trim(array2), 2, "#2");
	char	*expected3[] = {"echo", "/Users/druina/Desktop/github/minishellGitHub", "|", "cat", "-e", NULL};
	char	*array3[] = {"'echo'", "\"/Users/druina/Desktop/github/minishellGitHub\"", "|", "'cat'", "\"-e\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, ft_str_trim(array3), 6, "#3");
}


void test_ft_str_trim_2(void)
{
	char	**expected0 = NULL;
	char	*array0[] = {"\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_str_trim(array0), 2, "#0");
	char	**expected1 = NULL;
	char	*array1[] = {"'", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_str_trim(array1), 2, "#1");
	char	**expected2 = NULL;
	char	*array2[] = {"\"\"\'", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, ft_str_trim(array2), 2, "#2");
	char	**expected3 = NULL;
	char	*array3[] = {"\'\'\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, ft_str_trim(array3), 2, "#3");
	char	**expected4 = NULL;
	char	*array4[] = {"\'\"\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, ft_str_trim(array4), 2, "#4");
	char	**expected5 = NULL;
	char	*array5[] = {"\'\'\'", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected5, ft_str_trim(array5), 2, "#5");
	char	**expected6 = NULL;
	char	*array6[] = {"\"\"\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected6, ft_str_trim(array6), 2, "#6");
	char	*expected7[] = {"\"\"", NULL};;
	char	*array7[] = {"\"\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected7, ft_str_trim(array7), 1, "#7");
	char	*expected8[] = {"''", NULL};;
	char	*array8[] = {"''", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected8, ft_str_trim(array8), 1, "#8");

}

void test_ft_str_trim_3(void)
{
	char	**expected0 = NULL;
	char	*array0[] = {"echo\" abc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_str_trim(array0), 2, "#0");
	char	**expected1 = NULL;
	char	*array1[] = {"echo a\"bc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_str_trim(array1), 2, "#1");
	char	**expected2 = NULL;
	char	*array2[] = {"echo' a\"bc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, ft_str_trim(array2), 2, "#2");
	char	**expected3 = NULL;
	char	*array3[] = {"echo\" 'abc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, ft_str_trim(array3), 2, "#3");
	char	**expected4 = NULL;
	char	*array4[] = {"ech\"o 'abc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, ft_str_trim(array4), 2, "#4");
	char	**expected5 = NULL;
	char	*array5[] = {"\"echo abc''", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected5, ft_str_trim(array5), 2, "#5");
	char	*expected6[] = {"echo abc", NULL};
	char	*array6[] = {"echo\" a\"bc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected6, ft_str_trim(array6), 2, "#6");
	char	*expected7[] = {"echo abc", NULL};
	char	*array7[] = {"echo\" \"abc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected7, ft_str_trim(array7), 2, "#7");
	char	*expected8[] = {"echo abc", NULL};
	char	*array8[] = {"ech\"o \"abc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected8, ft_str_trim(array8), 2, "#8");
	char	*expected9[] = {"echo abc", NULL};
	char	*array9[] = {"\"echo abc\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected9, ft_str_trim(array9), 2, "#9");
}


void test_ft_str_trim_4(void)
{
	char	*expected0[] = {"echo", "abc"};
	char	*array0[] = {"echo", "\"abc\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected0, ft_str_trim(array0), 2, "#0");
	char	*expected1[] = {"echo", "abc"};
	char	*array1[] = {"echo", "\"a\"bc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, ft_str_trim(array1), 2, "#1");
	char	*expected2[] = {"echo", "abc"};
	char	*array2[] = {"echo", "\"ab\"c", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, ft_str_trim(array2), 2, "#2");
	char	*expected3[] = {"echo", "abc"};
	char	*array3[] = {"echo", "\"\"abc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, ft_str_trim(array3), 2, "#3");
	char	*expected4[] = {"echo", "abc"};
	char	*array4[] = {"echo", "abc\"\"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, ft_str_trim(array4), 2, "#4");
	char	*expected5[] = {"echo", "abc"};
	char	*array5[] = {"ech\"o\"", "abc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected5, ft_str_trim(array5), 2, "#5");
	char	*expected6[] = {"echo", "abc"};
	char	*array6[] = {"echo\"\"", "abc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected6, ft_str_trim(array6), 2, "#6");
	char	*expected7[] = {"echo", "abc"};
	char	*array7[] = {"\"\"echo", "abc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected7, ft_str_trim(array7), 2, "#7");
	char	*expected8[] = {"echo", "abc"};
	char	*array8[] = {"\"echo\"", "abc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected8, ft_str_trim(array8), 2, "#8");
	char	*expected9[] = {"echo", "abc"};
	char	*array9[] = {"\"echo\"\"\"", "abc", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected9, ft_str_trim(array9), 2, "#9");
}



int test_ft_str_trim(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_str_trim_0);
	RUN_TEST(test_ft_str_trim_1);
	RUN_TEST(test_ft_str_trim_2);
	RUN_TEST(test_ft_str_trim_3);
	RUN_TEST(test_ft_str_trim_4);
	return UNITY_END();
}
