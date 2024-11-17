#include "../../inc/minishell.h"

static void	wait_child(t_mshell *mshell)
{
	t_job	*temp_job;
	int		temp_status;
	int		i;

	temp_job = mshell->jobs->job_list;
	if (mshell->jobs->len == 1 && temp_job->built_in == true)
		return ;
	while (temp_job)
	{
		signal(SIGINT, &handler_sigint);
		i = waitpid(temp_job->pid, &temp_status, 0);
		if (i < 0)
			continue ;
		is_builtin(temp_job);
		if (mshell->jobs->len == 1 && temp_job->built_in == true)
			break ;
		if (WIFEXITED(temp_status))
			g_quest_mark = WEXITSTATUS(temp_status);
		else if (WIFSIGNALED(temp_status))
			g_quest_mark = 128 + WTERMSIG(temp_status);
		temp_job = temp_job->next_job;
	}
}

static char	executor_while(t_mshell *mshell)
{
	t_job	*temp;

	temp = mshell->jobs->job_list;
	while (temp)
	{
		if (mshell->jobs->len == 1)
		{
			if (temp->redir->eof && heredoc(mshell->jobs, temp, 1))
				return (EXIT_FAILURE);
			if (no_pipe(mshell->jobs, temp))
				return (EXIT_SUCCESS);
		}
		else
		{
			if (temp->redir->eof && heredoc(mshell->jobs, temp, 0))
				return (EXIT_FAILURE);
			if (g_quest_mark == 130)
				return (EXIT_FAILURE);
			if (pipe_handle(mshell->jobs, temp))
				return (EXIT_SUCCESS);
			g_quest_mark = 0;
		}
		temp = temp->next_job;
	}
	return (EXIT_SUCCESS);
}

char	executor(t_mshell *mshell)
{
	mshell->backup[0] = dup(STDIN_FILENO);
	mshell->backup[1] = dup(STDOUT_FILENO);
	if (!executor_while(mshell))
		return (EXIT_SUCCESS);
	else
	{
		dup2(mshell->backup[0], 0);
		close(mshell->backup[0]);
		dup2(mshell->backup[1], 1);
		close(mshell->backup[1]);
		wait_child(mshell);
	}
	return (EXIT_SUCCESS);
}
