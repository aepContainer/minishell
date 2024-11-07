#include "../../inc/minishell.h"

static char	if_redirection_or_heredoc(char *arg)
{
	if ((arg[0] == '<' || arg[0] == '>') && !arg[1])
		return (1);
	if ((arg[0] == '<' || arg[0] == '>') && arg[0] == arg[1] && !arg[2])
		return (2);
	return (0);
}

static char	ctrl_redirect(t_job *job, char *arg)
{
	char	state;

	if (!job->args_len)
		return (-1);
	state = if_redirection_or_heredoc(job->args[job->args_len - 1]);
	if (!state)
		return (-1);
	else if (state == 1)
	{
		job->redir->files = str_arr_realloc(job->redir->files, arg);
		if (!job->redir->files)
			return (EXIT_FAILURE);
	}
	else
	{
		job->redir->eof = str_arr_realloc(job->redir->eof, arg);
		if (!job->redir->eof)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static char	handle_distribute(t_job *job, char *arg)
{
	char	state;

	if (!*arg)
		return (EXIT_FAILURE);
	state = ctrl_redirect(job, arg);
	if (state == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (state == -1)
	{
		job->args = str_arr_realloc(job->args, arg);
		if (!job->args)
			return (EXIT_FAILURE);
		job->args_len += 1;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

char	parser(t_jobs *jobs, char *prompt)
{
	t_job	*temp;
	char	**splitted;
	int		i;

	jobs->job_list = ft_calloc(1, sizeof(t_job));
	if (!jobs->job_list)
		return (EXIT_FAILURE);
	jobs->len = 1;
	temp = jobs->job_list;
	expander(jobs, &prompt);
	splitted = word_split(prompt);
	if (!splitted)
		return (EXIT_FAILURE);
	i = -1;
	while (splitted[++i])
	{
		if (splitted[i][0] == '|')
		{
			jobs->len += 1;
			temp->next_job = ft_calloc(1, sizeof(t_job));
			if (!temp->next_job)
				return (free_str_arr(splitted), EXIT_FAILURE);
			temp = temp->next_job;
		}
		else if (handle_distribute(temp, splitted[i]))
			return (free_str_arr(splitted), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
