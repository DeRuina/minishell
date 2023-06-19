T = ./tests/

FLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I../inc -I../libft/inc -I./unity -I./inc
# SANITIZE = -fsanitize=address
TEST = ./unity/unity.c ./test.c
TESTS = \
	$T/test_ft_cmd_trim.c	$T/test_ft_expand.c	$T/test_ft_env.c					\
	$T/test_ft_split_operators.c	$T/test_ft_str_trim.c	$T/test_ft_executor.c	\
	$T/test_ft_get_exec_path.c	$T/test_ft_utils.c
MINISHELL =
PS := $(filter-out %main.c, $(MINISHELL))

all: clean run_test

run_test:
	cc $(FLAGS) $(INCLUDES) $(SANITIZE) $(TEST) $(TESTS) $(PS:%=../%) -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -L../libft -lft -o run_tests
	./run_tests

clean:
	rm -fr run_*
