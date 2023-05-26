/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:09:15 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/26 10:23:56 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"

t_vec	envs;

void	set_envs(void)
{
	if (vec_new(&envs, 10, sizeof(t_env)) < 0)
		exit (1);
	if(ft_putenv(&envs, "SHELL=/bin/zsh") < 0)
		exit (1);
	if(ft_putenv(&envs, "HOME=/Users/tspoof") < 0)
		exit (1);
	if(ft_putenv(&envs, "PWD=/Users/tspoof/Documents/HIVE/minishell") < 0)
		exit (1);
	if(ft_putenv(&envs, "PATH=/Users/tspoof/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/Users/tspoof/.brew/bin") < 0)
		exit (1);
}

t_node	get_node(void)
{
	t_node node;
	char *full_cmd[] = {"/bin/ls", NULL};

	node.full_cmd = full_cmd;
	// node.path_name = "/bin/ls";
	node.infile = STDIN_FILENO;
	node.outfile = STDOUT_FILENO;
	node.next = NULL;

	return (node);
}

void test_ft_executor_0(void)
{
	// char	*array[] = {"ls", "|", "wc", NULL};
	t_node node = get_node();
	ft_executor(&node, envs);

	TEST_ASSERT_TRUE(1 == 1);
}
void test_ft_executor_1337(void)
{
	// char *str = "ls | wc";
	char *str = "ls";
	t_node *node = ft_parse_args(str, envs);
	ft_executor(node, envs);

	TEST_ASSERT_TRUE(1 == 1);
	// TEST_ASSERT_EQUAL_STRING("/Users/tspoof", ft_getenv(envs, "HOME"));
	// TEST_ASSERT_EQUAL_STRING("/bin/zsh", ft_getenv(envs, "SHELL"));
	// TEST_ASSERT_EQUAL_STRING("en_US.UTF-8", ft_getenv(envs, "LANG"));
}


int test_ft_executor(void)
{
	set_envs();
	UNITY_BEGIN();
	// RUN_TEST(test_ft_executor_0);
	RUN_TEST(test_ft_executor_1337);

	return UNITY_END();
}
