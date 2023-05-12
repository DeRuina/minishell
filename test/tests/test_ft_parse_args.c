/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_parse_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:47:04 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/12 17:21:00 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"

void test_ft_parse_args_0(void)
{
	t_node	expected0 = {.full_cmd = {"echo", "hello"}, .path_name = "echo", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	char	*array0[] = {"echo", "hello", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected0, new_node(&array0), sizeof(expected0), "#0 node 0");
	t_node	expected1 = {.full_cmd = {"cd", ".."}, .path_name = "cd", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	char	*array1[] = {"cd", "..", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected1, new_node(&array1), sizeof(expected1), "#1 node 0");
	t_node	expected2 = {.full_cmd = {"echo", "'hello'"}, .path_name = "echo", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	char	*array2[] = {"echo", "'hello'", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected2, new_node(&array2), sizeof(expected2), "#2 node 0");
	t_node	expected3 = {.full_cmd = {"echo abc"}, .path_name = "echo abc", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	char	*array3[] = {"echo\" \"abc", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected3, new_node(&array3), sizeof(expected3), "#3 node 0");
	t_node	expected4 = {.full_cmd = {"echo abc"}, .path_name = "echo abc", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	char	*array4[] = {"ech\"o \"abc", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected4, new_node(&array4), sizeof(expected4), "#4 node 0");
	t_node	expected5 = {.full_cmd = {"echo abc"}, .path_name = "echo abc", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	char	*array5[] = {"\"echo abc\"", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected5, new_node(&array5), sizeof(expected5), "#5 node 0");
	t_node	expected6 = {.full_cmd = {"/"}, .path_name = "/", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	char	*array6[] = {"/", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected6, new_node(&array6), sizeof(expected6), "#6 node 0");
	t_node	expected7 = {.full_cmd = {"tr", "-d", "a"}, .path_name = "tr", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	char	*array7[] = {"tr", "-d", "a", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected7, new_node(&array7), sizeof(expected7), "#7 node 0");
	t_node	expected8 = {.full_cmd = {"echo", "/Users/druina/Desktop/github/minishellGitHub 'hola'"}, .path_name = "echo", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	char	*array8[] = {"echo", "/Users/druina/Desktop/github/minishellGitHub 'hola'", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected8, new_node(&array8), sizeof(expected8), "#8 node 0");
	t_node	*expected9 = NULL;
	char	**array9 = NULL;
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected9, new_node(&array9), sizeof(expected9), "#9 node 0");
	t_node	*expected10 = NULL;
	char	*array10[] ={NULL, NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected10, new_node(&array10), sizeof(expected10), "#10 node 0");

}

void test_ft_parse_args_1(void)
{
	t_node	expected0 = {.full_cmd = {"echo", "hello"}, .path_name = "echo", /*.pid = -1, .infile = 0, .outfile = 3, .next = NULL*/};
	char	*array0[] = {"echo", "hello" ">" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected0, new_node(&array0), sizeof(expected0), "#0 node 0");
	t_node	expected1 = {.full_cmd = {"cd", ".."}, .path_name = "cd", /*.pid = -1, .infile = 3, .outfile = 1, .next = NULL*/};
	char	*array1[] = { "<", "infile", "cd", "..", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected1, new_node(&array1), sizeof(expected1), "#1 node 0");
	t_node	expected2 = {.full_cmd = {"echo", "hello"}, .path_name = "echo", /*.pid = -1, .infile = 0, .outfile = 3, .next = NULL*/};
	char	*array2[] = {"echo", "hello" ">" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected2, new_node(&array2), sizeof(expected2), "#2 node 0");
	t_node	expected3 = {.full_cmd = {"echo", "hello"}, .path_name = "echo", /*.pid = -1, .infile = 3, .outfile = 4, .next = NULL*/};
	char	*array3[] = {"<", "infile", "echo", "hello" ">" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected3, new_node(&array3), sizeof(expected3), "#3 node 0");
	t_node	expected4 = {.full_cmd = {"echo", "hello"}, .path_name = "echo", /*.pid = -1, .infile = 3, .outfile = 4, .next = NULL*/};
	char	*array4[] = {"<", "infile", "echo", "hello" ">>" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected4, new_node(&array4), sizeof(expected4), "#4 node 0");
	t_node	expected5 = {.full_cmd = {"echo", "hello"}, .path_name = "echo", /*.pid = -1, .infile = 5, .outfile = 4, .next = NULL*/};
	char	*array5[] = {"<<", "infile", "echo", "hello" ">>" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected5, new_node(&array5), sizeof(expected5), "#5 node 0");
	t_node	expected6 = {.full_cmd = {"echo", "hello"}, .path_name = "echo", /*.pid = -1, .infile = 5, .outfile = 4, .next = NULL*/};
	char	*array6[] = {"<<", "infile", "echo", "hello" ">" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected6, new_node(&array6), sizeof(expected6), "#6 node 0");


}

void test_ft_parse_args_2(void)
{
	t_node	expected0 = {.full_cmd = {"echo", "hello \n hi"}, .path_name = "echo", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	char	*array0[] = {"echo", "hello \n hi" "|" "grep" "i", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected0, new_node(&array0), sizeof(expected0), "#0 node 0");
	t_node	expected1 = {.full_cmd = {"grep", "i"}, .path_name = "grep", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected1, new_node(&array0), sizeof(expected1), "#0 node 1");
	t_node	expected2 = {.full_cmd = {"echo", "hello"}, .path_name = "echo", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	char	*array1[] = {"echo", "hello", "|", "grep", "i", "|", "cat", "-e", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected2, new_node(&array1), sizeof(expected2), "#1 node 0");
	t_node	expected3 = {.full_cmd = {"grep", "i"}, .path_name = "grep", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected3, new_node(&array1), sizeof(expected3), "#1 node 1");
	t_node	expected4 = {.full_cmd = {"cat", "-e"}, .path_name = "cat", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected4, new_node(&array1), sizeof(expected4), "#1 node 2");
	t_node	expected5 = {.full_cmd = {"echo", "hello"}, .path_name = "echo", /*.pid = -1, .infile = 3, .outfile = 4, .next = NULL*/};
	char	*array2[] = {"<", "infile", "echo", "hello", "|", "grep", "i", "|", "cat", "-e", ">", "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected5, new_node(&array2), sizeof(expected5), "#2 node 0");
	t_node	expected6 = {.full_cmd = {"grep", "i"}, .path_name = "grep", /*.pid = -1, .infile = 3, .outfile = 4, .next = NULL*/};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected6, new_node(&array2), sizeof(expected6), "#2 node 1");
	t_node	expected7 = {.full_cmd = {"cat", "-e"}, .path_name = "cat", /*.pid = -1, .infile = 3, .outfile = 4, .next = NULL*/};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected7, new_node(&array2), sizeof(expected7), "#2 node 2");


}

void test_ft_parse_args_3(void)
{
	t_node	expected0 = {.full_cmd = {"Makefile", "cat"}, .path_name = "cat", /*.pid = -1, .infile = 3, .outfile = 1, .next = NULL*/};
	char	*array0[] = {"<", "Makefile", "cat" , "|", "echo", "\"/Users/druina/Desktop/github/minishell 'hola'\"", "/Users/druina/src", "|", "'tr'", "-d", "/", ">", "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected0, new_node(&array0), sizeof(expected0), "#0 node 0");
	t_node	expected1 = {.full_cmd = {"echo", "\"/Users/druina/Desktop/github/minishell 'hola'\"", "/Users/druina/src"}, .path_name = "echo", /*.pid = -1, .infile = 0, .outfile = 1, .next = NULL*/};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected1, new_node(&array0), sizeof(expected1), "#0 node 1");
	t_node	expected2 = {.full_cmd = {"tr", "-d", "/"}, .path_name = "tr", /*.pid = -1, .infile = 0, .outfile = 3, .next = NULL*/};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected2, new_node(&array0), sizeof(expected2), "#0 node 2");
}


int test_ft_parse_args(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_parse_args_0);
	RUN_TEST(test_ft_parse_args_1);
	RUN_TEST(test_ft_parse_args_2);
	RUN_TEST(test_ft_parse_args_3);

	return UNITY_END();
}
