#include "../../inc/minishell.h"

static char	get_status(char *arg, char *redir_status)
{
	if (arg[0] == '>' && !arg[1])
	{
		*redir_status = 0;
		return (EXIT_SUCCESS);
	}
	else if (arg[0] == '>' && arg[0] == arg[1] && !arg[2])
	{
		*redir_status = 1;
		return (EXIT_SUCCESS);
	}
	else if (arg[0] == '<' && !arg[1])
	{
		*redir_status = 2;
		return (EXIT_SUCCESS);
	}
	else if (arg[0] == '<' && arg[0] == arg[1] && !arg[2])
	{
		*redir_status = 3;
		return (EXIT_SUCCESS);
	}
	return (-1);
}

static char	append(t_job *job, char ***address, char *element)
{
	*address = str_arr_realloc(*address, element);
	if (!*address)
		return (EXIT_FAILURE);
	job->redir->files = str_arr_realloc(job->redir->files, element);
	if (!job->redir->files)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	append_all(t_job *job, char *arg, char *redir_status, char state)
{
	if (!arg)
		return (EXIT_FAILURE);
	*redir_status = -1;
	if (!state)
		return (append(job, &job->redir->out_f, arg));
	else if (state == 1)
		return (append(job, &job->redir->app_f, arg));
	else if (state == 2)
		return (append(job, &job->redir->in_f, arg));
	else if (state == 3)
		return (append(job, &job->redir->eof, arg));
	return (EXIT_FAILURE);
}

static char	ctrl_redirect(t_job *job, char *arg, char *redir_status)
{
	char	*arg_wout_quote;

	arg_wout_quote = ft_strtrim(arg, "\"");
	if (*redir_status == 0)
	{
		job->redir->last_out = 0;
		return (append_all(job, arg_wout_quote, redir_status, 1));
	}
	else if (*redir_status == 1)
	{
		job->redir->last_out = 1;
		return (append_all(job, arg_wout_quote, redir_status, 2));
	}
	else if (*redir_status == 2)
	{
		job->redir->last_in = 0;
		return (append_all(job, arg_wout_quote, redir_status, 3));
	}
	else if (*redir_status == 3)
	{
		job->redir->last_in = 1;
		return (append_all(job, arg_wout_quote, redir_status, 4));
	}
	return (get_status(arg_wout_quote, redir_status));
}

char    handle_distribute(t_job *job, char *arg, char *redir_status)
{
	char	state;

	if (!*arg)
		return (EXIT_FAILURE);
	state = ctrl_redirect(job, arg, redir_status);
	if (state == EXIT_FAILURE)
		return (EXIT_FAILURE);
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
