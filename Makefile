NAME 		= minishell

S			= src/
O			= obj/
I			= inc/
LIBFT_I		= libft/inc

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -O3
INCLUDES	= -I$I -I$(LIBFT_I)
LIBRARIES	= -L./libft -lft

AR			= ar
ARFLAGS		= rcs

SRC = \
$S/main.c	$S/ft_cmd_trim.c	$S/ft_expand.c	$S/ft_env.c	$S/ft_split_operators.c		\
$S/ft_split_operators_utils.c	$S/ft_str_trim.c	$S/ft_fd_handler.c	$S/here_doc.c	\
$S/ft_expand_utils.c $S/ft_parse_args.c

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
