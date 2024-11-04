#include "../../inc/minishell.h"

bool	save_std_io(int saved_fd[2])
{
	saved_fd[0] = dup(STDIN_FILENO);
	if (saved_fd[0] != -1)
		saved_fd[1] = dup(STDOUT_FILENO);
	else
		saved_fd[1] = -1;
	if (saved_fd[1] == -1)
	{
		perror("minishell");
		if (saved_fd[0] != -1)
			close(saved_fd[0]);
		return (false);
	}
	return (true);
}

bool	redirect_job_io(t_mshell *mshell, int *read_fd, int *write_fd)
{
	bool	ret;

	ret = true;
	if (dup2(*read_fd, STDIN_FILENO) == -1 || \
		dup2(*write_fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		ret = false;
	}
	close_all_pipes(mshell);
	if (*read_fd != -1)
		close(*read_fd);
	if (*write_fd != -1)
		close(*write_fd);
	return (ret);
}

char	redirect_pipe_io(t_job *job)
{
	char	ret;

	ret = handle_redirections(job);
	if (ret == 0 && \
		((job->redir->in_file != -1 && \
		dup2(job->redir->in_file, STDIN_FILENO) == -1) || \
		(job->redir->out_file != -1 && \
		dup2(job->redir->out_file, STDOUT_FILENO) == -1)))
	{
		perror("minishell");
		ret = 1;
	}
	if (job->redir->in_file != -1)
		close(job->redir->in_file);
	if (job->redir->out_file != -1)
		close(job->redir->out_file);
	return (ret);
}

bool	restore_std_io(int saved_fd[2])
{
	int	error;

	error = 0;
	if (saved_fd[0] != -1)
	{
		if (dup2(saved_fd[0], STDIN_FILENO) == -1)
			error = errno;
		close(saved_fd[0]);
	}
	if (saved_fd[1] != -1)
	{
		if (dup2(saved_fd[1], STDOUT_FILENO) == -1)
			error = errno;
		close(saved_fd[1]);
	}
	if (error != 0)
	{
		perror("minishell");
		return (false);
	}
	return (true);
}
