NAME = libftprintf.a

SRCS = ft_printf.c ft_print_perc.c ft_putnum_hex_arg.c \
ft_putnum_sdec_arg.c ft_putnum_udec_arg.c ft_putstr_arg.c \
ft_putnum_addr.c ft_putchar_arg.c ft_putnum_hex_ul_arg.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
