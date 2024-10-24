#ifndef PARSER_H
#define PARSER_H

# include "libft/libft.h"
# include "fcntl.h"
# include "unistd.h"
# include "stdio.h"

# define DQUOTE '\"'
# define SQUOTE '\''

typedef struct s_parse_tree	t_parse_tree;
typedef struct s_redir		t_redir;
typedef struct s_hdoc		t_hdoc;
typedef struct s_job		t_job;
typedef struct s_jobs		t_jobs;
typedef struct s_env		t_env;

typedef enum	e_type
{
	NONE,
	PIPE,
	EXEC
}	t_type;

struct s_redir
{
	int		in_file;
	int 	out_file;
	char	**files;
	char	*eof;
	char	*args;//inputs
};

struct s_job
{
	char		*cmd;
	char		**args;
	t_redir		*redir;
	t_job		*next_job;
};

struct s_jobs
{
	t_type	type;
	t_job	*job_list;
	int		len;
	int		pipe[2];
};

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

/*
PIPELIST
	- t_job
		- cmd
		- args
		- redirs
	- t_job
		- cmd
		- args
		- redirs
*/

char	parser(t_jobs *jobs, char *prompt);

// Free
void 	free_job_list(t_job *job);
void 	free_jobs(t_jobs *jobs);
void 	free_str_arr(char **arr);
void 	free_redir(t_redir *redir);

// Helpers
char	**str_arr_realloc(char **arr, char *element);

#endif
