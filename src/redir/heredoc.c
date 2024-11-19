#include "../../inc/minishell.h"

static char	calc_state(char *arg, char *test)
{
	int	len;
	int	len_test;

	len = ft_strlen(arg);
	len_test = ft_strlen(test);
	return (!ft_strncmp(arg, test, len) && len == len_test);
}

static void	handle_arg(t_job *job, int pipe_fd[2], char state)
{
	char	*arg;
	char	c_state;
	int		i;

	i = 0;
	while (job->redir->eof[i])
	{
		arg = readline(">");
		if (!arg)
		{
			g_quest_mark = 130;
			exit(g_quest_mark);
		}
		c_state = calc_state(arg, job->redir->eof[i]);
		if (!c_state && arg && !job->redir->eof[i + 1] && state)
			ft_putendl_fd(arg, pipe_fd[1]);
		if (c_state)
			i++;
		free(arg);
	}
}

static void	heredoc_child(t_jobs *jobs, t_job *job, int pipe_fd[2], char state)
{
	if (state)
		set_signal(HDOC);
	dup2(jobs->mshell->backup[0], 0);
    handle_arg(job, pipe_fd, state);
    exit(0);
}

char	heredoc(t_jobs *jobs, t_job *job, char state)
{
	int		temp_status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (EXIT_FAILURE);
	job->pid = fork();
    if (job->pid == 0)
		heredoc_child(jobs, job, pipe_fd, state);
    waitpid(job->pid, &temp_status, 0);
	if (state)
	{
		if (WIFEXITED(temp_status))
			g_quest_mark = WEXITSTATUS(temp_status);
	}
	if (g_quest_mark == 130)
		return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
