#include "../../inc/minishell.h"

static char	append_files(t_job *temp, char *arg)
{
	temp->redir->files = str_arr_realloc(temp->redir->files, arg);
	if (!temp->redir->files)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	get_status(char *arg, char *redir_status)
{
	if (arg[0] == '<' && !arg[1])
		*redir_status = 0;
	else if (arg[0] == '>' && !arg[1])
		*redir_status = 1;
	else if (arg[0] == '<' && arg[1] == arg[0] && !arg[2])
		*redir_status = 2;
	else if (arg[0] == '>' && arg[1] == arg[0] && !arg[2])
		*redir_status = 3;
	else
		*redir_status = -1;
}

static char	ctrl_redirect_line_helper(t_job *job, char *arg
	, char *redir_status)
{
	if (*redir_status == 2)
	{
		*redir_status = -1;
		job->redir->last_in = 2;
		job->redir->eof = str_arr_realloc(job->redir->eof, arg);
		if (!job->redir->eof || append_files(job, arg))
			return (EXIT_FAILURE);
	}
	else if (*redir_status == 3)
	{
		*redir_status = -1;
		job->redir->last_out = 2;
		job->redir->app_f = str_arr_realloc(job->redir->app_f, arg);
		if (!job->redir->app_f || append_files(job, arg))
			return (EXIT_FAILURE);
	}
	else
		get_status(arg, redir_status);
	return (EXIT_SUCCESS);
}

static char	ctrl_redirect(t_job *job, char *arg, char *redir_status)
{
	if (*redir_status == 0)
	{
		*redir_status = -1;
		job->redir->last_in = 1;
		job->redir->in_f = str_arr_realloc(job->redir->in_f,
				arg);
		if (!job->redir->in_f || append_files(job, arg))
			return (EXIT_FAILURE);
	}
	else if (*redir_status == 1)
	{
		*redir_status = -1;
		job->redir->last_out = 1;
		job->redir->out_f = str_arr_realloc(job->redir->out_f,
				arg);
		if (!job->redir->out_f || append_files(job, arg))
			return (EXIT_FAILURE);
	}
	return (ctrl_redirect_line_helper(job, arg, redir_status));
}

char	handle_distribute(t_job *temp, char *arg, char *redir_status)
{
	char	state;
	char	**temp_args;

	temp_args = temp->args;
	if (!*arg)
		return (EXIT_FAILURE);
	state = ctrl_redirect(temp, arg, redir_status);
	if (arg[0] == '<' && !arg[1])
		return (EXIT_SUCCESS);
	else if (arg[0] == '>' && !arg[1])
		return (EXIT_SUCCESS);
	else if (arg[0] == '<' && arg[1] == arg[0] && !arg[2])
		return (EXIT_SUCCESS);
	else if (arg[0] == '>' && arg[1] == arg[0] && !arg[2])
		return (EXIT_SUCCESS);
	if (state == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (*redir_status == -1 && !ctrl_append(temp->redir, arg))
	{
		temp->args = str_arr_realloc(temp_args, arg);
		if (!temp->args)
			return (free_str_arr(temp->args), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
