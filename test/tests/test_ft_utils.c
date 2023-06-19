/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:06:24 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/19 14:04:10 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "unity.h"
#include "minishell.h"
#include "utils.h"

void test_ft_utils_0(void)
{
	TEST_ASSERT_EQUAL_INT32_MESSAGE(1, is_builtin("echo"), "#1");
	TEST_ASSERT_EQUAL_INT32_MESSAGE(2, is_builtin("cd"), "#2");
	TEST_ASSERT_EQUAL_INT32_MESSAGE(3, is_builtin("pwd"), "#3");
	TEST_ASSERT_EQUAL_INT32_MESSAGE(4, is_builtin("export"), "#4");
	TEST_ASSERT_EQUAL_INT32_MESSAGE(5, is_builtin("unset"), "#5");
	TEST_ASSERT_EQUAL_INT32_MESSAGE(6, is_builtin("env"), "#6");
	TEST_ASSERT_EQUAL_INT32_MESSAGE(7, is_builtin("exit"), "#7");
}

void test_ft_utils_1(void)
{
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("echoo"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("eecho"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("c"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("ccd"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("cdd"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("pwd1"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("expo"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("unse"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("e"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("eexit"));
	TEST_ASSERT_EQUAL_INT32(0, is_builtin("welcome"));
}

int test_ft_utils(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_utils_0);
	RUN_TEST(test_ft_utils_1);
	return UNITY_END();
}
