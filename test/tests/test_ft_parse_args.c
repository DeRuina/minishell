/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_parse_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:47:04 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/04 13:46:28 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"

void test_ft_parse_args_0(void)
{
	t_node	expected0 = {.full_cmd = {"echo", "hello"}, .full_path = "echo", .pid = -1, .infile = 0, .outfile = 1, .next_node = NULL};
	char	*array0[] = {"echo", "hello", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected0, ft_parse_args(array0), sizeof(expected0), "#0 node 0");
	t_node	expected1 = {.full_cmd = {"cd", ".."}, .full_path = "cd", .pid = -1, .infile = 0, .outfile = 1, .next_node = NULL};
	char	*array1[] = {"cd", "..", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected1, ft_parse_args(array1), sizeof(expected1), "#1 node 0");
	t_node	expected2 = {.full_cmd = {"echo", "'hello'"}, .full_path = "echo", .pid = -1, .infile = 0, .outfile = 1, .next_node = NULL};
	char	*array2[] = {"echo", "'hello'", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected2, ft_parse_args(array2), sizeof(expected2), "#2 node 0");
	t_node	expected3 = {.full_cmd = {"echo abc"}, .full_path = "echo abc", .pid = -1, .infile = 0, .outfile = 1, .next_node = NULL};
	char	*array3[] = {"echo\" \"abc", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected3, ft_parse_args(array3), sizeof(expected3), "#3 node 0");
	t_node	expected4 = {.full_cmd = {"echo abc"}, .full_path = "echo abc", .pid = -1, .infile = 0, .outfile = 1, .next_node = NULL};
	char	*array4[] = {"ech\"o \"abc", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected4, ft_parse_args(array4), sizeof(expected4), "#4 node 0");
	t_node	expected5 = {.full_cmd = {"echo abc"}, .full_path = "echo abc", .pid = -1, .infile = 0, .outfile = 1, .next_node = NULL};
	char	*array5[] = {"\"echo abc\"", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected5, ft_parse_args(array5), sizeof(expected5), "#5 node 0");
	t_node	expected6 = {.full_cmd = {"/"}, .full_path = "/", .pid = -1, .infile = 0, .outfile = 1, .next_node = NULL};
	char	*array6[] = {"/", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected6, ft_parse_args(array6), sizeof(expected6), "#6 node 0");
	t_node	expected7 = {.full_cmd = {"tr", "-d", "a"}, .full_path = "tr", .pid = -1, .infile = 0, .outfile = 1, .next_node = NULL};
	char	*array7[] = {"tr", "-d", "a", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected7, ft_parse_args(array7), sizeof(expected7), "#7 node 0");
	t_node	expected8 = {.full_cmd = {"echo", "/Users/druina/Desktop/github/minishellGitHub 'hola'"}, .full_path = "echo", .pid = -1, .infile = 0, .outfile = 1, .next_node = NULL};
	char	*array8[] = {"echo", "/Users/druina/Desktop/github/minishellGitHub 'hola'", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected8, ft_parse_args(array8), sizeof(expected8), "#8 node 0");
	t_node	*expected9 = NULL;
	char	**array9 = NULL;
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected9, ft_parse_args(array9), sizeof(expected9), "#9 node 0");
	t_node	*expected10 = NULL;
	char	*array10[] ={NULL, NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected10, ft_parse_args(array10), sizeof(expected10), "#10 node 0");

}

void test_ft_parse_args_1(void)
{
	t_node	expected0 = {.full_cmd = {"echo", "hello"}, .full_path = "echo", .pid = -1, .infile = 0, .outfile = 3, .next_node = NULL};
	char	*array0[] = {"echo", "hello" ">" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected0, ft_parse_args(array0), sizeof(expected0), "#0 node 0");
	t_node	expected1 = {.full_cmd = {"cd", ".."}, .full_path = "cd", .pid = -1, .infile = 3, .outfile = 1, .next_node = NULL};
	char	*array1[] = { "<", "infile", "cd", "..", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected1, ft_parse_args(array1), sizeof(expected1), "#1 node 0");
	t_node	expected2 = {.full_cmd = {"echo", "hello"}, .full_path = "echo", .pid = -1, .infile = 0, .outfile = 3, .next_node = NULL};
	char	*array2[] = {"echo", "hello" ">" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected2, ft_parse_args(array2), sizeof(expected2), "#2 node 0");
	t_node	expected3 = {.full_cmd = {"echo", "hello"}, .full_path = "echo", .pid = -1, .infile = 3, .outfile = 4, .next_node = NULL};
	char	*array3[] = {"<", "infile", "echo", "hello" ">" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected3, ft_parse_args(array3), sizeof(expected3), "#3 node 0");
	t_node	expected4 = {.full_cmd = {"echo", "hello"}, .full_path = "echo", .pid = -1, .infile = 3, .outfile = 4, .next_node = NULL};
	char	*array4[] = {"<", "infile", "echo", "hello" ">>" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected4, ft_parse_args(array4), sizeof(expected4), "#4 node 0");
	t_node	expected5 = {.full_cmd = {"echo", "hello"}, .full_path = "echo", .pid = -1, .infile = 5, .outfile = 4, .next_node = NULL};
	char	*array5[] = {"<<", "infile", "echo", "hello" ">>" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected5, ft_parse_args(array5), sizeof(expected5), "#5 node 0");
	t_node	expected6 = {.full_cmd = {"echo", "hello"}, .full_path = "echo", .pid = -1, .infile = 5, .outfile = 4, .next_node = NULL};
	char	*array6[] = {"<<", "infile", "echo", "hello" ">" "outfile", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected6, ft_parse_args(array6), sizeof(expected6), "#6 node 0");


}

void test_ft_parse_args_2(void)
{
	t_node	expected0 = {.full_cmd = {"echo", "hello \n hi"}, .full_path = "echo", .pid = -1, .infile = 0, .outfile = 3, .next_node = NULL};
	char	*array0[] = {"echo", "hello \n hi" "|" "grep" "i", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected0, ft_parse_args(array0), sizeof(expected0), "#0 node 0");
	t_node	expected0 = {.full_cmd = {"grep", "i"}, .full_path = "grep", .pid = -1, .infile = 0, .outfile = 3, .next_node = NULL};
	char	*array0[] = {"echo", "hello \n hi" "|" "grep" "i", NULL};
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&expected0, ft_parse_args(array0), sizeof(expected0), "#0 node 1");

}

void test_ft_parse_args_3(void)
{

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
