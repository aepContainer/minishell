#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "fcntl.h"
# include "unistd.h"
# include "stdbool.h"
# include "signal.h"
# include "errno.h"
# include "dirent.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "sys/wait.h"
# include "sys/stat.h"
# include "termios.h"
# include "termcap.h"

# define PROMPT "shellshock <(^_^)> "

# define QUOTES "'\""
# define DQUOTE '\"'
# define SQUOTE '\''

# define MAIN 0
# define CHILD 1
# define HDOC 2

int	g_quest_mark;

typedef struct s_redir			t_redir;
typedef struct s_job			t_job;
typedef struct s_jobs			t_jobs;
typedef struct s_mshell			t_mshell;
typedef struct s_env			t_env;
typedef struct s_quote_state	t_quote_state;
typedef struct s_parser_state	t_parser_state;
typedef struct termios			t_termios;
typedef struct stat				t_stat;

struct s_redir
{
	char	last_out;
	char	last_in;
	int 	out_file;
	int		app_file;
	int		in_file;
	char	**out_f;
	char	**app_f;
	char	**in_f;
	char	**eof;
	char	**files;
};

struct s_job
{
	pid_t		pid;
	char		built_in;
	char		**args;
	int			args_len;
	t_redir		*redir;
	t_job		*next_job;
};

struct s_jobs
{
	t_mshell	*mshell;
	t_env		*env;
	t_job		*job_list;
	int			len;
};

struct s_mshell
{
	t_jobs		*jobs;
	char		**envp;
	char		*prompt;
	char		**ctrl_paths;
	char		**success_arr;
	int			backup[2];
	t_termios	termios;
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

bool	check_unclosed_quotes(const char *input);
bool	check_syntax_errors(char **tokens);

char	parser(t_jobs *jobs, char *prompt);
char    handle_distribute(t_job *job, char *arg, char *redir_status);
char 	**word_split(char *prompt);

char	expander_new(t_jobs *jobs, char **splitted);
void	expander(t_jobs *jobs, char **prompt);
char	*expand_env_vars(t_jobs *jobs, char *prompt);

void	update_quote_state(t_quote_state *state, char c);
char	*find_value(t_env *env, char *key_start, int key_len);

char	executor(t_mshell *mshell);
char	pipe_handle(t_jobs *jobs, t_job *job);
char	no_pipe(t_jobs *jobs, t_job *job);
void	run_cmd(t_jobs *jobs, t_job *job);

int		get_fd(t_jobs *jobs, t_job *job);
char	file_control(t_jobs *jobs, t_job *job, char *file, int fd);
char	heredoc(t_jobs *jobs, t_job *job, char state);

char	env_del_element(t_env **env, char *key, char *value);
char	env_add(t_env *env, char *key, char *value);
char	*env_find_value(t_env *env, char *key);

void	built_in(t_job *job);
char	ctrl_builtins(t_jobs *jobs, t_job *job);
char	update_env(t_env *env, char *key, char *value);
char	export(t_env *env, char **args);
char	unset(t_env **env, char **keys);
void	env(t_env *env);
char	pwd(void);
char	cd(char *path);
void	echo(t_job *job);
void	exit_d(char **args);
void	handle_exit_argument(char **args, char *stripped);

void	set_signal(int c);
void	handler_sigint(int sig);

int		str_arr_len(char **arr);
char	**str_arr_realloc(char **arr, char *element);
void	error_msg(char *file, const char *message);
char	*ft_strjoin_const(char *s1, const char *s2);
char	*env_find_value_const(t_env *env, const char *key);
char	exit_error(char *arg, const char *msg);

void 	free_job_list(t_job *job);
void 	free_jobs(t_jobs *jobs);
void 	free_str_arr(char **arr);
void 	free_redir(t_redir *redir);
void	free_mshell(t_mshell *mshell);
void	free_env(t_env *env);
void	free_str_arr_null(char ***arr);
void 	free_nec(t_mshell *mshell);

#endif
