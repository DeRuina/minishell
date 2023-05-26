/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:06:24 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/26 12:17:33 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "unity.h"
#include "minishell.h"
#include "parser.h"

void test_ft_utils_0(void)
{
	TEST_ASSERT_EQUAL_INT32(1, is_builtin("echo"));
	TEST_ASSERT_EQUAL_INT32(1, is_builtin("cd"));
	TEST_ASSERT_EQUAL_INT32(1, is_builtin("pwd"));
	TEST_ASSERT_EQUAL_INT32(1, is_builtin("export"));
	TEST_ASSERT_EQUAL_INT32(1, is_builtin("unset"));
	TEST_ASSERT_EQUAL_INT32(1, is_builtin("env"));
	TEST_ASSERT_EQUAL_INT32(1, is_builtin("exit"));
}

void test_ft_utils_1(void)
{
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("echoo"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("eecho"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("c"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("cd"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("cdd"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("pwd1"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("expo"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("unse"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("e"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("eexit"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("welcome"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("home"));
}

int test_ft_utils(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_utils_0);
	RUN_TEST(test_ft_utils_1);
	return UNITY_END();
}
