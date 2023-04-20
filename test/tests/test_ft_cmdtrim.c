#include "unity.h"
#include "minishell.h"


// Probably checks stuff it's not supposed to
void test_fd_cmdtrim_1337(void)
{
	char	*expected[] = {"<Makefile", "cat|", "echo", "$PWD 'hola'", "~/src", "|", "'tr'", "-d", "/", ">outfile"};
	char	*actual[10] = tokenizer("<Makefile cat| echo \"$PWD 'hola'\" ~/src | 'tr' -d / >outfile");

	TEST_ASSERT_EQUAL_MEMORY(expected, actual, sizeof(char *) * 10);
}

int test_fd_cmdtrim(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_fd_cmdtrim_1337);
	return UNITY_END();
}
