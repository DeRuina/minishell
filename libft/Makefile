NAME 		= libft.a

S			= src/
O			= obj/
I			= inc/

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -c -I$I
FLAGS		=

AR			= ar
ARFLAGS		= rcs

SRC = \
$S/ft_bzero.c		$S/ft_isalnum.c		$S/ft_isalpha.c			$S/ft_isascii.c			\
$S/ft_isdigit.c		$S/ft_isprint.c		$S/ft_memcpy.c			$S/ft_memmove.c			\
$S/ft_memset.c		$S/ft_strlcpy.c		$S/ft_strlen.c			$S/ft_toupper.c			\
$S/ft_tolower.c		$S/ft_strchr.c		$S/ft_strrchr.c			$S/ft_strncmp.c			\
$S/ft_memchr.c		$S/ft_strlcat.c		$S/ft_memcmp.c			$S/ft_strnstr.c			\
$S/ft_atoi.c		$S/ft_calloc.c		$S/ft_strdup.c			$S/ft_substr.c			\
$S/ft_strjoin.c		$S/ft_strtrim.c		$S/ft_split.c			$S/ft_itoa.c			\
$S/ft_strmapi.c		$S/ft_striteri.c	$S/ft_putchar_fd.c		$S/ft_putstr_fd.c		\
$S/ft_putendl_fd.c	$S/ft_putnbr_fd.c	$S/ft_lstnew.c			$S/ft_lstadd_front.c	\
$S/ft_lstsize.c		$S/ft_lstlast.c		$S/ft_lstadd_back.c		$S/ft_lstdelone.c		\
$S/ft_lstclear.c	$S/ft_lstiter.c		$S/ft_lstmap.c			$S/get_next_line.c		\
$S/ft_ulongtohex.c	$S/ft_ltoa.c		$S/vec_append.c			$S/vec_free.c			\
$S/vec_from.c		$S/vec_new.c		$S/vec_push.c			$S/vec_resize.c			\
$S/vec_copy.c
OBJ			= $(SRC:$S%=$O%.o)

RM			= /bin/rm -f
RMDIR		= /bin/rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@mkdir $@

$(OBJ): | $O

$(OBJ): $O%.o: $S%
	$(CC) $(CFLAGS) $(FLAGS) $< -o $@

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $?

cleanobjdir: $O
	$(RMDIR) $O

clean: cleanobjdir

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all
