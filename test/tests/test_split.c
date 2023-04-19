#include "unity.h"

void test_tokenizer_0(void)
{
	char	*expected[] = {"echo test1", "|", "echo \"|\""};
	char	*actual[] = tokenizer("echo test1 | echo test2");

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_tokenizer_1(void)
{
	char	*expected[] = {"echo test1", "|" ,"echo test2", ">", "file.txt"};
	char	*actual = tokenizer("echo test1 | echo test2 > file.txt");

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_tokenizer_2(void)
{
	char	*expected[] = {"echo test1", "|" ,"echo test2", ">", "file.txt"};
	char	*actual = tokenizer();

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
