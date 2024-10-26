#ifndef PARSER_H
#define PARSER_H

# include "libft/libft.h"
# include "fcntl.h"
# include "unistd.h"
# include "stdio.h"
# include "stdbool.h"

# define DQUOTE '\"'
# define SQUOTE '\''

typedef struct s_parse_tree		t_parse_tree;
typedef struct s_redir			t_redir;
typedef struct s_hdoc			t_hdoc;
typedef struct s_job			t_job;
typedef struct s_jobs			t_jobs;
typedef struct s_mshell			t_mshell;
typedef struct s_env			t_env;
typedef struct s_quote_state	t_quote_state;
typedef struct s_parser_state	t_parser_state;
typedef struct termios			t_termios;

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
	char	*args;
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
};

struct s_mshell
{
	t_jobs		*jobs;
	char		*envp;
	char		*prompt;
	char		*path_env;
	char		**ctrl_paths;
	char		**cmds;
	char		**success_arr;
	int			active_pipe[2];
	int			old_pipe[2];
	t_termios	*termios;
};

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

struct s_quote_state
{
	bool	in_single;
	bool	in_double;
};

struct s_parser_state
{
    t_quote_state	*state;
    int				pos;
    int				len;
};

// Parser
char	parser(t_jobs *jobs, char *prompt);
char 	**word_split(char *prompt);

// Helpers
int		str_arr_len(char **arr);
char	**str_arr_realloc(char **arr, char *element);

// Free
void 	free_job_list(t_job *job);
void 	free_jobs(t_jobs *jobs);
void 	free_str_arr(char **arr);
void 	free_redir(t_redir *redir);
void	free_mshell(t_mshell *mshell);
void	free_env_node(t_env *env);

// Redir
void	create_file(char **files, int len);

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

#endif
