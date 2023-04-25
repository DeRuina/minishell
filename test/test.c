#include "test.h"

void setUp(void) {
}

void tearDown(void) {
}

int main(void)
{
	test_ft_env();
	test_ft_cmd_trim();
	test_ft_expand();
	// test_ft_split_operators();
	// test_ft_str_trim();

	return (0);
}
