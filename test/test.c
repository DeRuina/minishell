#include "test.h"

void setUp(void) {
}

void tearDown(void) {
}

int main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	// test_ft_utils();
	// test_ft_env(envp);
	// test_ft_cmd_trim();
	// test_ft_expand();
	// test_ft_split_operators();
	// test_ft_str_trim();
	// // test_ft_parse_args();
	// test_ft_get_exec_path();
	test_ft_executor();
	return (0);
}
