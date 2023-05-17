NAME 		= minishell

S			= src/
P			= $S/parser
O			= obj/
I			= inc/
LIBFT_I		= libft/inc

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -O3
INCLUDES	= -I$I -I$(LIBFT_I) -I$P
LIBRARIES	= -L./libft -lft

AR			= ar
ARFLAGS		= rcs

SRC = \
$S/main.c	$P/ft_cmd_trim.c	$P/ft_expand.c	$P/ft_env.c	$P/ft_split_operators.c		\
$P/ft_split_operators_utils.c	$P/ft_str_trim.c	$P/ft_fd_handler.c	$P/here_doc.c	\
$P/ft_expand_utils.c	$P/ft_parse_args.c	$P/ft_get_exec_path.c

OBJ			= $(SRC:$S%=$O%.o)

RM			= /bin/rm -f
RMDIR		= /bin/rm -rf

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= $(CFLAGS)

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@mkdir $@

$(OBJ): | $O

$(OBJ): $O%.o: $S%
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBRARIES) -o $(NAME) -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

cleanobjdir: $O
	$(RMDIR) $O

clean: cleanobjdir

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re:
	@make fclean
	@make all

run_test: $(LIBFT)
	make MINISHELL="$(SRC)" -C ./test

debug: CFLAGS := $(filter-out -O3,$(CFLAGS))
debug: CFLAGS += -g
debug: $(NAME)
