#include "unity.h"

void test_tokenizer_0(void)
{
	char	*expected = "this";
	char 	*test = "      this     ";
	char	*actual = tokenizer(&test);

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_tokenizer_1(void)
{
	char	*expected = "this";
	char 	*test = "this  is a   ";
	char	*actual = tokenizer(&test);

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_tokenizer_2(void)
{
	char	*expected = NULL;
	char 	*test = "         ";
	char	*actual = tokenizer(&test);

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

int test0(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_tokenizer_0);
	RUN_TEST(test_tokenizer_1);
	RUN_TEST(test_tokenizer_2);
	return UNITY_END();
}
