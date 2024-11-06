NAME = minishell

CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = inc/libft/
LIBFT_FLAGS = -L $(LIBFT_PATH) -lft
LIBFT = $(LIBFT_PATH)libft.h

PRINTF_PATH = inc/ft_printf/
PRINTF_FLAGS = -L $(PRINTF_PATH) -lftprintf
PRINTF = $(PRINTF_PATH)libftprintf.a

READLINE = $(PWD)/inc/readline/
RL_FLAGS = -lreadline -I $(READLINE)/include/readline -L $(READLINE)/lib -lhistory

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
RED_SRC = $(RED_PATH)create_file.c $(RED_PATH)heredoc.c $(RED_PATH)io_file.c \
$(RED_PATH)io_handler.c $(RED_PATH)pipe.c

SIG_PATH = $(SRC_PATH)signal/
SIG_SRC = $(SIG_PATH)signal_handle.c

SRCS = src/main.c $(B_SRC) $(ENV_SRC) $(EX_SRC) $(EXP_SRC) $(FREE_SRC) $(H_SRC) $(PARSER_SRC) $(RED_SRC) $(SIG_SRC)

all: $(SRCS) $(LIBFT) $(PRINTF) $(READLINE)
	cc $(CFLAGS) $(SRCS) $(LIBFT_FLAGS) $(PRINTF_FLAGS) $(RL_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(PRINTF):
	make -C $(PRINTF_PATH)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=$(READLINE)
	cd readline-8.2 && make install
	@rm -fr readline-8.2 readline-8.2.tar.gz

clean:
	make -C $(LIBFT_PATH) clean
	make -C $(PRINTF_PATH) clean
	$(RM) $(NAME)

fclean: clean
	$(RM) -r inc/readline

re: fclean all

.PHONY: all clean fclean re
