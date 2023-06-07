/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:46:45 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/07 11:49:23 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"
#include "parser.h"

char **env_vars;
t_vec	env_envs;

void	set_env_envs(void)
{
	if (vec_new(&env_envs, 10, sizeof(t_env)) < 0)
		exit (1);
	if(ft_putenv(&env_envs, "SHELL=/bin/zsh") < 0)
		exit (1);
	if(ft_putenv(&env_envs, "HOME3=/Users/tspoof9") < 0)
		exit (1);
	if(ft_putenv(&env_envs, "PWD=/Users/tspoof/Documents/HIVE/minishell") < 0)
		exit (1);
}


void test_ft_env_getkey(void)
{
	char *actual = ft_getkey("HOME=/Users/tspoof");
	TEST_ASSERT_EQUAL_STRING("HOME", actual);
	free(actual);
}

void test_ft_env_getvalue(void)
{
	char *actual = ft_getvalue("HOME=/Users/tspoof");
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof", actual);
	free(actual);
}

void test_ft_putenv_0(void)
{
	t_vec	envs;

	if (vec_new(&envs, 10, sizeof(t_env)) < 0)
		exit (1);
	if (ft_putenv(&envs, "HOME=/Users/tspoof1") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof1", ((t_env *)envs.memory)[0].value);
	free_envs(envs);
	vec_free(&envs);
}

void test_ft_putenv_1(void)
{
	t_vec	envs;

	if (vec_new(&envs, 10, sizeof(t_env)) < 0)
		exit (1);
	if (ft_putenv(&envs, "HOME=/Users/tspoof2") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof2", ((t_env *)envs.memory)[0].value);
	if (ft_putenv(&envs, "SHELL=/bin/zsh") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof2", ((t_env *)envs.memory)[0].value);
	TEST_ASSERT_EQUAL_STRING("SHELL", ((t_env *)envs.memory)[1].key);
	TEST_ASSERT_EQUAL_STRING("/bin/zsh", ((t_env *)envs.memory)[1].value);
	free_envs(envs);
	vec_free(&envs);
}

void test_ft_putenv_2(void)
{
	t_vec	envs;

	if (vec_new(&envs, 10, sizeof(t_env)) < 0)
		exit (1);
	if (ft_putenv(&envs, "HOME=/Users/tspoof3") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof3", ((t_env *)envs.memory)[0].value);
	if (ft_putenv(&envs, "HOME=/Users/tspoof/src") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof/src", ((t_env *)envs.memory)[0].value);
	free_envs(envs);
	vec_free(&envs);
}

// int	ft_putenv_key(t_vec *envs_vec, char *key, char *str)
void test_ft_putenv_key_0(void)
{
	t_vec	envs;
	char	*home = ft_strdup("HOME1");
	char	*dup1 = ft_strdup("/Users/tspoof");
	char	*dup2 = ft_strdup("/Users/tspoof/src");

	if (vec_new(&envs, 10, sizeof(t_env)) < 0)
		exit (1);
	if (ft_putenv_key(&envs, home, dup1) < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME1", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof", ((t_env *)envs.memory)[0].value);
	if (ft_putenv_key(&envs, home, dup2) < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("HOME1", ((t_env *)envs.memory)[0].key);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof/src", ((t_env *)envs.memory)[0].value);
	free_envs(envs);
	vec_free(&envs);
}

void test_ft_getenv_0(void)
{
	t_vec	envs;

	if (vec_new(&envs, 10, sizeof(t_env)) < 0)
		exit (1);
	if (ft_putenv(&envs, "HOME2=/Users/tspoof5") < 0)
		exit (1);
	if (ft_putenv(&envs, "SHELL=/bin/zsh") < 0)
		exit (1);
	if (ft_putenv(&envs, "LANG=en_US.UTF-8") < 0)
		exit (1);
	TEST_ASSERT_EQUAL_STRING("/Users/tspoof5", ft_getenv(envs, "HOME2"));
	TEST_ASSERT_EQUAL_STRING("/bin/zsh", ft_getenv(envs, "SHELL"));
	TEST_ASSERT_EQUAL_STRING("en_US.UTF-8", ft_getenv(envs, "LANG"));
	free_envs(envs);
	vec_free(&envs);
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
	free_envs(envs);
	vec_free(&envs);
}
void test_ft_strenv_0(void)
{
	char *expected[] = {"SHELL=/bin/zsh", "HOME3=/Users/tspoof9", "PWD=/Users/tspoof/Documents/HIVE/minishell", NULL};
	char **actual;

	actual = ft_strenv(env_envs);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, 4);
	free_2d(actual);
}
void test_ft_unset_0(void)
{
	ft_unset(&env_envs, "HOME3");
	TEST_ASSERT_EQUAL(NULL, ft_getenv(env_envs, "HOME3"));
}

int test_ft_env(char **envp)
{
	set_env_envs();
	env_vars = envp;
	UNITY_BEGIN();
	RUN_TEST(test_ft_env_getkey);
	RUN_TEST(test_ft_env_getvalue);
	RUN_TEST(test_ft_putenv_0);
	RUN_TEST(test_ft_putenv_1);
	RUN_TEST(test_ft_putenv_2);
	// RUN_TEST(test_ft_putenv_key_0);
	// RUN_TEST(test_ft_getenv_0);
	// // RUN_TEST(test_ft_copyenv_0);
	// RUN_TEST(test_ft_strenv_0);
	// RUN_TEST(test_ft_unset_0);
	free_envs(env_envs);
	vec_free(&env_envs);
	return UNITY_END();
}
