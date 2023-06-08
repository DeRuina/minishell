/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:46:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/08 13:58:14 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"
#include "parser.h"

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

	TEST_ASSERT_EQUAL_STRING(&(str[4]), ft_var_end(str));
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
	char *val = ft_strdup("$PWD");
	char *result = ft_var_expand(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(val);
}
void test_ft_var_expand_1(void)
{
	char *expected = "/Users/tspoof/Documents/HIVE/minishell";
	char *val = ft_strdup("$PWD test");
	char *result = ft_var_expand(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(val);
}
void test_ft_var_expand_2(void)
{
	char *expected = "/Users/tspoof/Documents/HIVE/minishell";
	char *val = ft_strdup("$PWD$PWD");
	char *result = ft_var_expand(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(val);
}
void test_ft_var_expand_3(void)
{
	char *expected = "$";
	char *val = ft_strdup("$");
	char *result = ft_var_expand(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(val);
	free(result);
}
void test_ft_var_expand_4(void)
{
	char *expected = NULL;
	char *val =  ft_strdup("$SOMETHING");
	char *result = ft_var_expand(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(val);
}
void test_ft_var_expand_5(void)
{
	char *expected = NULL;
	char *val = ft_strdup("$SOMETHING$");
	char *result = ft_var_expand(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(val);
}
void test_ft_var_expand_6(void)
{
	char *expected = "$";
	char *val = ft_strdup("$ ");
	char *result = ft_var_expand(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(result);
	free(val);
}

// ft_expand_token

void test_ft_expand_token_0(void)
{
	char *expected = "/Users/tspoof/Documents/HIVE/minishell";
	char *val = ft_strdup("$PWD");
	char *actual = ft_expand_token(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, actual);
	free(val);
	free(actual);
}

void test_ft_expand_token_1(void)
{
	char *expected = "/Users/tspoof/Documents/HIVE/minishell$";
	char *val = ft_strdup("$PWD$");
	char *actual = ft_expand_token(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, actual);
	free(val);
	free(actual);
}

void test_ft_expand_token_2(void)
{
	char *expected = "";
	char *val = ft_strdup("$SOMETHING");
	char *actual = ft_expand_token(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, actual);
	free(val);
	free(actual);
}

void test_ft_expand_token_3(void)
{
	char *expected = "$";
	char *val = ft_strdup("$");
	char *actual = ft_expand_token(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, actual);
	free(val);
	free(actual);
}

void test_ft_expand_token_4(void)
{
	char *expected = "$ test";
	char *val = ft_strdup("$ test");
	char *actual = ft_expand_token(vars, val);
	TEST_ASSERT_EQUAL_STRING(expected, actual);
	free(actual);
	free(val);
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
	free(line[0]);
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
	free(line[0]);
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
	free_2d(line);
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
	free(line[0]);
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
	free(line[0]);
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
	free(line[0]);
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
	free(line[0]);
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
	free(line[0]);
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
	free(line[0]);
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
	free(line[0]);
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
	free(line[0]);
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
	free(line[0]);
	free(line);
}

void test_ft_expand_5(void)
{
	char **expected = calloc(2, sizeof(char *));
	char **line = calloc(2, sizeof(char *));
	expected[0] = "/Users/tspoof /Users/tspoof";
	line[0] = "$HOME ~";

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
	free(expected);
	free(line[0]);
	free(line);
}

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
	RUN_TEST(test_ft_expand_0);
	RUN_TEST(test_ft_expand_1);
	RUN_TEST(test_ft_expand_2);
	RUN_TEST(test_ft_expand_3);
	RUN_TEST(test_ft_expand_4);
	RUN_TEST(test_ft_expand_5);
	free_envs(vars);
	vec_free(&vars);
	return UNITY_END();
}
