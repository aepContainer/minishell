NAME = mshell
CFLAGS = -Wall -Werror -Wextra

LFT_PATH = ../libft/
LFT_FLAGS = -L $(LFT_PATH) -lft

RLINE_FLAG = -lreadline

FLAGS = $(LFT_FLAGS) $(RLINE_FLAG)

SRCS = mshell.c builtins.c

all: $(NAME)

$(NAME): $(SRCS)
	cc $(CFLAGS) $(SRCS) $(FLAGS) -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
