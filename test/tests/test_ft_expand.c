/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:46:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/04 16:22:20 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"

t_vec	vars;

void	set_vars(void)
{
	if (vec_new(&vars, 10, sizeof(t_env)) < 0)
		exit (1);
	if(ft_putenv(&vars, "SHELL=/bin/zsh") < 0)
		exit (1);
	if(ft_putenv(&vars, "HOME=/Users/tspoof") < 0)
		exit (1);
	if(ft_putenv(&vars, "PWD=/Users/tspoof/Documents/HIVE/minishell") < 0)
		exit (1);
}


// Variable expand
void test_ft_var_end_0(void)
{
	char *str = "$PWD";

	TEST_ASSERT_EQUAL_HEX32(&(str[4]), ft_var_end(str));
}

void test_ft_var_end_1(void)
{
	char *str = "$ PWD";

	TEST_ASSERT_EQUAL_STRING(&(str[1]), ft_var_end(str));
}

void test_ft_var_end_2(void)
{
	char *str = "$PWD$";

	TEST_ASSERT_EQUAL_STRING(&(str[4]), ft_var_end(str));
}

void test_ft_var_end_3(void)
{
	char *str = "$PWD $";

	TEST_ASSERT_EQUAL_STRING(&(str[4]), ft_var_end(str));
}

void test_ft_var_end_4(void)
{
	char *str = "$PWD!";

	TEST_ASSERT_EQUAL_STRING(&(str[4]), ft_var_end(str));
}

void test_ft_var_expand_0(void)
{
	char *expected = "/Users/tspoof/Documents/HIVE/minishell";
	char *result = ft_var_expand(vars, "$PWD");
	TEST_ASSERT_EQUAL_STRING(expected, result);
}
void test_ft_var_expand_1(void)
{
	char *expected = "/Users/tspoof/Documents/HIVE/minishell";
	char *result = ft_var_expand(vars, "$PWD test");
	TEST_ASSERT_EQUAL_STRING(expected, result);
}
void test_ft_var_expand_2(void)
{
	char *expected = "/Users/tspoof/Documents/HIVE/minishell";
	char *result = ft_var_expand(vars, "$PWD$PWD");
	TEST_ASSERT_EQUAL_STRING(expected, result);
}
void test_ft_var_expand_3(void)
{
	char *expected = "$";
	char *result = ft_var_expand(vars, "$");
	TEST_ASSERT_EQUAL_STRING(expected, result);
}
void test_ft_var_expand_4(void)
{
	char *expected = NULL;
	char *result = ft_var_expand(vars, "$SOMETHING");
	TEST_ASSERT_EQUAL_STRING(expected, result);
}
void test_ft_var_expand_5(void)
{
	char *expected = NULL;
	char *result = ft_var_expand(vars, "$SOMETHING$");
	TEST_ASSERT_EQUAL_STRING(expected, result);
}
void test_ft_var_expand_6(void)
{
	char *expected = "$";
	char *result = ft_var_expand(vars, "$ ");
	TEST_ASSERT_EQUAL_STRING(expected, result);
}

// ft_expand_token

void test_ft_expand_token_0(void)
{
	char *expected = "/Users/tspoof/Documents/HIVE/minishell";
	char *actual = ft_expand_token(vars, "$PWD");
	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_ft_expand_token_1(void)
{
	char *expected = "/Users/tspoof/Documents/HIVE/minishell$";
	char *actual = ft_expand_token(vars, "$PWD$");
	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_ft_expand_token_2(void)
{
	char *expected = "";
	char *actual = ft_expand_token(vars, "$SOMETHING");
	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_ft_expand_token_3(void)
{
	char *expected = "$";
	char *actual = ft_expand_token(vars, "$");
	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_ft_expand_token_4(void)
{
	char *expected = "$ test";
	char *actual = ft_expand_token(vars, "$ test");
	TEST_ASSERT_EQUAL_STRING(expected, actual);

}

// $ tests
void test_ft_expand_$0(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "/Users/tspoof/Documents/HIVE/minishell";
	line[0] = "$PWD";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}

void test_ft_expand_$1(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "$";
	line[0] = "$";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}

void test_ft_expand_$2(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "";
	line[0] = "$NOTEXISTING";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}

void test_ft_expand_$3(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "/Users/tspoof/Documents/HIVE/minishell$";
	line[0] = "$PWD$";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}

void test_ft_expand_$4(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "$";
	line[0] = "$NOTEXISTING$";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}

void test_ft_expand_$5(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "$ HOME";
	line[0] = "$ HOME";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}

void test_ft_expand_$6(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "/Users/tspoof/Users/tspoof";
	line[0] = "$HOME$HOME";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}


// ~ tests
void test_ft_expand_0(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "/Users/tspoof";
	line[0] = "~";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}

void test_ft_expand_1(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "test~ hehe";
	line[0] = "test~ hehe";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}

void test_ft_expand_2(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "test /Users/tspoof hehe";
	line[0] = "test ~ hehe";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}

void test_ft_expand_3(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "~~";
	line[0] = "~~";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}

void test_ft_expand_4(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "~SHELL";
	line[0] = "~SHELL";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line);
}

// void test_ft_expand_1337(void)
// {
// 	char **expected = calloc(2, sizeof(char *));
// 	char **line = calloc(2, sizeof(char *));
// 	char *expected[] = {"$", "/Users/tspoof", "/Users/tspoof$", "", "$", "/Users/tspoof", "~~", "$ HOME", NULL};
// 	char *line[] = {"$", "$HOME", "$HOME$", "$NOTEXISTING", "$NOTEXISTING$", "~", "~~", "$ HOME", NULL};

// 	ft_expand(vars, line);
// 	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
// }

int test_ft_expand(void)
{
	UNITY_BEGIN();
	set_vars();

	RUN_TEST(test_ft_var_end_0);
	RUN_TEST(test_ft_var_end_1);
	RUN_TEST(test_ft_var_end_2);
	RUN_TEST(test_ft_var_end_3);
	RUN_TEST(test_ft_var_end_4);
	RUN_TEST(test_ft_var_expand_0);
	RUN_TEST(test_ft_var_expand_1);
	RUN_TEST(test_ft_var_expand_2);
	RUN_TEST(test_ft_var_expand_3);
	RUN_TEST(test_ft_var_expand_4);
	RUN_TEST(test_ft_var_expand_5);
	RUN_TEST(test_ft_var_expand_6);
	RUN_TEST(test_ft_expand_token_0);
	RUN_TEST(test_ft_expand_token_1);
	RUN_TEST(test_ft_expand_token_2);
	RUN_TEST(test_ft_expand_token_3);
	RUN_TEST(test_ft_expand_token_4);
	RUN_TEST(test_ft_expand_$0);
	RUN_TEST(test_ft_expand_$1);
	RUN_TEST(test_ft_expand_$2);
	RUN_TEST(test_ft_expand_$3);
	RUN_TEST(test_ft_expand_$4);
	RUN_TEST(test_ft_expand_$5);
	RUN_TEST(test_ft_expand_$6);
	RUN_TEST(test_ft_expand_1);
	RUN_TEST(test_ft_expand_2);
	RUN_TEST(test_ft_expand_3);
	RUN_TEST(test_ft_expand_4);
	// RUN_TEST(test_ft_expand_1337);
	return UNITY_END();
}
