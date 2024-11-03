#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "fcntl.h"
# include "unistd.h"
# include "stdio.h"
# include "stdbool.h"
# include "dirent.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "termios.h"
# include "signal.h"
# include "errno.h"

# define PROMPT "shellshock <(^_^)> "

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

struct s_redir
{
	int		in_file;
	int 	out_file;
	char	**files;
	char	**eof;
	char	*heredoc_arg;
};

struct s_job
{
	char		*cmd;// kaldır / yerine args[0] kullan *
	char		**args;
	int			args_len;
	t_redir		*redir;
	t_job		*next_job;
};

struct s_jobs
{
	t_env	*env;
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
	char		quest_mark;
	int			active_pipe[2];
	int			old_pipe[2];
	t_termios	*termios;
};

struct s_env
{
	char	**key;
	char	**value;
	int		len;
};

struct s_quote_state
{
	bool	in_single;
	bool	in_double;
};

struct s_parser_state
{
    t_quote_state	*state;
    int				len;
    int				i;
};

// Parser
char	parser(t_jobs *jobs, char *prompt);
char 	**word_split(char *prompt);

// Expander
void	expander(t_env *env, char **prompt);
char	*expand_env_vars(t_env *env, char *prompt);
// Expander Helpers
void	update_quote_state(t_quote_state *state, char c);
char	*find_value(t_env *env, const char *key_start, int key_len);

// Executor
char	executor(t_mshell *mshell);
char	**accessor(t_mshell *mshell);

// Env
char	env_del_element(t_env **env, char *key, char *value);
char	env_add(t_env **env, char *key, char *value);
char	*env_find_value(t_env *env, char *key);

// Builtins
char	ctrl_builtins(char	*prompt);
char	export(t_env **env, char *key, char *value, char *arg);
char	pwd(void);
char	cd(char *path);

// Redir
void	create_file(char **files, int len);
void	init_pipes(t_mshell *mshell);
bool	create_pipe(t_mshell *mshell);
void	handle_pipes_parent(t_mshell *mshell);
void	handle_pipes_child(t_mshell *mshell);
void	close_active_pipe(t_mshell *mshell);
void	close_all_pipes(t_mshell *mshell);

// Signal
void	signal_handle_general(t_mshell *mshell);
void	signal_handle_exec(t_mshell *mshell);

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
