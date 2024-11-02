NAME = minishell

CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = inc/libft/
LIBFT_FLAGS = -L $(LIBFT_PATH) -lft
LIBFT = $(LIBFT_PATH)libft.h

RL_FLAGS = -lreadline -I/usr/include/readline

SRC_PATH = src/

B_PATH = $(SRC_PATH)builtins/
B_SRC = $(B_PATH)ctrl_builtins.c $(B_PATH)cd.c $(B_PATH)pwd.c $(B_PATH)export.c $(B_PATH)unset.c

ENV_PATH = $(SRC_PATH)env/
ENV_SRC = $(ENV_PATH)env_handle.c

EX_PATH = $(SRC_PATH)executor/
EX_SRC = $(EX_PATH)executor_helpers1.c $(EX_PATH)executor.c

EXP_PATH = $(SRC_PATH)expander/
EXP_SRC = $(EXP_PATH)expander.c $(EXP_PATH)expander_helpers_1.c $(EXP_PATH)expander_helpers_2.c

FREE_PATH = $(SRC_PATH)free/
FREE_SRC = $(FREE_PATH)free_helpers_1.c $(FREE_PATH)free_helpers_2.c

H_PATH = $(SRC_PATH)helpers/
H_SRC = $(H_PATH)str_arr.c

PARSER_PATH = $(SRC_PATH)parser/
PARSER_SRC = $(PARSER_PATH)parser.c $(PARSER_PATH)get_word.c

RED_PATH = $(SRC_PATH)redir/
RED_SRC = $(RED_PATH)create_file.c

SIG_PATH = $(SRC_PATH)signals/
SIG_SRC = $(SIG_PATH)signal_handle.c

SRCS = src/main.c $(B_SRC) $(ENV_SRC) $(EX_SRC) $(EXP_SRC) $(FREE_SRC) $(H_SRC) $(PARSER_SRC) $(RED_SRC) $(SIG_SRC)

all: $(SRCS) $(LIBFT) $(READLINE)
	cc $(CFLAGS) $(SRCS) $(LIBFT_FLAGS) $(RL_FLAGS) -o $(NAME)

$(LIBFT):
	make -c $(LIBFT_PATH)

$(READLINE):
	curl -O https://gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=../inc/readline
#cd readline-8.2 && make install
	make install
	@rm -fr readline-8.2 readline-8.2.tar.gz

clean:
	make -c $(LIBFT_PATH) clean
	$(RM) $(NAME)

fclean: clean
	$(RM) -r inc/readline

re: fclean all

.PHONY: all clean fclean re
