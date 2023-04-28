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

void test_ft_expand_0(void)
{
	char *expected[2];
	char path[100];
	char *line[] = {"$PWD", NULL};

	getcwd(path, 100);
	expected[0] = path;
	expected[1] = NULL;

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_1(void)
{
	char *expected = getenv("HOME");
	char *line = "~";

	ft_expand(vars, &line);
	TEST_ASSERT_EQUAL_STRING(expected, line);
}

void test_ft_expand_2(void)
{
	char *expected[] = {"test~", "hehe"};
	char *line[] = {"test~ hehe"};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 2);
}

void test_ft_expand_3(void)
{
	char *expected[] = {"test", getenv("HOME"), "hehe"};
	char *line[] = {"test ~ hehe"};

	ft_expand(vars, line);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, line, 3);
}

void test_ft_expand_4(void)
{
	char expected[100];
	chdir("..");
	getcwd(expected, 100);
	char *line = "$PWD";

	ft_expand(vars, &line);
	TEST_ASSERT_EQUAL_STRING(expected, line);
}

int test_ft_expand(void)
{
	UNITY_BEGIN();
	set_vars();
	RUN_TEST(test_ft_expand_0);
	RUN_TEST(test_ft_expand_1);
	RUN_TEST(test_ft_expand_2);
	RUN_TEST(test_ft_expand_3);
	RUN_TEST(test_ft_expand_4);
	return UNITY_END();
}
