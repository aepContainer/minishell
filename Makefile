NAME = minishell
CFLAGS = -Wall -Werror -Wextra

LFT_PATH = libft/
LFT_FLAGS = -L $(LFT_PATH) -lft

RLINE_FLAG = -lreadline

FLAGS = $(LFT_FLAGS) $(RLINE_FLAG)

PARSER_PATH = parser/
SRCS_PARSER = $(PARSER_PATH)parser.c $(PARSER_PATH)parser_helpers1.c $(PARSER_PATH)parser_helpers2.c

EXE_PATH = executor/
SRCS_EXE = $(EXE_PATH)executor.c $(EXE_PATH)executor_helpers1.c

SRCS = minishell.c builtins_1.c $(SRCS_EXE) $(SRCS_PARSER) \
print_parse_tree.c

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
