#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"

# define NONE 0
# define CMD 1
# define BLTNS 2
# define ARG 3
# define ENVAR 4
# define PIPE 5
# define HDOC 6

typedef struct s_tree	t_tree;
typedef struct s_job	t_job;
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

struct s_job
{
	char	**job;
	t_node	**elements;
};

struct s_tree
{
	t_job	*job;
	int		noj;//	number of jobs
	t_tree	*next;
};

#endif
