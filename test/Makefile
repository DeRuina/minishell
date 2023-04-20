T = ./tests/

FLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I../inc -I../libft/inc -I./unity -I.
# SANITIZE = -fsanitize=address
TEST = ./unity/unity.c ./test.c
TESTS = \
$T/test_tokenizer.c
MINISHELL =
PS := $(filter-out %main.c, $(MINISHELL))

all: clean run_test

run_test:
	gcc $(FLAGS) $(INCLUDES) $(SANITIZE) $(TEST) $(TESTS) $(PS:%=../%) -L../libft -lft -o run_tests
	./run_tests

clean:
	rm -fr run_*
