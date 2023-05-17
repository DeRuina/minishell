#include "unity.h"
#include "minishell.h"

t_vec	env;

void	set_env(void)
{
	if (vec_new(&env, 10, sizeof(t_env)) < 0)
		exit (1);
	if(ft_putenv(&env, "PATH=/Users/tspoof/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/") < 0)
		exit (1);
}

void test_ft_get_exec_path_0(void)
{
	char *expected = "/bin/ls";
	char *actual = ft_get_exec_path(env, "ls");

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

int test_ft_get_exec_path(void)
{
	UNITY_BEGIN();
	set_env();
	RUN_TEST(test_ft_get_exec_path_0);
	return UNITY_END();
}
