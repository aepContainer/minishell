#include "../../inc/minishell.h"

static int	next_quote(char *str, int i, char quote)
{
	while (str[i] != quote)
		i++;
	return (i);
}

static char	dist_jobs_line_helper(t_jobs *jobs)
{
	t_jobs	*rtrn;

	rtrn->job_list = ft_calloc(1, sizeof(t_job));
	if (!rtrn->job_list)
		return (free(rtrn), -1);
	return (rtrn);
}

char	dist_jobs(t_jobs *jobs, char *prompt)
{
	t_job	*temp;
	int		i;

	jobs = dist_jobs_line_helper();
	if (!jobs)
		return (-1);
	temp = jobs->job_list;
	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] == '|')
		{
			temp->next = ft_calloc(1, sizeof(t_job));
			if (!temp->next_job)
				return (free_jobs(jobs), -1);
			temp = temp->next_job;
			jobs->len++;
		}
		if (prompt[i] == DQUOTE)
			next_quote(prompt, i, DQUOTE);
		else if (prompt[i] == SQUOTE)
			next_quote(prompt, i, SQUOTE);
	}
	return (0);
}

static char	dist_args_line_helper(t_job *job_list, char *prompt, int start, int len)
{
	char	*temp;

	temp = ft_substr(prompt, start, len);
	if (!temp)
		return (-1);
	job_list->quotes = str_arr_realloc(job_list->quotes, temp);
	free(temp);
	if (!job_list->quotes)
		return (-1);
	return (0);
}

char	dist_args(t_job *job_list, char *prompt)
{
	char	quote;
	int		start;
	int		len;
	int		i;

	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] == '|')
			job_list = job_list->next;
		if (prompt[i] == DQUOTE || prompt[i] == SQUOTE)
		{
			quote = prompt[i];
			start = i;
			len = 0;
			while (prompt[++i] != quote)
				len++;
		}
		if (dist_args_line_helper(job_list, prompt, start, len))
			return (-1);
	}
	return (0);
}
