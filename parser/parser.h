#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"

# define NONE 0
# define CMD 1
# define ARG 2
# define PIPE 3
# define HDOC 4
# define PTHSS 5
# define ENVAR 6

typedef struct s_tree	t_tree;
typedef struct s_node	t_node;
typedef union u_cnt		t_cnt;

union u_cnt
{
	char	*cmd;
	char	**args;
	char	*envar;
	char	pipe;
	char	heredoc;
};

struct s_node
{
	char	type;
	t_cnt	content;
	t_node	*next;
};

struct s_tree
{
	char	**job;
	t_node	**elements;
	t_tree	*next;
};

t_node	*new_node(char *input, char type);
void	add_arg(char ***args, char *arg);

char	lexer(char *str);

t_tree	*parser(t_mshell *mshell);

#endif
