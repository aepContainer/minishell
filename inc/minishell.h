/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem <yunozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:43 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/21 20:51:06 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dirent.h"
# include "errno.h"
# include "fcntl.h"
# include "libft/libft.h"
# include "signal.h"
# include "stdbool.h"
# include "stdio.h"
# include "sys/stat.h"
# include "sys/wait.h"
# include "termcap.h"
# include "termios.h"
# include "unistd.h"
# include <readline/history.h>
# include <readline/readline.h>

# define PROMPT "shellshock <(^_^)> "

# define QUOTES "'\""
# define DQUOTE '\"'
# define SQUOTE '\''

# define MAIN 0
# define CHILD 1
# define HDOC 2

typedef struct s_redir			t_redir;
typedef struct s_job			t_job;
typedef struct s_jobs			t_jobs;
typedef struct s_mshell			t_mshell;
typedef struct s_env			t_env;
typedef struct s_quote_state	t_quote_state;
typedef struct s_parser_state	t_parser_state;
typedef struct termios			t_termios;
typedef struct stat				t_stat;

struct							s_redir
{
	char						last_out;
	char						last_in;
	int							out_file;
	int							app_file;
	int							in_file;
	char						**out_f;
	char						**app_f;
	char						**in_f;
	char						**eof;
	char						**files;
};

struct							s_job
{
	pid_t						pid;
	char						built_in;
	char						**args;
	int							args_len;
	t_redir						*redir;
	t_job						*next_job;
};

struct							s_jobs
{
	t_mshell					*mshell;
	t_env						*env;
	t_job						*job_list;
	int							len;
};

struct							s_mshell
{
	t_jobs						*jobs;
	char						**envp;
	char						*prompt;
	char						exit;
	int							quest_mark;
	int							backup[2];
	t_termios					termios;
};

struct							s_env
{
	char						**key;
	char						**value;
	int							len;
};

struct							s_quote_state
{
	bool						in_single;
	bool						in_double;
};

struct							s_parser_state
{
	t_quote_state				*state;
	int							len;
	int							i;
};

bool							check_unclosed_quotes(t_jobs *jobs,
									const char *input);
bool							check_syntax_errors(t_jobs *jobs,
									char **tokens);
bool							is_special_char(const char *token);

char							parser(t_jobs *jobs, char *prompt);
char							handle_distribute(t_job *job, char *arg,
									char *redir_status);
char							**word_split(char *prompt);

void							expander(t_jobs *jobs, char **prompt);
char							*expand_env_vars(t_jobs *jobs, char *prompt);
char							ctrl_append(t_redir *redir, char *arg);
int								calc_len(t_jobs *jobs, char *prompt,
									t_quote_state state);

void							update_quote_state(t_quote_state *state,
									char c);

char							executor(t_mshell *mshell);
char							pipe_handle(t_jobs *jobs, t_job *job);
char							no_pipe(t_jobs *jobs, t_job *job);
void							get_backup(t_mshell *mshell);
void							run_cmd(t_jobs *jobs, t_job *job);
char							**get_env_for_exec(t_env *env);

int								get_fd(t_jobs *jobs, t_job *job);
int								get_fd_lh(t_jobs *jobs, t_job *job,
									int indexes[5]);
char							redir_error(t_jobs *jobs, t_job *job,
									char *file_i, int fd);
char							heredoc(t_jobs *jobs, t_job *job, char state);

char							env_del_element(t_env **env, char *key,
									char *value);
char							env_add(t_env *env, char *key, char *value);
char							*env_find_value(t_env *env, char *key);
char							get_first_env(t_jobs *jobs, char **env);
char							env_del_index(t_env **env, int index);

void							built_in(t_job *job);
char							ctrl_builtins(t_jobs *jobs, t_job *job);
char							update_env(t_env *env, char *key, char *value);
char							export(t_jobs *jobs, char **args);
char							unset(t_env **env, char **keys);
void							env(t_jobs *jobs);
char							pwd(t_jobs *jobs);
char							cd(t_jobs *jobs, char *path);
void							echo(t_jobs *jobs, t_job *job);
void							exit_d(t_jobs *jobs, char **args);
void							handle_exit_argument(t_jobs *jobs, char **args,
									char *stripped);

void							set_signal(int c);
void							handler_sigint(int sig);

int								str_arr_len(char **arr);
char							**str_arr_realloc(char **arr, char *element);
void							error_msg(t_jobs *jobs, char *file,
									const char *message);
char							*ft_strjoin_const(char *s1, const char *s2);
char							*env_find_value_const(t_env *env,
									const char *key);
char							exit_error(t_jobs *jobs, char *arg,
									const char *msg);

void							free_job_list(t_job *job);
void							free_jobs(t_jobs *jobs);
void							free_str_arr(char **arr);
void							free_redir(t_redir *redir);
void							free_mshell(t_mshell *mshell);
void							free_env(t_env *env);
void							free_str_arr_null(char ***arr);
void							free_nec(t_mshell *mshell);

#endif
