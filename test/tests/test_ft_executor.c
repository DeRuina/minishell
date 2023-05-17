/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:09:15 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/17 14:42:08 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"

void test_ft_executor_0(void)
{
	char	*array[] = {"ls", "|", "wc", NULL};
	t_node *node = ft_parse_args(array);
	ft_executor(node);

	TEST_ASSERT_TRUE(1 == 1);
	// TEST_ASSERT_EQUAL_STRING("/Users/tspoof", ft_getenv(envs, "HOME"));
	// TEST_ASSERT_EQUAL_STRING("/bin/zsh", ft_getenv(envs, "SHELL"));
	// TEST_ASSERT_EQUAL_STRING("en_US.UTF-8", ft_getenv(envs, "LANG"));
}


int test_ft_executor(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_executor_0);
	return UNITY_END();
}
