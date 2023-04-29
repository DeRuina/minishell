/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:46:26 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/29 16:46:28 by tspoof           ###   ########.fr       */
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


// $ tests
void test_ft_expand_$0(void)
{
	char *expected[] = {"/Users/tspoof/Documents/HIVE/minishell", NULL};
	char *line[] = {"$PWD", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_$1(void)
{
	char *expected[] = {"$", NULL};
	char *line[] = {"$", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_$2(void)
{
	char *expected[] = {NULL, NULL};
	char *line[] = {"$NOTEXISTING", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_$3(void)
{
	char *expected[] = {"/Users/tspoof/Documents/HIVE/minishell$", NULL};
	char *line[] = {"$PWD$", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_$4(void)
{
	char *expected[] = {"$", NULL};
	char *line[] = {"$NOTEXISTING$", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_$5(void)
{
	char *expected[] = {"$ HOME", NULL};
	char *line[] = {"$ HOME", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}


// ~ tests
void test_ft_expand_0(void)
{
	char *expected[] = {"/Users/tspoof", NULL};
	char *line[] = {"~", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_1(void)
{
	char *expected[] = {"test~ hehe", NULL};
	char *line[] = {"test~ hehe", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_2(void)
{
	char *expected[] = {"test /Users/tspoof hehe", NULL};
	char *line[] = {"test ~ hehe", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_3(void)
{
	char *expected[] = {"~~", NULL};
	char *line[] = {"~~", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_4(void)
{
	char *expected[] = {"/bin/zsh", NULL};
	char *line[] = {"~SHELL", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_1337(void)
{
	char *expected[] = {"$", "/Users/tspoof", "/Users/tspoof$", NULL, "$", "/Users/tspoof", "~~", "$ HOME", NULL};
	char *line[] = {"$", "$HOME", "$HOME$", "$NOTEXISTING", "$NOTEXISTING$", "~", "~~", "$ HOME", NULL};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

int test_ft_expand(void)
{
	UNITY_BEGIN();
	set_vars();
	RUN_TEST(test_ft_expand_$0);
	RUN_TEST(test_ft_expand_$1);
	RUN_TEST(test_ft_expand_$2);
	RUN_TEST(test_ft_expand_$3);
	RUN_TEST(test_ft_expand_$4);
	RUN_TEST(test_ft_expand_$5);
	RUN_TEST(test_ft_expand_1);
	RUN_TEST(test_ft_expand_2);
	RUN_TEST(test_ft_expand_3);
	RUN_TEST(test_ft_expand_4);
	RUN_TEST(test_ft_expand_1337);
	return UNITY_END();
}
