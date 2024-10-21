
#include "../../inc/minishell.h"

static void	setup_pipes(int pipes[][2], int noj)
{
	int	i;

	i = -1;
	while (++i + 1 < noj)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
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

static void	exec_child(int i, t_tree *tree, int pipes[][2], char **envp)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i + 1 < tree->noj)
		dup2(pipes[i][1], STDOUT_FILENO);
	close_all_pipes(pipes, tree->noj);
	execve(tree->success_arr[i], tree->jobs[i]->job_exec, envp);
	perror("execve");
}

char	executor(t_tree *tree)
{
	int		pipes[tree->noj - 1][2];
	pid_t	pid;
	int		i;

	tree->success_arr = accessor(tree);
	setup_pipes(pipes, tree->noj);
	i = -1;
	while (++i < tree->noj)
	{
		pid = fork();
		if (pid == -1)
			return(perror("fork"), 1);
		if (pid == 0)
			exec_child(i, tree, pipes, tree->env);
	}
	close_all_pipes(pipes, tree->noj);
	i = -1;
	while (++i < tree->noj)
		wait(NULL);
	return (0);
}
