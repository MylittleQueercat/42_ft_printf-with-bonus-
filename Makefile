NAME	= libftprintf.a
LIBFT	= libft/libft.a

CC		= cc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -f
AR		= ar rcs
INCLUDE	= .
INCDIR	= -I$(INCLUDE)

SRC		= ft_printf.c \
		printf_parse.c \
		printf_part1.c \
		printf_part2.c \
		printf_part3.c

OBJS	= $(SRC:.c=.o)

PRINTF_HEAD = ft_printf.h

all: $(NAME)

bonus: all

$(NAME): $(LIBFT) $(OBJS)
		cp $(LIBFT) $(NAME)
		$(AR) $@ $(OBJS)

%.o: %.c $(PRINTF_HEAD)
		$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
