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

typedef struct s_parse_tree t_parse_tree;
typedef struct s_node		t_node;

struct s_node
{
	char	**job;// job nasıl elde edilir?
	char	*cmd;
	char	*arg;
	char	type;
};

struct s_parse_tree
{
	t_node			*this_node;
	t_node			**child_node;
	t_parse_tree	*next;
};

char	lexer(char *str);

#endif
