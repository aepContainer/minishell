NAME = minishell
CFLAGS = -Wall -Werror -Wextra

LFT_PATH = libft/
LFT_FLAGS = -L $(LFT_PATH) -lft

RLINE_FLAG = -lreadline

FLAGS = $(LFT_FLAGS) $(RLINE_FLAG)

SRCS = minishell.c builtins_1.c

all: $(NAME)

$(NAME): $(LIBFT) $(SRCS)
	cc $(CFLAGS) $(SRCS) $(FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LFT_PATH)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
