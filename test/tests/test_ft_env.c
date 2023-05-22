/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:46:45 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/22 08:08:28 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"
#include "parser.h"

char **env_vars;

void test_ft_env_getkey(void)
{
	TEST_ASSERT_EQUAL_STRING("HOME", ft_getkey("HOME=/Users/tspoof"));
}

void test_ft_env_getvalue(void)
{
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof", ft_getvalue("HOME=/Users/tspoof"));
}

void test_ft_putenv_0(void)
{
	t_vec	envs;

	if (vec_new(&envs, 10, sizeof(t_env)) < 0)
		exit (1);
	if (ft_putenv(&envs, "HOME=/Users/tspoof") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof", ((t_env *)envs.memory)[0].value);
}

void test_ft_putenv_1(void)
{
	t_vec	envs;

	if (vec_new(&envs, 10, sizeof(t_env)) < 0)
		exit (1);
	if (ft_putenv(&envs, "HOME=/Users/tspoof") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof", ((t_env *)envs.memory)[0].value);
	if (ft_putenv(&envs, "SHELL=/bin/zsh") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof", ((t_env *)envs.memory)[0].value);
	TEST_ASSERT_EQUAL_STRING("SHELL", ((t_env *)envs.memory)[1].key);
	TEST_ASSERT_EQUAL_STRING("/bin/zsh", ((t_env *)envs.memory)[1].value);
}

void test_ft_putenv_2(void)
{
	t_vec	envs;

	if (vec_new(&envs, 10, sizeof(t_env)) < 0)
		exit (1);
	if (ft_putenv(&envs, "HOME=/Users/tspoof") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof", ((t_env *)envs.memory)[0].value);
	if (ft_putenv(&envs, "HOME=/Users/tspoof/src") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof/src", ((t_env *)envs.memory)[0].value);
}

void test_ft_getenv_0(void)
{
	t_vec	envs;

	if (vec_new(&envs, 10, sizeof(t_env)) < 0)
		exit (1);
	if (ft_putenv(&envs, "HOME=/Users/tspoof") < 0)
		exit (1);
	if (ft_putenv(&envs, "SHELL=/bin/zsh") < 0)
		exit (1);
	if (ft_putenv(&envs, "LANG=en_US.UTF-8") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof", ft_getenv(envs, "HOME"));
	TEST_ASSERT_EQUAL_STRING("/bin/zsh", ft_getenv(envs, "SHELL"));
	TEST_ASSERT_EQUAL_STRING("en_US.UTF-8", ft_getenv(envs, "LANG"));
}
void test_ft_copyenv_0(void)
{
	t_vec envs;
	envs = ft_copyenv(env_vars);

	t_env *jee = (t_env *)envs.memory;
	size_t i = 0;
	while (i < envs.len)
	{
		ft_putstr_fd(jee[i].key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(jee[i].value, 1);
		i++;
	}
}
// void test_ft_strenv_0(void)
// {
// 	t_vec envs;
// 	envs = ft_copyenv(env_vars);
// 	char *envs_str;
// 	envs_str = ft_strenv(env_vars);
// 	ft_putendl_fd(envs_str, 1);
// }

int test_ft_env(char **envp)
{
	env_vars = envp;
	UNITY_BEGIN();
	RUN_TEST(test_ft_env_getkey);
	RUN_TEST(test_ft_env_getvalue);
	RUN_TEST(test_ft_putenv_0);
	RUN_TEST(test_ft_putenv_1);
	RUN_TEST(test_ft_putenv_2);
	RUN_TEST(test_ft_getenv_0);
	// RUN_TEST(test_ft_copyenv_0);
	// RUN_TEST(test_ft_strenv_0);
	return UNITY_END();
}
