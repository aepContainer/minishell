NAME = minishell

CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = inc/libft/
LIBFT_FLAGS = -L $(LIBFT_PATH) -lft
LIBFT = $(LIBFT_PATH)libft.h

RL_FLAGS = -lreadline -I/usr/include/readline

SRC_PATH = src/

B_PATH = $(SRC_PATH)builtins/
B_SRC = $(B_PATH)cd.c $(B_PATH)pwd.c

EX_PATH = $(SRC_PATH)executor/
#EX_SRC = $(EX_PATH)executor_helpers1.c $(EX_PATH)executor.c

EXP_PATH = $(SRC_PATH)expander/
EXP_SRC = $(EXP_PATH)expander.c

H_PATH = $(SRC_PATH)helpers/
H_SRC = $(H_PATH)

PARSER_PATH = $(SRC_PATH)parser/
#PARSER_SRC = $(PARSER_PATH)parser_helpers_1.c

RED_PATH = $(SRC_PATH)redir/
RED_SRC = $(RED_PATH)create_file.c

SIG_PATH = $(SRC_PATH)signals/
#SIG_SRC = $(SIG_PATH) 

SRCS = src/main.c $(B_SRC) $(EX_SRC) $(EXP_SRC) $(PARSER_SRC) $(RED_SRC)

all: $(SRCS) $(LIBFT)
	cc $(CFLAGS) $(SRCS) $(LIBFT_FLAGS) $(RL_FLAGS) -o $(NAME)

$(LIBFT):
	make -c $(LIBFT_PATH)

clean:
	make -c $(LIBFT_PATH) clean
	$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
