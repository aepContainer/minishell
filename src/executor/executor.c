#include "../../inc/minishell.h"

static void close_pipe(int pipe[2])
{
    close(pipe[0]);
    close(pipe[1]);
}

static void	exec_child(int i, t_mshell *mshell, int active_pipe[2], int old_pipe[2])
{
    if (i > 0)
        dup2(old_pipe[0], STDIN_FILENO);
    if (i + 1 < mshell->jobs->len)
        dup2(active_pipe[1], STDOUT_FILENO);
    if (i > 0)
        close_pipe(old_pipe);
    if (i + 1 < mshell->jobs->len)
        close_pipe(active_pipe);
    while (i)
    {
        mshell->jobs->job_list = mshell->jobs->job_list->next_job;
        i--;
    }
    execve(mshell->success_arr[i], mshell->jobs->job_list->args, mshell->envp);
    perror("execve error");
}

static char	executor_line_helper(t_mshell *mshell)
{
	if (i + 1 < mshell->jobs->len)
    {
        if (pipe(active_pipe) == -1)
            return (perror("pipe error"), EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
        return (perror("fork error"), EXIT_FAILURE);
    if (pid == 0)
        exec_child(i, mshell, active_pipe, old_pipe, mshell->envp);
    if (i > 0)
        close_pipe(old_pipe);
    if (i + 1 < mshell->jobs->len)
    {
        old_pipe[0] = pipes[0];
        old_pipe[1] = pipes[1];
    }
	return (EXIT_SUCCESS);
}

char	executor(t_mshell *mshell)
{
    int     active_pipe[2];
    int     old_pipe[2];
    pid_t   pid;
    int     i;

    mshell->success_arr = accessor(mshell);
    i = -1;
    while (++i < mshell->jobs->len)
        if (executor_line_helper(mshell))
			return (EXIT_FAILURE);
    i = -1;
    while (++i < mshell->jobs->len)
        wait(NULL);
    return (EXIT_SUCCESS);
}
