#include "../../inc/minishell.h"

static void close_pipe(int pipe[2])
{
    close(pipe[0]);
    close(pipe[1]);
}

static void	exec_child(int i, t_mshell *mshell, int active_pipe[2], int old_pipe[2])
{
	t_job	*temp;
	int		index;

    if (i > 0)
        dup2(old_pipe[0], STDIN_FILENO);
    if (i + 1 < mshell->jobs->len)
        dup2(active_pipe[1], STDOUT_FILENO);
    if (i > 0)
        close_pipe(old_pipe);
    if (i + 1 < mshell->jobs->len)
        close_pipe(active_pipe);
	temp = mshell->jobs->job_list;
	index = i;
    while (i)
    {
        temp = temp->next_job;
        i--;
    }
	if (ctrl_builtins(temp->args[0]) == -1)
	    execve(mshell->success_arr[index], temp->args, mshell->envp);
    perror("execve error");
}

static char	executor_line_helper(t_mshell *mshell, int i)
{
	pid_t   pid;

	if (i + 1 < mshell->jobs->len)
    {
        if (pipe(mshell->active_pipe) == -1)
            return (perror("pipe error"), EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
        return (perror("fork error"), EXIT_FAILURE);
    if (pid == 0)
        exec_child(i, mshell, mshell->active_pipe, mshell->old_pipe);
    if (i > 0)
        close_pipe(mshell->old_pipe);
    if (i + 1 < mshell->jobs->len)
    {
        mshell->old_pipe[0] = mshell->active_pipe[0];
        mshell->old_pipe[1] = mshell->active_pipe[1];
    }
	return (EXIT_SUCCESS);
}

char	executor(t_mshell *mshell)
{
    int     i;

    mshell->success_arr = accessor(mshell);
    signal_handle_exec(mshell);
    i = -1;
    while (++i < mshell->jobs->len)
        if (executor_line_helper(mshell, i))
			return (EXIT_FAILURE);
    i = -1;
    while (++i < mshell->jobs->len)
        wait(NULL);
    return (EXIT_SUCCESS);
}
