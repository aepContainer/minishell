
#include "../../inc/minishell.h"

static char	setup_pipes(int pipes[][2], int noj)
{
	int	i;

	i = -1;
	while (++i + 1 < noj)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe error");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static void	close_all_pipes(int pipes[][2], int noj)
{
	int	i;

	i = -1;
	while (++i + 1 < noj)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

static void	exec_child(int i, t_mshell *mshell, int pipes[][2], char **envp)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i + 1 < tree->noj)
		dup2(pipes[i][1], STDOUT_FILENO);
	close_all_pipes(pipes, tree->noj);
	while (i)
	{
		mshell->jobs->job_list = mshell->jobs->job_list->next_job;
		i--;
	}
	execve(mshell->success_arr[i], mshell->jobs->job_list->args, envp);
	perror("execve error");
}

char	executor(t_mshell *mshell)
{
	int		pipes[tree->noj - 1][2];
	pid_t	pid;
	int		i;

	mshell->success_arr = accessor(mshell);
	if (setup_pipes(pipes, mshell->jobs->len))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < mshell->jobs->len)
	{
		pid = fork();
		if (pid == -1)
			return(perror("fork error"), EXIT_FAILURE);
		if (pid == 0)
			exec_child(i, mshell, pipes, mshell->env);
	}
	close_all_pipes(pipes, mshell->jobs->len);
	i = -1;
	while (++i < mshell->jobs->len)
		wait(NULL);
	return (EXIT_SUCCESS);
}
