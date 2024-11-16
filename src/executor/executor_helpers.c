#include "../../inc/minishell.h"

char	no_pipe(t_jobs *jobs, t_job *job)
{
	int	fd;

	built_in(job);
	fd = get_fd(jobs, job);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (job->is_builtin == false)
	{
		job->pid = fork();
		if (job->pid == 0)
		{
			set_signal(CHILD);
			runCmd(jobs, job);//
			exit(g_quest_mark);
		}
	}
	else
		return (ctrl_builtins(jobs, job));
	return (EXIT_SUCCESS);
}

char	pipe_handle(t_jobs *jobs, t_job *job)
{
	int	pipe_fd[2];
	int	fd;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(127);
	}
	job->pid = fork();
	if (job->pid == 0)
	{
		set_signal(CHILD);
		close(pipe_fd[0]);
		if (job->next_job)
		{
			dup2(pipe_fd[1], 1);
			close(pipe_fd[1]);
		}
		if (job->redir->in_f || job->redir->out_f || job->redir->app_f)
		{
			fd = get_fd(jobs, job);
			if (fd == -1)
				return (EXIT_FAILURE);
		}
		built_in(job);
		if (job->builtin == false)
			runCmd(jobs, job);
		exit(ctrl_builtins(jobs, job));
	}
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (EXIT_SUCCESS);
}
