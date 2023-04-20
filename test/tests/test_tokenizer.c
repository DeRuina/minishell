#include "unity.h"
#include "minishell.h"

// void test_tokenizer_0(void)
// {
// 	char	*expected[] = {"echo test1", "|", "echo \"|\""};
// 	char	*actual[] = tokenizer("echo test1 | echo test2");

// 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// }

// void test_tokenizer_1(void)
// {
// 	char	*expected[] = {"echo test1", "|" ,"echo test2", ">", "file.txt"};
// 	char	*actual = tokenizer("echo test1 | echo test2 > file.txt");

// 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// }

// void test_tokenizer_2(void)
// {
// 	char	*expected[] = {"echo test1", "|" ,"echo test2", ">", "file.txt"};
// 	char	*actual = tokenizer();

// 	TEST_ASSERT_EQUAL_STRING(expected, actual);
// }

void test_tokenizer_3(void)
{
	char	*expected = "this";
	char 	*test = ft_strdup("      this     ");
	char	*actual = tokenizer(&test);

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_tokenizer_4(void)
{
	char	*expected = "this";
	char 	*test = ft_strdup("this");
	char	*actual = tokenizer(&test);

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_tokenizer_5(void)
{
	char	*expected = NULL;
	char 	*test = ft_strdup("         ");
	char	*actual = tokenizer(&test);

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_tokenizer_6(void)
{
	char	*expected = NULL;
	char 	*test = NULL;
	char	*actual = tokenizer(&test);

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_tokenizer_7(void)
{
	char	*expected = "\" ' thisi ' \"";
	char 	*test = ft_strdup("\" ' thisi ' \"");
	char	*actual = tokenizer(&test);

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

void test_tokenizer_8(void)
{
	char	*expected = "\' ' thisi ' \'";
	char 	*test = ft_strdup("\' ' thisi ' \'");
	char	*actual = tokenizer(&test);

	TEST_ASSERT_EQUAL_STRING(expected, actual);
}

int test_tokenizer(void)
{
	UNITY_BEGIN();
	// RUN_TEST(test_tokenizer_0);
	// RUN_TEST(test_tokenizer_1);
	// RUN_TEST(test_tokenizer_2);
	RUN_TEST(test_tokenizer_3);
	RUN_TEST(test_tokenizer_4);
	RUN_TEST(test_tokenizer_5);
	RUN_TEST(test_tokenizer_6);
	RUN_TEST(test_tokenizer_7);
	RUN_TEST(test_tokenizer_8);
	return UNITY_END();
}
