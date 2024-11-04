#include "../../inc/minishell.h"

static bool	handle_input_file(t_redir *redir, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (false);
	}
	if (redir->in_file != -1)
		close(redir->in_file);
	redir->in_file = fd;
	return (true);
}

static bool	handle_append_file(t_redir *redir, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (false);
	}
	if (redir->out_file != -1)
		close(redir->out_file);
	redir->out_file = fd;
	return (true);
}

static bool	handle_output_file(t_redir *redir, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (false);
	}
	if (redir->out_file != -1)
		close(redir->out_file);
	redir->out_file = fd;
	return (true);
}

static char	apply_redirections(t_redir *redir)
{
	if (redir->in_file != -1)
	{
		if (dup2(redir->in_file, STDIN_FILENO) == -1)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	if (redir->out_file != -1)
	{
		if (dup2(redir->out_file, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static char	handle_redir_type(t_redir *redir, int i)
{
	if (redir->heredoc_arg[i] == '<')
	{
		if (!handle_input_file(redir, redir->files[i]))
			return (1);
	}
	else if (redir->heredoc_arg[i] == '>' && redir->heredoc_arg[i + 1] != '>')
	{
		if (!handle_output_file(redir, redir->files[i]))
			return (1);
	}
	else if (redir->heredoc_arg[i] == '>' && redir->heredoc_arg[i + 1] == '>')
	{
		if (!handle_append_file(redir, redir->files[i]))
			return (1);
	}
	return (0);
}

void	handle_redirections(t_job *job)
{
	t_redir	*redir;
	int		i;

	if (!job || !job->redir || !job->redir->files)
		return ;
	redir = job->redir;
	redir->in_file = -1;
	redir->out_file = -1;
	i = 0;
	while (redir->files && redir->files[i])
	{
		if (handle_redir_type(redir, i) != 0)
			return ;
		i++;
	}
	apply_redirections(redir);
}
