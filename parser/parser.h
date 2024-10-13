#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "stdio.h"

# define DQUOTE '\"'
# define SQUOTE '\''

typedef struct s_tree	t_tree;
typedef struct s_jobs	t_jobs;
typedef struct s_node	t_node;
typedef struct s_redir	t_redir;
typedef struct s_cont	t_cont;
typedef struct s_hdoc	t_hdoc;

struct s_cont
{
	t_redir	*redir;
	t_hdoc	*hdoc;
};

struct s_redir // < >
{
	char	**in_filename;
	char 	**out_filename;
};

struct s_hdoc
{
	char	*eof;
	char	**args;
};

struct s_node
{
	char	**args;
	t_cont	*content;
	t_node	*next;
};

struct s_jobs
{
	char	**job_exec;
	char	*job;
	char	*cmd;
	t_node	*elements;
};

struct s_tree
{
	char	**success_arr;
	char 	**env;
	char	**paths;
	char 	**cmds;
	int		c_len;
	int		p_len;
	t_jobs	**jobs;
	int		noj;//	number of jobs
};

// Helper

int		str_arr_len(char **strarr);
char	initialize_elements(t_tree *tree);
char	inject_char_to_str(char **str_p, char c);
char	inject_str_to_arr(char ***str_arr_p, char *element);
void	free_jobs(t_jobs **jobs);
void	free_nodes(t_node *nodes);
void	free_content(t_cont *content);
void	free_str_arr(char **str_arr);

char	**accessor(t_tree *tree);
char    **joins(char **env_paths, int paths_len, char **cmds, int cmds_len);

// Main
char	parser(t_tree *tree, char *prompt);

#endif
