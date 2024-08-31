#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"

# define NONE 0
# define CMD 1
# define ARG 2
# define PIPE 3
# define HDOC 4
# define ENVAR 5

typedef struct s_ParseTree t_ParseTree;
typedef struct s_node		t_node;

struct s_node
{
	char	**job;
	char	*cmd;
	char	*arg;
	char	type;
};

struct s_ParseTree
{
	char		pipe;
	t_node		*this_node;
	t_ParseTree	*next;
};

char	lexer(char *str);

#endif
