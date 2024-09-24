#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"

# define NONE 0
# define CMD 1
# define ARG 2
# define PIPE 3
# define HDOC 4
# define ENVAR 6

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
	t_job	**job;
	int		noj;//	number of jobs
	t_tree	*next;
};

char	add_node_to_tree(t_mshell *mshell, t_tree *tree, t_node *node);
char	inject_jobs(t_tree *tree, t_node *node);
void	add_arg(char ***args, char *arg);

char	lexer(char *str);

t_tree	*parser(t_mshell *mshell);

#endif
