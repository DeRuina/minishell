#include "unity.h"
#include "minishell.h"

void test_ft_putenv(void)
{
	t_env	envs[1];


	ft_putenv(&envs, "HOME=/Users/tspoof");
	TEST_ASSERT_TRUE_MESSAGE(envs[0].key == "HOME", "env.key is not HOME");
	TEST_ASSERT_TRUE_MESSAGE(envs[0].value == "/Users/tspoof", "env.value is not correct");
}

// void test_ft_getenv(void)
// {

// }


int test_ft_env(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_putenv);
	return UNITY_END();
}
